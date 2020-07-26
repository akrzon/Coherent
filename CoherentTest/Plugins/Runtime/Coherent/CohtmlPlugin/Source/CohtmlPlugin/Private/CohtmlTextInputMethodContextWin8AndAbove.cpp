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

#include "CohtmlIMEManager.h"
#include "CohtmlTextInputMethodContextWin8AndAbove.h"
#include "SCohtmlInputForward.h"
#include "CohtmlIMEManager.h"

#if !defined(COHERENT_UI_GT_UE4_414_SUPPORT) && PLATFORM_WINDOWS
#include <Windows/AllowWindowsPlatformTypes.h>
#endif

static bool IsCurrentKeyboardLayoutChinese()
{
#if PLATFORM_WINDOWS
	HKL KeyboardLayout = ::GetKeyboardLayout(0);
	// Disable warning C4302 : 'reinterpret_cast' : truncation from 'HKL' to 'LANGID'
#pragma warning( disable : 4302 )
	LANGID InputLanguageID = reinterpret_cast<LANGID>(KeyboardLayout);
#pragma warning( default : 4302 )

	return (PRIMARYLANGID(InputLanguageID) == LANG_CHINESE) ||
		(PRIMARYLANGID(InputLanguageID) == LANG_CHINESE_TRADITIONAL);
#else
	check(!"This implementation should be used for Windows 8 and above only!");
	return false;
#endif
}

uint32 FCohtmlTextInputMethodContextWin8AndAbove::GetTextLength()
{
	if (!IsCurrentKeyboardLayoutChinese())
	{
		return FCohtmlTextInputMethodContextGeneric::GetTextLength();
	}
	return bUseHelperString ? HelperString.Len() : CompositionString.Len();
}

void FCohtmlTextInputMethodContextWin8AndAbove::GetTextInRange(const uint32 BeginIndex, const uint32 Length, FString& OutString)
{
	if (!IsCurrentKeyboardLayoutChinese())
	{
		return FCohtmlTextInputMethodContextGeneric::GetTextInRange(BeginIndex, Length, OutString);
	}
	OutString = bUseHelperString ? HelperString : CompositionString.Mid(BeginIndex, Length);
}

void FCohtmlTextInputMethodContextWin8AndAbove::SetTextInRange(const uint32 BeginIndex, const uint32 Length, const FString& InString)
{
	if (!IsCurrentKeyboardLayoutChinese())
	{
		return FCohtmlTextInputMethodContextGeneric::SetTextInRange(BeginIndex, Length, InString);
	}
	//CompositionString may contain ASCII character at starting location, intentinally left in front
	CompositionString = CompositionString.Left(BeginIndex) + InString + CompositionString.Mid(OffsetIndex + BeginIndex + Length);
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
			//Set IME composition with stripped ASCII character at starting location if any
			const FString& ConfirmationCompositionString = OffsetIndex ? CompositionString.Mid(OffsetIndex) : CompositionString;
			uint32 Len = ConfirmationCompositionString.Len();
			View->IMESetComposition(TCHAR_TO_UTF8(*ConfirmationCompositionString), Len, Len);
		}
	}
}

void FCohtmlTextInputMethodContextWin8AndAbove::BeginComposition()
{
	if (!IsCurrentKeyboardLayoutChinese())
	{
		return FCohtmlTextInputMethodContextGeneric::BeginComposition();
	}
	if (!bIsComposing)
	{
		OffsetIndex = HelperString.Len();
		if (bUseHelperString)
		{
			CompositionString = HelperString;
		}
		else
		{
			CompositionString.Empty();
		}
		bIsComposing = true;
		CompositionLength = 0;
		CompositionBeginIndex = 0;
		bUseHelperString = false;
		HelperString.Empty();
	}
}

namespace
{
bool IsASCII(const TCHAR& ch)
{
	return ch <= 127;
}
}

void FCohtmlTextInputMethodContextWin8AndAbove::EndComposition()
{
	if (!IsCurrentKeyboardLayoutChinese())
	{
		return FCohtmlTextInputMethodContextGeneric::EndComposition();
	}
	if (bIsComposing && !CompositionString.IsEmpty())
	{
		int32 Length = CompositionString.Len();
		if (OffsetIndex && Length > OffsetIndex && IsASCII(CompositionString[0]))
		{
			//strip added ASCII character at starting location if any
			CompositionString = CompositionString.Mid(OffsetIndex);
		}
		if (Length == 1 && IsASCII(CompositionString[Length - 1]))
		{
			bUseHelperString = true;
			HelperString = CompositionString;
		}

		auto View = IMEManager->GetView();
		if (View)
		{
			View->IMEConfirmComposition(TCHAR_TO_UTF8(*CompositionString));
		}

		bIsComposing = false;
		CompositionString.Empty();
		CompositionBeginIndex = 0;
		CompositionLength = 0;

		// Reactivate the text input method system context so any
		// selection index/length saved by the OS is reset
		IMEManager->ActivateTextInputMethodSystemContext(false);
		IMEManager->ActivateTextInputMethodSystemContext(true);
	}
}

#if !defined(COHERENT_UI_GT_UE4_414_SUPPORT) && PLATFORM_WINDOWS
#include <Windows/HideWindowsPlatformTypes.h>
#endif