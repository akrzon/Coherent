#pragma once
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
#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/Internationalization/Text.h"

#include "Widgets/Input/IVirtualKeyboardEntry.h"
#include "cohtml/Binding/EventHandler.h"
#include "cohtml/InputEvents.h"
#include "cohtml/InputProxy.h"
#include "cohtml/View.h"

#include "CohtmlFStringBinder.h"

class COHTMLPLUGIN_API FCohtmlVirtualKeyboardEntry : public IVirtualKeyboardEntry
{
public:
	FCohtmlVirtualKeyboardEntry(cohtml::View* InOwner, cohtml::IInputProxy* InInputProxy);
#if !defined(COHTML_UE4_419_SUPPORT)
	FCohtmlVirtualKeyboardEntry(cohtml::View* InOwner, cohtml::IInputProxy* InInputProxy, FVirtualKeyboardOptions InOptions);
#endif
	bool GetInputAttribute(const char* AttributeName, FString& Text);
	void ClearOwningView();
	virtual void SetTextFromVirtualKeyboard(const FText& InNewText, ETextEntryType TextEntryType) override;
#if !defined(COHTML_UE4_420_SUPPORT)
	virtual void SetSelectionFromVirtualKeyboard(int InSelStart, int InSelEnd) override;
#endif
	virtual FText GetText() const override;
	virtual FText GetHintText() const override;
	virtual EKeyboardType GetVirtualKeyboardType() const override;
#if !defined(COHTML_UE4_419_SUPPORT)
	virtual FVirtualKeyboardOptions GetVirtualKeyboardOptions() const override;
#endif
	virtual bool IsMultilineEntry() const override;
	virtual ~FCohtmlVirtualKeyboardEntry();

protected:
	cohtml::View* OwningView;
	cohtml::IInputProxy* InputProxy;
#if !defined(COHTML_UE4_419_SUPPORT)
	FVirtualKeyboardOptions Options;
#endif
	cohtml::BoundEventHandle VirtualKeyboardInfoHandler;
	FText VirtualKeyboardTextInitial;
	FText VirtualKeyboardText;
	FText VirtualKeyboardHint;
	EKeyboardType VirtualKeyboardType;
	bool bIsMultilineEntry;
};
