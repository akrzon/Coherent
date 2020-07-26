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

#include <GenericPlatform/ITextInputMethodSystem.h>
#include <GenericPlatform/GenericWindow.h>

#include "CohtmlIMEManager.h"

#include <Engine/GameViewportClient.h>

class FCohtmlTextInputMethodContextGeneric : public ITextInputMethodContext
{
public:
	FCohtmlTextInputMethodContextGeneric(class FCohtmlIMEManager* imeManager)
		: IMEManager(imeManager)
		, CompositionBeginIndex(0)
		, CompositionLength(0)
		, bIsComposing(false)
	{
	}

	virtual ~FCohtmlTextInputMethodContextGeneric() {}

protected:
	virtual bool IsReadOnly() override;
#if !defined(COHTML_UE4_417_SUPPORT)
	virtual bool IsComposing() override;
#endif
	virtual uint32 GetTextLength() override;
	virtual void GetSelectionRange(uint32& BeginIndex, uint32& Length, ECaretPosition& CaretPosition) override;
	virtual void SetSelectionRange(const uint32 BeginIndex, const uint32 Length, const ECaretPosition CaretPosition) override;
	virtual void GetTextInRange(const uint32 BeginIndex, const uint32 Length, FString& OutString) override;
	virtual void SetTextInRange(const uint32 BeginIndex, const uint32 Length, const FString& InString) override;
	virtual int32 GetCharacterIndexFromPoint(const FVector2D& Point) override;
	virtual bool GetTextBounds(const uint32 BeginIndex, const uint32 Length, FVector2D& Position, FVector2D& Size) override;
	virtual void GetScreenBounds(FVector2D& Position, FVector2D& Size) override;
	virtual TSharedPtr<FGenericWindow> GetWindow() override;
	virtual void BeginComposition() override;
	virtual void UpdateCompositionRange(const int32 InBeginIndex, const uint32 InLength) override;
	virtual void EndComposition() override;

protected:
	class FCohtmlIMEManager* IMEManager;

	int32 CompositionBeginIndex;
	uint32 CompositionLength;
	FString CompositionString;
	bool bIsComposing;
};
#pragma once
