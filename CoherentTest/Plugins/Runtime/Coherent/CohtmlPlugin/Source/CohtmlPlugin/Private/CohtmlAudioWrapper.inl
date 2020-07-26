/*
This file is part of Cohtml, modern user interface library for
games. Release $RELEASE$. Build $VERSION$ for $LICENSEE$.

Copyright (c) 2012-2018 Coherent Labs AD and/or its licensors. All
rights reserved in all media.

The coded instructions, statements, computer programs, and/or related
material (collectively the "Data") in these files contain confidential
and unpublished information proprietary Coherent Labs and/or its
licensors, which is protected by United States of America federal
copyright law and by international treaties.

This software or source code is supplied under the terms of a license
agreement and nondisclosure agreement with Coherent Labs Limited and may
not be copied, disclosed, or exploited except in accordance with the
terms of that agreement. The Data may not be disclosed or distributed to
third parties, in whole or in part, without the prior written consent of
Coherent Labs Limited.

COHERENT LABS MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS
SOURCE CODE FOR ANY PURPOSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER, ITS AFFILIATES,
PARENT COMPANIES, LICENSORS, SUPPLIERS, OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OR PERFORMANCE OF THIS SOFTWARE OR SOURCE CODE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once
#include "CohtmlPluginPrivatePCH.h"
#include "CohtmlAudioWrapper.h"
#include <Sound/SoundWaveProcedural.h>
#include "Components/AudioComponent.h"

constexpr float BUFFER_TIME_TOLERANCE_S = 0.05f;

template<typename T>
TCohtmlAudioWrapper<T>::TCohtmlAudioWrapper()
	: Owner(nullptr)
	, bShouldOverrideAttenuation(false)
{}

template<typename T>
void TCohtmlAudioWrapper<T>::SetOwner(T* InOwner)
{
	Owner = InOwner;
}

template<typename T>
TCohtmlAudioWrapper<T>::~TCohtmlAudioWrapper()
{
	TArray<int> Keys;
	Sounds.GetKeys(Keys);
	for (auto Id : Keys)
	{
		DestroyStream(Id);
	}
}

template<typename T>
void TCohtmlAudioWrapper<T>::CreateStream(int Id, int BitDepth, int Channels, float SamplingRate)
{
#if PLATFORM_IOS
	COHTML_UE_LOG(Warning, TEXT("Playing sounds is not supported on IOS because Procedural sounds in UE4 are not implemented for that platform."));
#else
	FCohtmlSound Sound;

	Sound.BufferMinSize = 2 * SamplingRate * Channels * BUFFER_TIME_TOLERANCE_S;
	static int32 Counter = 0;
	Sound.Stream = NewObject<USoundWaveProcedural>(Owner, FName(*(FString("COHTML_") + FString::FormatAsNumber(Counter++))));
#if defined(COHTML_UE4_419_SUPPORT)
	Sound.Stream->SampleRate = SamplingRate;
#else
	Sound.Stream->SetSampleRate(SamplingRate);
#endif
	Sound.Stream->NumChannels = Channels;
	Sound.Stream->Duration = INDEFINITELY_LOOPING_DURATION;
	Sound.Stream->bLooping = false;
	Sound.Stream->bStreaming = false;

#if defined(COHTML_UE4_422_SUPPORT)
	Sound.Stream->bVirtualizeWhenSilent = true;
#endif
	Sound.Stream->DecompressionType = EDecompressionType::DTYPE_Procedural;

	Sound.Component = NewObject<UAudioComponent>(Owner);
	Sound.Component->SetSound(Sound.Stream);

	if (bShouldOverrideAttenuation)
	{
		Sound.Component->AdjustAttenuation(AttenuationSettings);
	}

	Sounds.Add(Id, Sound);
#endif
}

template<typename T>
void TCohtmlAudioWrapper<T>::DestroyStream(int Id)
{
#if !PLATFORM_IOS
	FCohtmlSound Sound;
	if (Sounds.RemoveAndCopyValue(Id, Sound) && Sound.Component->IsValidLowLevel())
	{
		Sound.Component->SetSound(nullptr);
		Sound.Component->UnregisterComponent();
	}
#endif
}

template<typename T>
void TCohtmlAudioWrapper<T>::PlayStream(int Id)
{
	auto Sound = Sounds.Find(Id);
	if (Sound)
	{
		auto ByteCount = Sound->Stream->GetAvailableAudioByteCount();
		if (ByteCount >= Sound->BufferMinSize)
		{
			Sound->Component->Play();
		}
		else
		{
			Sound->bStoppedAfterUnderrun = true;
		}
	}
}

template<typename T>
void TCohtmlAudioWrapper<T>::PauseStream(int Id)
{
	auto Sound = Sounds.Find(Id);
	if (Sound)
	{
		Sound->bStoppedAfterUnderrun = false;
		Sound->Component->Stop();
	}
}

template<typename T>
void TCohtmlAudioWrapper<T>::ReceiveDataForStream(int Id, int Samples, float** Pcm, int Channels)
{
#if !PLATFORM_IOS
	auto Sound = Sounds.Find(Id);
	if (Sound)
	{
		auto ByteCount = Sound->Stream->GetAvailableAudioByteCount();
		auto IncomingBytes = Samples * Channels * 2;
		if (ByteCount == 0 && Sound->Component->IsPlaying())
		{
			COHTML_UE_LOG(Verbose, TEXT("Pausing audio until buffer fills up."));
			Sound->bStoppedAfterUnderrun = true;
			Sound->Component->Stop();
		}
		else if (Sound->bStoppedAfterUnderrun && ByteCount + IncomingBytes >= Sound->BufferMinSize)
		{
			COHTML_UE_LOG(Verbose, TEXT("Audio buffer filled up. Resuming audio."));
			Sound->bStoppedAfterUnderrun = false;
			Sound->Component->Play();
		}

		TArray<unsigned char> Buffer;
		Buffer.Reserve(IncomingBytes);
		for (int i = 0; i < Samples; ++i)
		{
			for (int j = 0; j < Channels; ++j)
			{
				float Sample = Pcm[j][i];
				// Clip to a signed value using
				// round(sample * (2^(bitDepth-1) - 1))
				static const float CLIP_VALUE = 32767.0f;
				Sample = FMath::FloorToFloat(0.5f + Sample * CLIP_VALUE);
				Sample = FMath::Clamp(Sample, -CLIP_VALUE, CLIP_VALUE);

				short Clipped = static_cast<short>(Sample);
				char* B0 = reinterpret_cast<char*>(&Clipped);
				char* B1 = reinterpret_cast<char*>(&Clipped) + 1;
				Buffer.Push(*B0);
				Buffer.Push(*B1);
			}
		}

		Sound->Stream->QueueAudio(Buffer.GetData(), Buffer.Num());
	}
#endif
}

template<typename T>
void TCohtmlAudioWrapper<T>::StreamEnded(int Id)
{
	PauseStream(Id);
}

template<typename T>
void TCohtmlAudioWrapper<T>::ChangeStreamVolume(int Id, float Volume)
{
	auto Sound = Sounds.Find(Id);
	if (Sound)
	{
		Sound->Component->SetVolumeMultiplier(FMath::Clamp(Volume, 0.f, 1.f));
	}
}

template<typename T>
void TCohtmlAudioWrapper<T>::SetAttenuation(const FSoundAttenuationSettings& Settings)
{
	bShouldOverrideAttenuation = true;
	AttenuationSettings = Settings;
	for (auto& Sound : Sounds)
	{
		Sound.Value.Component->AdjustAttenuation(Settings);
	}
}
