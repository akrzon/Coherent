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
#include "CohtmlVirtualKeyboardEntry.h"
#include "CohtmlFStringBinder.h"
#include <Async/Async.h>

FCohtmlVirtualKeyboardEntry::FCohtmlVirtualKeyboardEntry(cohtml::View* InOwner, cohtml::IInputProxy* InInputProxy)
	: OwningView(InOwner)
	, InputProxy(InInputProxy)
	, VirtualKeyboardInfoHandler(nullptr)
	, VirtualKeyboardType(EKeyboardType::Keyboard_Default)
	, bIsMultilineEntry(false)
{
	check(OwningView);

	FString Text;
	bIsMultilineEntry = InputProxy->GetTag() == cohtml::HTMLTag::TEXTAREA;

	if (const char* Buffer = InputProxy->GetText(0))
	{
		cohtml::AnsiToTCharConverter(Buffer, strlen(Buffer), Text);
		VirtualKeyboardTextInitial = FText::FromString(Text);
		VirtualKeyboardText = VirtualKeyboardTextInitial;
	}

	if (GetInputAttribute("placeholder", Text))
	{
		VirtualKeyboardHint = FText::FromString(Text);
	}

	if (!bIsMultilineEntry)
	{
		if (GetInputAttribute("type", Text))
		{
			if (Text == TEXT("password"))
			{
				VirtualKeyboardType = EKeyboardType::Keyboard_Password;
			}
			else if (Text == TEXT("number"))
			{
				VirtualKeyboardType = EKeyboardType::Keyboard_Number;
			}
			else if (Text == TEXT("url"))
			{
				VirtualKeyboardType = EKeyboardType::Keyboard_Web;
			}
			else if (Text == TEXT("email"))
			{
				VirtualKeyboardType = EKeyboardType::Keyboard_Email;
			}
		}
	}
}

#if !defined(COHTML_UE4_419_SUPPORT)
FCohtmlVirtualKeyboardEntry::FCohtmlVirtualKeyboardEntry(cohtml::View* InOwner, cohtml::IInputProxy* InInputProxy, FVirtualKeyboardOptions InOptions)
	: FCohtmlVirtualKeyboardEntry(InOwner, InInputProxy)
{
	Options = InOptions;
}
#endif

bool FCohtmlVirtualKeyboardEntry::GetInputAttribute(const char* AttributeName, FString& Text)
{
	size_t Size = InputProxy->GetAttribute(AttributeName, nullptr, 0);
	if (Size)
	{
		TUniquePtr<char[]> Buffer(new char[Size]);
		InputProxy->GetAttribute(AttributeName, Buffer.Get(), Size);
		cohtml::AnsiToTCharConverter(Buffer.Get(), Size, Text);
		return true;
	}
	return false;
}

void FCohtmlVirtualKeyboardEntry::ClearOwningView()
{
	OwningView = nullptr;
}

FText FCohtmlVirtualKeyboardEntry::GetText() const
{
	return VirtualKeyboardText;
}

FText FCohtmlVirtualKeyboardEntry::GetHintText() const
{
	return VirtualKeyboardHint;
}

EKeyboardType FCohtmlVirtualKeyboardEntry::GetVirtualKeyboardType() const
{
	return VirtualKeyboardType;
}

bool FCohtmlVirtualKeyboardEntry::IsMultilineEntry() const
{
	return bIsMultilineEntry;
}

#if !defined(COHTML_UE4_419_SUPPORT)
FVirtualKeyboardOptions FCohtmlVirtualKeyboardEntry::GetVirtualKeyboardOptions() const
{
	return Options;
}
#endif

#if !defined(COHTML_UE4_420_SUPPORT)
void FCohtmlVirtualKeyboardEntry::SetSelectionFromVirtualKeyboard(int InSelStart, int InSelEnd)
{
	cohtml::TextInput::Selection TextSelection;
	TextSelection.SelectionRange.Start = InSelStart;
	TextSelection.SelectionRange.End = InSelEnd;
	TextSelection.SelectionDirection = cohtml::TextInput::Direction::Forward;
	bool bSuccess = InputProxy->SetSelection(TextSelection);
	if (!bSuccess)
	{
		COHTML_UE_LOG(Error, TEXT("VirtualKeyboard SetSelection failed!"));
	}
}
#endif

void FCohtmlVirtualKeyboardEntry::SetTextFromVirtualKeyboard(const FText& InNewText, ETextEntryType TextEntryType)
{
	if (TextEntryType != ETextEntryType::TextEntryCanceled)
	{
		VirtualKeyboardText = InNewText;
	}
	else
	{
		if (VirtualKeyboardText.CompareTo(VirtualKeyboardTextInitial) == 0)
		{
			return;
		}
		else
		{
			VirtualKeyboardText = VirtualKeyboardTextInitial;
		}
	}

	size_t Size;
	cohtml::CoherentToString<FText>::Invoke(VirtualKeyboardText, nullptr, &Size);
	if (Size)
	{
		TUniquePtr<char[]> Buffer(new char[Size]);
		cohtml::CoherentToString<FText>::Invoke(VirtualKeyboardText, Buffer.Get(), &Size);
		unsigned RangeStart = 0;
		unsigned RangeEnd = -1; // replace all text
		bool bSuccess = InputProxy->SetText(Buffer.Get(), Size,
			cohtml::TextInput::Range{ RangeStart, RangeEnd });
		if (!bSuccess)
		{
			COHTML_UE_LOG(Warning, TEXT("VirtualKeyboard SetText failed!"));
		}
	}
}

FCohtmlVirtualKeyboardEntry::~FCohtmlVirtualKeyboardEntry()
{
}
