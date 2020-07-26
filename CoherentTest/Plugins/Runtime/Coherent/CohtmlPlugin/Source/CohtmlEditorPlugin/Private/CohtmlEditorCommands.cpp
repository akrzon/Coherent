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
#include "CohtmlEditorPluginPrivatePCH.h"
#include "CohtmlEditorCommands.h"

#include "ISettingsViewer.h"
#include "ISettingsModule.h"

#include "CohtmlGameHUD.h"
#include "CohtmlAssetReferencer.h"
#include "CohtmlAtlasManager.h"

#include "CohtmlBaseComponent.h"
#include "CohtmlComponent.h"
#include <cohtml/View.h>
#include <cohtml/CohtmlLicense.h>

#include "Kismet2/CompilerResultsLog.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Editor/KismetCompiler/Public/KismetCompilerModule.h"
#include "GameFramework/HUD.h"
#include "GameMapsSettings.h"
#include "HAL/PlatformFilemanager.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/UObjectGlobals.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "GameFramework/GameModeBase.h"
#include "Misc/MessageDialog.h"
#include "GameFramework/WorldSettings.h"
#if PLATFORM_WINDOWS
#include "Windows/WindowsPlatformMisc.h"
// This header includes Windows.h but guards us from all of the namespace polution and warnings Windows.h introduces
#include "Windows/WindowsHWrapper.h"
#endif

namespace
{
	void EnsureDirectoryExists(const FString& Destination, const FString& Source = "")
	{
		FPlatformFileManager::Get().GetPlatformFile()
			.CreateDirectoryTree(*Destination);

		if (!Source.IsEmpty())
		{
			bool bOverwriteExistingFiles = false;
			FPlatformFileManager::Get().GetPlatformFile()
				.CopyDirectoryTree(*Destination, *Source, bOverwriteExistingFiles);
		}
	}

	void EnsureFileExists(const FString& Destination, const FString& Source)
	{
		bool bFileExists = FPlatformFileManager::Get().GetPlatformFile()
			.FileExists(*Destination);
		if (!bFileExists)
		{
			FPlatformFileManager::Get().GetPlatformFile()
				.CopyFile(*Destination, *Source);
		}
	}

	// The dev tools only run in Chrome so figure out where Chrome is
	FString FindChromeExecutable()
	{
		static FString ChromeInstallPath;
		static bool bDidTestForChrome = false;
		if (bDidTestForChrome)
		{
			return ChromeInstallPath;
		}
#if PLATFORM_WINDOWS
		// Chrome can store its registry at several places according to people's experience at stackoverflow:
		// https://stackoverflow.com/questions/17736215/universal-path-to-chrome-exe
		// So let's try with several registry keys
		TArray<FString> PossibleRegistryKeys =
		{
			TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\chrome.exe"),
			TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Google Chrome\\InstallLocation")
		};
		for (const auto& Registry : PossibleRegistryKeys)
		{
			if (FWindowsPlatformMisc::QueryRegKey(HKEY_LOCAL_MACHINE, *Registry, NULL, ChromeInstallPath))
			{
				// Hey, we found it!
				return ChromeInstallPath;
			}
		}
#elif PLATFORM_MAC
		// TODO: Try finding this path under /Applications
#else
#error "This platform is not supported"
#endif
		bDidTestForChrome = true;
		return ChromeInstallPath;
	}

	// The next 5 functions are copied from GameModeInfoCustomizer. GetCurrentGameModeClass
	// has been slightly altered.

	/** Get the currently set GameMode class */
	const UClass* GetCurrentGameModeClass()
	{
		// Check if there's a selected mode first
		check(GEditor);
		UWorld* EditorWorld = GEditor->GetEditorWorldContext().World();
		if (EditorWorld)
		{
			AWorldSettings* WorldSettings = EditorWorld->GetWorldSettings();
			if (WorldSettings->DefaultGameMode)
			{
				const UClass* GameModeClass = WorldSettings->DefaultGameMode->GetAuthoritativeClass();
				if (GameModeClass)
				{
					return GameModeClass;
				}
			}
		}

		// Check global default
		FString ClassName =
			GetMutableDefault<UGameMapsSettings>()->GetGlobalDefaultGameMode();

		if (ClassName.IsEmpty() || ClassName == "None")
		{
			return NULL;
		}

		FString StrippedClassName = ClassName;
		ConstructorHelpers::StripObjectClass(StrippedClassName);

		const UClass* GameModeClass = FindObject<UClass>(ANY_PACKAGE, *StrippedClassName);
		if (!GameModeClass)
		{
			GameModeClass = LoadObject<UClass>(NULL, *ClassName);
		}

		return GameModeClass;
	}

	/** Are we allowed to modify the currently selected GameMode */
	bool AllowModifyGameMode()
	{
		// Only allow editing GameMode BP, not native class!
		const UBlueprintGeneratedClass* GameModeBPClass = Cast<UBlueprintGeneratedClass>(GetCurrentGameModeClass());
		return (GameModeBPClass != NULL);
	}

	/** Get the CDO from the currently set GameMode class */

#if defined(COHTML_UE4_413_SUPPORT)
	typedef AGameMode AGameModeClass;
#else
	typedef AGameModeBase AGameModeClass;
#endif
	AGameModeClass* GetCurrentGameModeCDO()
	{
		UClass* GameModeClass = const_cast<UClass*>(GetCurrentGameModeClass());
		if (GameModeClass != NULL)
		{
			return GameModeClass->GetDefaultObject<AGameModeClass>();
		}
		else
		{
			return NULL;
		}
	}

	/** Find the current default class by property name */
	const UClass* GetDefaultClass(FName ClassPropertyName)
	{
		UClass* CurrentDefaultClass = NULL;
		const UClass* GameModeClass = GetCurrentGameModeClass();
		if (GameModeClass != NULL)
		{
			UClassProperty* ClassProp = FindFieldChecked<UClassProperty>(GameModeClass, ClassPropertyName);
			CurrentDefaultClass = (UClass*)ClassProp->GetObjectPropertyValue(ClassProp->ContainerPtrToValuePtr<void>(GetCurrentGameModeCDO()));
		}
		return CurrentDefaultClass;
	}

	/** Set a new default class by property name */
	void SetDefaultClass(const UClass* NewDefaultClass, FName ClassPropertyName)
	{
		const UClass* GameModeClass = GetCurrentGameModeClass();
		if (GameModeClass != NULL && AllowModifyGameMode())
		{
			UClassProperty* ClassProp = FindFieldChecked<UClassProperty>(GameModeClass, ClassPropertyName);
			const UClass** DefaultClassPtr = ClassProp->ContainerPtrToValuePtr<const UClass*>(GetCurrentGameModeCDO());
			*DefaultClassPtr = NewDefaultClass;

			// Indicate that the BP has changed and would need to be saved.
			GameModeClass->MarkPackageDirty();
		}
	}
}

FString FCohtmlEditorCommands::EnsurePageExistsInGame(const FString& SourceFilePath, const FString& DestinationName)
{
	const FCohtmlEditorPaths& CoherentPaths = FCohtmlEditorPaths::Get();
	EnsureDirectoryExists(CoherentPaths.GameUIResourcesDir);
	EnsureDirectoryExists(CoherentPaths.GameJSDir);
	EnsureDirectoryExists(CoherentPaths.GameDefaultFontsDir, CoherentPaths.DefaultFontsDir);

	const FString PageDestinationPath = FPaths::Combine(*CoherentPaths.GameUIResourcesDir,
		*DestinationName);
	const FString CoherentJSDestinationPath = FPaths::Combine(*CoherentPaths.GameJSDir,
		*CoherentPaths.CoherentCohtmlJS);

	EnsureFileExists(PageDestinationPath, SourceFilePath);
	EnsureFileExists(CoherentJSDestinationPath, CoherentPaths.CoherentJSPath);

	return PageDestinationPath;
}

PRAGMA_DISABLE_OPTIMIZATION

void FCohtmlEditorCommands::RegisterCommands()
{
#define LOCTEXT_NAMESPACE "MainCohtmlMenu"
	UI_COMMAND(AddHUD, "Add HUD", "Changes the current HUD class to " COHTML_PRODUCT "GameHUD and initialize it. (Works only if the current GameMode is a BP class)", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(AddPlane, "Add In-world UI", "Adds a 3D plane in front of the camera with a " COHTML_PRODUCT " view attached to it. (Works only if outside PIE)", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(LaunchDevTools, "Launch Dev Tools", "Inspect, debug and profile your UI while the game is running.\r\n(Can only be launched if Chrome is installed and a game is already running.)", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(ShowProfilingInfo, "Show Profiling Info", "See how to start profiling " COHTML_PRODUCT "'s Performance.", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(LaunchDocs, "Open Documentation", "Opens " COHTML_PRODUCT "'s documentation.", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(LaunchDevPortal, "Open Dev Portal", "Opens " COHTML_PRODUCT "'s Dev Portal.", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(LaunchChangelog, "Open Changelog", "Opens " COHTML_PRODUCT"'s Changelog.", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(ShowOptions, "Options", "Open " COHTML_PRODUCT "'s options", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(LaunchAtlasViewer, "Launch Atlas Viewer", "Launches " COHTML_PRODUCT "'s Atlas Viewer which allows you to preview and modify the generated texture atlases.", EUserInterfaceActionType::Button, FInputGesture());
#undef LOCTEXT_NAMESPACE
}

bool FCohtmlEditorCommands::CanExecute::AddHUD()
{
	return AllowModifyGameMode();
}

void FCohtmlEditorCommands::Execute::AddHUD()
{
	auto GameMode = GetCurrentGameModeClass();
	if (GameMode)
	{
		UBlueprint* HUDBlueprint = Cast<UBlueprint>(CohtmlAssetReferences::CoherentGameHUDBP().TryLoad());
		if (!HUDBlueprint)
		{
			COHTML_EDITOR_UE_LOG(Warning, TEXT("Cannot set HUD class! Missing file from the plugin content directory: %s"),
				*CohtmlAssetReferences::CoherentGameHUDBP().ToString());
			return;
		}
		SetDefaultClass(HUDBlueprint->GeneratedClass, "HUDClass");

		auto BlueprintGamemode = Cast<UBlueprint>(GameMode->ClassGeneratedBy);

		FCompilerResultsLog Results;
		Results.bSilentMode = true;
		Results.bLogInfoOnly = true;

#if defined(COHTML_UE4_423_SUPPORT)
		FKismetCompilerOptions CompileOptions;
		CompileOptions.CompileType = EKismetCompileType::Full;

		IKismetCompilerInterface& Compiler = FModuleManager::LoadModuleChecked<IKismetCompilerInterface>(KISMET_COMPILER_MODULENAME);
		Compiler.CompileBlueprint(BlueprintGamemode, CompileOptions, Results);
#else
		FKismetEditorUtilities::CompileBlueprint(BlueprintGamemode, EBlueprintCompileOptions::None, &Results);
#endif

		BlueprintGamemode->BroadcastCompiled();

		const FCohtmlEditorPaths& CoherentPaths = FCohtmlEditorPaths::Get();
		const FString LogoDestinationPath = FPaths::Combine(*CoherentPaths.GameUIResourcesDir, CoherentPaths.DefaultLogoName);
		const FString LogoSampleDirectoryPath = FPaths::Combine(*CoherentPaths.GameUIResourcesDir, FString("Logo"));
		EnsureDirectoryExists(LogoSampleDirectoryPath);
		EnsureFileExists(LogoDestinationPath, CoherentPaths.DefaultLogoPath);
		auto DestinationPath = FCohtmlEditorCommands::EnsurePageExistsInGame(CoherentPaths.HUDHTMLPagePath, CoherentPaths.HUDHTMLPageName);
		FString PageURL = CoherentPaths.GetBrowserURL(DestinationPath);
		FPlatformProcess::LaunchURL(*PageURL, nullptr, nullptr);
	}
	else
	{
		COHTML_EDITOR_UE_LOG(Warning, TEXT("Failed to change HUD Class to " COHTML_PRODUCT "GameHUD."));
	}
}

bool FCohtmlEditorCommands::CanExecute::AddPlane()
{
	return GEditor->PlayWorld == nullptr;
}

void FCohtmlEditorCommands::Execute::AddPlane()
{
	UBlueprint* PlaneBlueprint = Cast<UBlueprint>(CohtmlAssetReferences::CoherentPlane().TryLoad());
	bool bSuccess = false;
	if (PlaneBlueprint && GWorld)
	{
		AActor* PlaneActor = GWorld->SpawnActor<AActor>(PlaneBlueprint->GeneratedClass);
		bSuccess = PlaneActor != nullptr;
		if (bSuccess)
		{
			const FCohtmlEditorPaths& CoherentPaths = FCohtmlEditorPaths::Get();
			FCohtmlEditorCommands::EnsurePageExistsInGame(CoherentPaths.DefaultHTMLPagePath, CoherentPaths.PlaneHTMLPageName);
			const FString LogoDestinationPath = FPaths::Combine(*CoherentPaths.GameUIResourcesDir,
				CoherentPaths.DefaultLogoName);
			const FString LogoSampleDirectoryPath = FPaths::Combine(*CoherentPaths.GameUIResourcesDir, FString("Logo"));
			EnsureDirectoryExists(LogoSampleDirectoryPath);
			EnsureFileExists(LogoDestinationPath, CoherentPaths.DefaultLogoPath);
			auto ViewportClient = static_cast<FEditorViewportClient*>(GEditor->GetActiveViewport()->GetClient());

			FVector CameraPosition = ViewportClient->GetViewLocation();
			FVector CameraDirection = ViewportClient->GetLookAtLocation() - CameraPosition;
			CameraDirection.Normalize();
			GEditor->MoveActorInFrontOfCamera(*PlaneActor, CameraPosition, CameraDirection);

			FVector PlaneToCamera = CameraPosition - PlaneActor->GetActorLocation();
			PlaneToCamera.Z = 0;
			PlaneToCamera.Normalize();
			auto PlaneLookAtRotation = FQuat::FindBetween(PlaneActor->GetActorForwardVector(), PlaneToCamera);
			PlaneLookAtRotation *= FQuat::MakeFromEuler(FVector(90, 0, -90));

			PlaneActor->SetActorRotation(FRotator(PlaneLookAtRotation));
			GEditor->SelectActor(PlaneActor, true, true, true);
			ViewportClient->bNeedsRedraw = true;
		}
	}
	if (!bSuccess)
	{
		COHTML_EDITOR_UE_LOG(Warning, TEXT("Failed to spawn " COHTML_PRODUCT " Plane."));
	}
}

bool FCohtmlEditorCommands::CanExecute::LaunchDevTools()
{
	FString ChromeInstallPath = FindChromeExecutable();
	return !ChromeInstallPath.IsEmpty() && GEditor->PlayWorld != nullptr;
}

void FCohtmlEditorCommands::Execute::LaunchDevTools()
{
	FString ChromeInstallPath = FindChromeExecutable();
	verify(!ChromeInstallPath.IsEmpty()); // This should never be executed if Chrome's not there in the first place
	FString Url = FString::Printf(TEXT("http://localhost:%d"), GetDefault<UCohtmlSettings>()->DevToolsPort);
	FPlatformProcess::CreateProc(*ChromeInstallPath, *Url, true, false, false, nullptr, 0, nullptr, nullptr);
}

void FCohtmlEditorCommands::Execute::ShowProfilingInfo()
{
	const FText Title = FText::FromString(TEXT("Profiling tips"));
	const FText Reminder = FText::FromString(
		TEXT("If you are wondering how to profile " COHTML_PRODUCT "'s efforts on making your UI awesome, ")
		TEXT("start by running 'stat Prysm / stat " COHTML_PRODUCT "Memory' in the console.")
		TEXT("You can also launch our integrated Dev Tools from the " COHTML_PRODUCT " menu for even more details. \r\n")
		TEXT("See our docs for more details."));
	FMessageDialog::Open(EAppMsgType::Ok, Reminder, &Title);
}

void FCohtmlEditorCommands::Execute::LaunchDocs()
{
	FPlatformProcess::LaunchURL(*FCohtmlEditorPaths::Get().DocsURL, nullptr, nullptr);
}

void FCohtmlEditorCommands::Execute::LaunchDevPortal()
{
	FPlatformProcess::LaunchURL(*FCohtmlEditorPaths::Get().DevPortalURL, nullptr, nullptr);
}

void FCohtmlEditorCommands::Execute::LaunchChangelog()
{
	FPlatformProcess::LaunchURL(*FCohtmlEditorPaths::Get().ChangelogURL, nullptr, nullptr);
}

void FCohtmlEditorCommands::Execute::ShowOptions()
{
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	SettingsModule->ShowViewer(FName("Project"), FName("Plugins"), FName(COHTML_PRODUCT));
}

void FCohtmlEditorCommands::Execute::LaunchAtlasViewer()
{
	FCohtmlAtlasManager::Get().LaunchAtlasViewer();
}
PRAGMA_ENABLE_OPTIMIZATION
