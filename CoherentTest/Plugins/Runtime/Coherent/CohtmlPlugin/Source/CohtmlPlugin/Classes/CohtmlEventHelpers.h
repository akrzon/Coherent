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

#include "CohtmlJSEvent.h"

#include "CohtmlEventHelpers.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCohtmlReadyForBindingsSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCohtmlBindingsReleasedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCohtmlScriptingReady);
DECLARE_DYNAMIC_DELEGATE_FourParams(FCohtmlOnLiveViewSizeRequest, UCohtmlBaseComponent*, compo, const FString&, name, int32&, width, int32&, height);

namespace cohtml
{
class View;
}

namespace CohtmlEventHelpers
{
	COHTMLPLUGIN_API void TriggerJSEvent(const FString& name, UCohtmlJSEvent* eventData, cohtml::View* View);
}

struct FCohtmlCaretRect
{
	FCohtmlCaretRect()
		: X(0)
		, Y(0)
		, Width(0)
		, Height(0)
	{}
	FCohtmlCaretRect(int32 InX, int32 InY, uint32 InWidth, uint32 InHeight)
		: X(InX)
		, Y(InY)
		, Width(InWidth)
		, Height(InHeight)
	{}

	int32 X;
	int32 Y;
	uint32 Width;
	uint32 Height;
};

/** Dummy class required in this file as otherwise UE4 won't generate delegates from the above macros. */
UCLASS(meta=(DisplayName = "Prysm Event Helpers"))
class UCohtmlEventHelpers : public UObject
{
	GENERATED_UCLASS_BODY()
};