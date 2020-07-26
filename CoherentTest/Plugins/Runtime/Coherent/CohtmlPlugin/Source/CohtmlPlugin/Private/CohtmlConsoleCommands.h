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

#include <HAL/IConsoleManager.h>

namespace cohtml
{
class View;
}

class FCohtmlConsoleCommands
{
public:
	FCohtmlConsoleCommands();

	bool IsViewProfiled(const cohtml::View* View) const;
	void ResetViewTrackingData() { ViewData.Empty(); }
private:
	void ExecuteListCommand(UWorld* World);
	void ExecuteRefreshCommand(const TArray<FString>& Args, UWorld* World);
	void ExecuteRedirectCommand(const TArray<FString>& Args, UWorld* World);
	void ExecuteDebugCommand(const TArray<FString>& Args, UWorld* World);
	void ExecuteTrackCommand(const TArray<FString>& Args, UWorld* World);
	template<typename TViewFunctor>
	void ExecuteFunctionOnViews(const TArray<FString>& Args, UWorld* World, TViewFunctor Function);

	bool bAreAnyViewsExplicitlyProfiled;
	struct ViewTrackingData
	{
		bool bIsExplicitlyProfiled;
		bool bIsPaintingDebugRects;
		ViewTrackingData()
			: bIsExplicitlyProfiled(false)
			, bIsPaintingDebugRects(false)
		{}
	};
	TMap<cohtml::View*, ViewTrackingData> ViewData;

	FAutoConsoleCommandWithWorld ListCmd;
	FAutoConsoleCommandWithWorldAndArgs RefreshCmd;
	FAutoConsoleCommandWithWorldAndArgs RedirectCmd;
	FAutoConsoleCommandWithWorldAndArgs DebugCmd;
	FAutoConsoleCommandWithWorldAndArgs TrackCmd;

};
