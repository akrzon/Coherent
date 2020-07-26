/*
This file is part of Renoir, a modern graphics library.
Release $RELEASE$. Build $VERSION$ for $LICENSEE$.

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
#include "CoherentRenderingPluginPrivatePCH.h"
#include "CohIndexBuffer.h"

FCohIndexBuffer::FCohIndexBuffer(unsigned SizeInBytes, unsigned IndexCount, bool bIsDynamic)
	: IsDynamic(bIsDynamic)
	, ElementSizeInBytes(SizeInBytes)
	, LockedPointer(nullptr)
{
	Size = IndexCount * ElementSizeInBytes;
	InitResource();
}

FCohIndexBuffer::~FCohIndexBuffer()
{
	ReleaseResource();
}

void FCohIndexBuffer::InitRHI()
{
	FRHIResourceCreateInfo Info;
	IndexBufferRHI = RHICreateIndexBuffer(
		ElementSizeInBytes,
		Size,
#if PLATFORM_PS4 || PLATFORM_DPX
		IsDynamic ? BUF_Volatile : BUF_Static,
#else
		IsDynamic ? BUF_Dynamic : BUF_Static,
#endif
		Info);
	verify(IndexBufferRHI);
}

void* FCohIndexBuffer::Lock()
{
	check(!IsLocked());
	LockedPointer = RHILockIndexBuffer(IndexBufferRHI, 0, Size, RLM_WriteOnly);
	return LockedPointer;
}

void* FCohIndexBuffer::LockPtr()
{
	return LockedPointer;
}

void FCohIndexBuffer::Unlock()
{
	check(IsLocked());
	RHIUnlockIndexBuffer(IndexBufferRHI);
	LockedPointer = nullptr;
}

bool FCohIndexBuffer::IsLocked() const
{
	return LockedPointer != nullptr;
}

bool FCohIndexBuffer::UpdateData(const void* Data, size_t DataLen)
{
	check(DataLen <= Size);
	bool wasLocked = IsLocked();
	if (!wasLocked)
	{
		Lock();
	}

	FMemory::Memcpy(LockPtr(), Data, DataLen);

	if (!wasLocked)
	{
		Unlock();
	}

	return true;
}

size_t FCohIndexBuffer::GetMemorySize()
{
	return Size;
}
