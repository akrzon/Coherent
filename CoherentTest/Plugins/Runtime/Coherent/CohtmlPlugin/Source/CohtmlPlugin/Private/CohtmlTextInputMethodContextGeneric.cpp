/*
This file is part of Cohtml, Gameface and Prysm -
modern user interface technologies for games. Release $RELEASE$. Build $VERSION$ for $LICENSEE$.

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
#include "CohtmlPluginPrivatePCH.h"
#include "CohtmlTextInputMethodContextGeneric.h"

#include "CohtmlIMEManager.h"
#include "SCohtmlInputForward.h"
#include "CohtmlIMEManager.h"

// Win7 IME doesn't end a composition until the user either cancels it or confirms it.
// Even if the string is very long and the composition is done in parts
// (i.e. some latin letters are converted and some more are left),
// this is a single composition. This means that |CompositionString| is the
// ongoing composition and we can safely reset it to empty string when starting
// a new one.
//
// Also, SetTextInRange is usually called with the single new letter that needs
// to be appended.

#if !defined(COHTML_UE4_417_SUPPORT)
bool FCohtmlTextInputMethodContextGeneric::IsComposing()
{
	return bIsComposing;
}
#endif

bool FCohtmlTextInputMethodContextGeneric::IsReadOnly()
{
	return !IMEManager->IsValid();
}

uint32 FCohtmlTextInputMethodContextGeneric::GetTextLength()
{
	return CompositionString.Len();
}

void FCohtmlTextInputMethodContextGeneric::GetSelectionRange(uint32& BeginIndex, uint32& Length, ECaretPosition& OutCaretPosition)
{
	BeginIndex = CompositionBeginIndex;
	Length = CompositionLength;
	OutCaretPosition = ITextInputMethodContext::ECaretPosition::Ending;
}

void FCohtmlTextInputMethodContextGeneric::SetSelectionRange(const uint32 BeginIndex, const uint32 Length, const ECaretPosition InCaretPosition)
{
	CompositionBeginIndex = BeginIndex;
	CompositionLength = Length;
}

void FCohtmlTextInputMethodContextGeneric::GetTextInRange(const uint32 BeginIndex, const uint32 Length, FString& OutString)
{
	OutString = CompositionString.Mid(BeginIndex, Length);
}

void FCohtmlTextInputMethodContextGeneric::SetTextInRange(const uint32 BeginIndex, const uint32 Length, const FString& InString)
{
	CompositionString = CompositionString.Left(BeginIndex) + InString + CompositionString.Mid(BeginIndex + Length);

	check(BeginIndex >= 0);
	check(Length >= 0);

	auto View = IMEManager->GetView();
	if (View)
	{
		if (CompositionString.IsEmpty())
		{
			View->IMECancelComposition();
		}
		else
		{
			uint32 Len = CompositionString.Len();
			View->IMESetComposition(TCHAR_TO_UTF8(*CompositionString), Len, Len);
		}
	}
}

int32 FCohtmlTextInputMethodContextGeneric::GetCharacterIndexFromPoint(const FVector2D& Point)
{
	return INDEX_NONE;
}

bool FCohtmlTextInputMethodContextGeneric::GetTextBounds(const uint32 BeginIndex, const uint32 Length, FVector2D& Position, FVector2D& Size)
{
	Position = FVector2D(0, 0);
	Size = FVector2D(0, 0);

	if (IMEManager->IsValid())
	{
		if (IMEManager->RequiresProjection())
		{
			// Projection to screen coordinates is what we should do here,
			// but the object's geometry makes it difficult to create a location
			// on screen that doesn't obstruct the actual text field.
			// For now, just show the candidate list in the top left corner of
			// the screen.
		}
		else
		{
			// HUD View
			const auto& CaretRect = IMEManager->GetCaretRect();
			Position = FVector2D(CaretRect.X, CaretRect.Y);
			Size = FVector2D(CaretRect.Width, CaretRect.Height);

			if (GEngine && GEngine->IsValidLowLevel() &&
				GEngine->GameViewport && !GEngine->GameViewport->IsFullScreenViewport() &&
				GEngine->GameViewport->Viewport)
			{
				FIntPoint ViewportOffset = GEngine->GameViewport->Viewport->ViewportToVirtualDesktopPixel(FVector2D(0, 0));
				// ViewportToVirtualDesktopPixel returns non-dpi-scaled coordinates, so we need to scale them
				auto DPIScale = GEngine->GameViewport->Viewport->GetClient()->GetDPIScale();
				ViewportOffset.X = ViewportOffset.X * DPIScale;
				ViewportOffset.Y = ViewportOffset.Y * DPIScale;
				Position += FVector2D(ViewportOffset);
			}
		}
	}

	bool IsClipped = false;
	return IsClipped;
}

void FCohtmlTextInputMethodContextGeneric::GetScreenBounds(FVector2D& Position, FVector2D& Size)
{
	Position = FVector2D(0, 0);
	Size = FVector2D(0, 0);
}

TSharedPtr<FGenericWindow> FCohtmlTextInputMethodContextGeneric::GetWindow()
{
	return IMEManager->GetWindow();
}

void FCohtmlTextInputMethodContextGeneric::BeginComposition()
{
	if (!bIsComposing)
	{
		bIsComposing = true;

		CompositionString.Empty();
		CompositionBeginIndex = 0;
		CompositionLength = 0;
	}
}

void FCohtmlTextInputMethodContextGeneric::UpdateCompositionRange(const int32 InBeginIndex, const uint32 InLength)
{
	check(bIsComposing);
}

void FCohtmlTextInputMethodContextGeneric::EndComposition()
{
	if (bIsComposing && !CompositionString.IsEmpty())
	{
		auto View = IMEManager->GetView();
		if (View)
		{
			View->IMEConfirmComposition(TCHAR_TO_UTF8(*CompositionString));
		}

		bIsComposing = false;
		CompositionString.Empty();
		CompositionBeginIndex = 0;
		CompositionLength = 0;
	}
}
