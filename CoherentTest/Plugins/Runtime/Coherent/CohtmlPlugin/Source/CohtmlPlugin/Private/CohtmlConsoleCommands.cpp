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
#include "CohtmlPluginPrivatePCH.h"
#include "CohtmlConsoleCommands.h"

#include "CohtmlSystem.h"
#include "CohtmlBaseComponent.h"
#include "CohtmlWidget.h"
#include "CohtmlSettings.h"

#include "EngineUtils.h"
#include "UObject/UObjectIterator.h"
#include "GameFramework/PlayerController.h"

FCohtmlConsoleCommands::FCohtmlConsoleCommands()
	: bAreAnyViewsExplicitlyProfiled(false)
	, ListCmd(TEXT("cohtml.list"),
		TEXT("List all currently active views"),
		FConsoleCommandWithWorldDelegate::CreateRaw(this, &FCohtmlConsoleCommands::ExecuteListCommand))
	, RefreshCmd(TEXT("cohtml.reload"),
		TEXT("Refreshes the view with the specified <id> or all views if no id is specified."),
		FConsoleCommandWithWorldAndArgsDelegate::CreateRaw(this, &FCohtmlConsoleCommands::ExecuteRefreshCommand))
	, RedirectCmd(TEXT("cohtml.redirect"),
		TEXT("Redirects the view with the specified <id> to the specified <url> or all views if no id is specified.")
			LINE_TERMINATOR
		TEXT("Note: the <url> MUST be surrounded by DOUBLE quotes (e.g. \"http://coherent-labs.com\")"),
		FConsoleCommandWithWorldAndArgsDelegate::CreateRaw(this, &FCohtmlConsoleCommands::ExecuteRedirectCommand))
	, DebugCmd(TEXT("cohtml.debug"),
		TEXT("Toggles drawing of paint rectangles on the view with the specified <id> or all views if no id is specified."),
		FConsoleCommandWithWorldAndArgsDelegate::CreateRaw(this, &FCohtmlConsoleCommands::ExecuteDebugCommand))
	, TrackCmd(TEXT("cohtml.track"),
		TEXT("Toggles tracking the view with the specified <id>. Only tracked views are profiled with stat " COHTML_PRODUCT ".")
			LINE_TERMINATOR
		TEXT("* If no views are explicitly tracked, all views are profiled.")
			LINE_TERMINATOR
		TEXT("* Pass no arguments to reset tracked views."),
		FConsoleCommandWithWorldAndArgsDelegate::CreateRaw(this, &FCohtmlConsoleCommands::ExecuteTrackCommand))
{
}

bool FCohtmlConsoleCommands::IsViewProfiled(const cohtml::View* View) const
{
	// Check whether no views are explicitly tracked -> then all views are tracked
	if (ViewData.Num() == 0 || !bAreAnyViewsExplicitlyProfiled)
	{
		return true;
	}
	auto TrackingData = ViewData.Find(View);
	return TrackingData && TrackingData->bIsExplicitlyProfiled;
}

void FCohtmlConsoleCommands::ExecuteListCommand(UWorld* World)
{
	// UE4 does not provide a console command callback with both world and output
	// so we need to cheat
	auto PlayerController = World->GetFirstPlayerController();
	if (!PlayerController)
	{
		return;
	}

	ACohtmlSystem* SystemActor = nullptr;

	for (auto It = TActorIterator<ACohtmlSystem>(World); It; ++It)
	{
		SystemActor = *It;
		break;
	}
	check(SystemActor);

	const uint8 Padding = 15;
	PlayerController->ClientMessage(FString(TEXT("id")).RightPad(Padding) + TEXT("title"));
	auto LogViewLambda = [&](const cohtml::View* View)
	{
		if (View)
		{
			FString Id = FString::FormatAsNumber(View->GetId()).RightPad(Padding);
			PlayerController->ClientMessage(Id);
		}
	};
	for (auto ComponentIt = SystemActor->GetCohtmlComponentsIterator(); ComponentIt; ++ComponentIt)
	{
		LogViewLambda(ComponentIt->Get()->GetView());
	}
	for (TObjectIterator<UCohtmlWidget> WidgetIt; WidgetIt; ++WidgetIt)
	{
		if (WidgetIt->GetWorld() == World)
		{
			// TObjectIterator may return UMG Widgets from the editor, outside the
			// game so skip if the world does not match
			LogViewLambda(WidgetIt->GetView());
		}
	}
}
template<typename TViewFunctor>
void FCohtmlConsoleCommands::ExecuteFunctionOnViews(const TArray<FString>& Args, UWorld* World, TViewFunctor Functor)
{
	ACohtmlSystem* SystemActor = nullptr;

	for (auto It = TActorIterator<ACohtmlSystem>(World); It; ++It)
	{
		SystemActor = *It;
		break;
	}
	check(SystemActor);

	const unsigned DefaultId = static_cast<unsigned>(-1);
	unsigned ViewIdToRefresh = DefaultId;
	if (Args.Num() > 0)
	{
		ViewIdToRefresh = FCString::Atoi(*Args[0]);
	}

	bool bViewFound = false;
	auto ExecuteFuncLambda = [&](cohtml::View* View)
	{
		if (View && (ViewIdToRefresh == DefaultId || View->GetId() == ViewIdToRefresh))
		{
			Functor(View);
			bViewFound = true;
		}
	};
	for (auto ComponentIt = SystemActor->GetCohtmlComponentsIterator(); ComponentIt; ++ComponentIt)
	{
		ExecuteFuncLambda(ComponentIt->Get()->GetView());
	}
	for (TObjectIterator<UCohtmlWidget> WidgetIt; WidgetIt; ++WidgetIt)
	{
		if (WidgetIt->GetWorld() == World)
		{
			// TObjectIterator may returns UMG Widgets from the editor, outside the
			// game so skip if the world does not match
			ExecuteFuncLambda(WidgetIt->GetView());
		}
	}
	if (!bViewFound)
	{
		auto PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->ClientMessage(TEXT("Command execution failed - either the specified id is invalid or no views exists"));
		}
	}
}

void FCohtmlConsoleCommands::ExecuteRefreshCommand(const TArray<FString>& Args, UWorld* World)
{
	ExecuteFunctionOnViews(Args, World, [](cohtml::View* View) { View->Reload(); });
}
void FCohtmlConsoleCommands::ExecuteRedirectCommand(const TArray<FString>& Args, UWorld* World)
{
	if (Args.Num() == 0)
	{
		auto PlayerController = World->GetFirstPlayerController();
		if (!PlayerController)
		{
			return;
		}
		PlayerController->ClientMessage(TEXT("cohtml.redirect requires an URL"));
		return;
	}
	// If the user provided only an URL, replace the first arg as ExecuteFunctionOnViews thinks of it
	// as the view's id and will try to parse it
	auto ModifiedArgs = Args;
	FString URL;
	if (Args.Num() == 1)
	{
		URL = ModifiedArgs[0];
		ModifiedArgs[0] = "-1";
	}
	else if (Args.Num() >= 2)
	{
		URL = ModifiedArgs[1];
	}
	URL.ReplaceInline(TEXT("\""), TEXT(""));
	ExecuteFunctionOnViews(ModifiedArgs, World, [&URL](cohtml::View* View)
	{
		View->LoadURL(TCHAR_TO_UTF8(*URL));
	});
}
void FCohtmlConsoleCommands::ExecuteDebugCommand(const TArray<FString>& Args, UWorld* World)
{
	ExecuteFunctionOnViews(Args, World, [this](cohtml::View* View)
	{
		auto& TrackingData = ViewData.FindOrAdd(View);
		TrackingData.bIsPaintingDebugRects = !TrackingData.bIsPaintingDebugRects;
		View->ShowPaintRectangles(TrackingData.bIsPaintingDebugRects);
	});
}
void FCohtmlConsoleCommands::ExecuteTrackCommand(const TArray<FString>& Args, UWorld* World)
{
	if (Args.Num() == 0)
	{
		// No args, reset tracking
		for (auto& It : ViewData)
		{
			It.Value.bIsExplicitlyProfiled = false;
		}
		bAreAnyViewsExplicitlyProfiled = false;
	}

	ExecuteFunctionOnViews(Args, World, [this](cohtml::View* View)
	{
		auto& TrackingData = ViewData.FindOrAdd(View);
		TrackingData.bIsExplicitlyProfiled = !TrackingData.bIsExplicitlyProfiled;
		if (TrackingData.bIsExplicitlyProfiled)
		{
			bAreAnyViewsExplicitlyProfiled = true;
		}
		else
		{
			for (auto& It : ViewData)
			{
				if (It.Value.bIsExplicitlyProfiled)
				{
					return;
				}
			}
			bAreAnyViewsExplicitlyProfiled = false;
		}
	});
}