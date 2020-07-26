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
#include "Editor/MainFrame/Public/Interfaces/IMainFrameModule.h"
#include "ISettingsModule.h"
#include "AssetRegistryModule.h"
#include "AssetToolsModule.h"
#include "PropertyEditorModule.h"
#include "Framework/Commands/GenericCommands.h"
#include "CohtmlSettings.h"
#include "CohtmlTriggerEventDetails.h"
#include "CohtmlEditorDirectoryWatcher.h"
#include "CohtmlAtlasDirectoryWatcher.h"
#include "CohtmlAtlasAssetTypeActions.h"
#include "CohtmlAtlasManager.h"
#include "ICoherentRenderingPlugin.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "GameFramework/GameModeBase.h"

#if COHTML_IS_GAMEFACE
DEFINE_LOG_CATEGORY(LogPrysmEditor);
#else
DEFINE_LOG_CATEGORY(LogPrysmEditor);
#endif

class FCohtmlEditorPlugin : public ICohtmlEditorPlugin
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
	void AddMenuBarExtension(FMenuBarBuilder&);

	FDelegateHandle ContentBrowserCommandExtenderDelegateHandle;

	TSharedPtr<FUICommandList> PluginCommands;
	TSharedPtr<FExtensibilityManager> ExtensibilityManager;
	TSharedPtr<FExtender> Extender;
	TSharedPtr<const FExtensionBase> Extension;
};

IMPLEMENT_MODULE(FCohtmlEditorPlugin, CohtmlEditorPlugin)

namespace
{
#define LOCTEXT_NAMESPACE "MainCohtmlMenu"
	static void FillCohtmlMenu(FMenuBuilder& MenuBuilder, const TSharedRef< FExtender > Extender)
	{
		MenuBuilder.BeginSection("Cohtml_CreateEdit", LOCTEXT("Cohtml_CreateEditHeading", "Create + Edit"));
		{
			MenuBuilder.AddMenuEntry(FCohtmlEditorCommands::Get().AddHUD);
			MenuBuilder.AddMenuEntry(FCohtmlEditorCommands::Get().AddPlane);
		}
		MenuBuilder.EndSection();

		MenuBuilder.BeginSection("Cohtml_Documentation", LOCTEXT("Cohtml_Documentation", "Documentation"));
		{
			MenuBuilder.AddMenuEntry(FCohtmlEditorCommands::Get().LaunchDocs);
		}
		MenuBuilder.EndSection();

		MenuBuilder.BeginSection("Cohtml_Debug", LOCTEXT("Cohtml_Debug", "Debug"));
		{
			MenuBuilder.AddMenuEntry(FCohtmlEditorCommands::Get().LaunchDevTools);
			MenuBuilder.AddMenuEntry(FCohtmlEditorCommands::Get().ShowProfilingInfo);
		}
		MenuBuilder.EndSection();

		MenuBuilder.BeginSection("Cohtml_Miscellaneous", LOCTEXT("Cohtml_MiscellaneousHeading", "Miscellaneous"));
		{
			MenuBuilder.AddMenuEntry(FCohtmlEditorCommands::Get().ShowOptions);
			MenuBuilder.AddMenuEntry(FCohtmlEditorCommands::Get().LaunchAtlasViewer);
		}
		MenuBuilder.EndSection();

		MenuBuilder.BeginSection("Cohtml_NewVersionInfo", LOCTEXT("Cohtml_NewVersionInfo", "New versions and information"));
		{
			MenuBuilder.AddMenuEntry(FCohtmlEditorCommands::Get().LaunchDevPortal);
			MenuBuilder.AddMenuEntry(FCohtmlEditorCommands::Get().LaunchChangelog);
		}
		MenuBuilder.EndSection();
	}
#undef LOCTEXT_NAMESPACE


	void MapCohtmlActions(TSharedPtr<FUICommandList> PluginCommands)
	{
		PluginCommands->MapAction(FCohtmlEditorCommands::Get().AddHUD,
			FExecuteAction::CreateStatic(&FCohtmlEditorCommands::Execute::AddHUD),
			FCanExecuteAction::CreateStatic(&FCohtmlEditorCommands::CanExecute::AddHUD));

		PluginCommands->MapAction(FCohtmlEditorCommands::Get().AddPlane,
			FExecuteAction::CreateStatic(&FCohtmlEditorCommands::Execute::AddPlane),
			FCanExecuteAction::CreateStatic(&FCohtmlEditorCommands::CanExecute::AddPlane));

		PluginCommands->MapAction(FCohtmlEditorCommands::Get().LaunchDevTools,
			FExecuteAction::CreateStatic(&FCohtmlEditorCommands::Execute::LaunchDevTools),
			FCanExecuteAction::CreateStatic(&FCohtmlEditorCommands::CanExecute::LaunchDevTools));

		PluginCommands->MapAction(FCohtmlEditorCommands::Get().ShowProfilingInfo,
			FExecuteAction::CreateStatic(&FCohtmlEditorCommands::Execute::ShowProfilingInfo));

		PluginCommands->MapAction(FCohtmlEditorCommands::Get().LaunchDocs,
			FExecuteAction::CreateStatic(&FCohtmlEditorCommands::Execute::LaunchDocs));

		PluginCommands->MapAction(FCohtmlEditorCommands::Get().LaunchDevPortal,
			FExecuteAction::CreateStatic(&FCohtmlEditorCommands::Execute::LaunchDevPortal));

		PluginCommands->MapAction(FCohtmlEditorCommands::Get().LaunchChangelog,
			FExecuteAction::CreateStatic(&FCohtmlEditorCommands::Execute::LaunchChangelog));

		PluginCommands->MapAction(FCohtmlEditorCommands::Get().ShowOptions,
			FExecuteAction::CreateStatic(&FCohtmlEditorCommands::Execute::ShowOptions));

		PluginCommands->MapAction(FCohtmlEditorCommands::Get().LaunchAtlasViewer,
			FExecuteAction::CreateStatic(&FCohtmlEditorCommands::Execute::LaunchAtlasViewer));
	}

	void RegisterSettings()
	{
#define LOCTEXT_NAMESPACE "CohtmlEditorSettings"
		if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
		{
			auto DefaultValues = GetMutableDefault<UCohtmlSettings>();
			SettingsModule->RegisterSettings("Project", "Plugins", COHTML_PRODUCT,
				LOCTEXT("RuntimeSettingsName", COHTML_PRODUCT),
				LOCTEXT("RuntimeSettingsDescription", "Configure the " COHTML_PRODUCT " plugin"),
				DefaultValues
			);
		}
#undef LOCTEXT_NAMESPACE
	}

	void UnregisterSettings()
	{
		if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
		{
			SettingsModule->UnregisterSettings("Project", "Plugins", COHTML_PRODUCT);
		}
	}

}

void FCohtmlEditorPlugin::StartupModule()
{
	FCohtmlEditorCommands::Register();
	PluginCommands = MakeShareable(new FUICommandList);
	MapCohtmlActions(PluginCommands);
	FCohtmlEditorDirectoryWatcher::Initialize();
	FCohtmlAtlasDirectoryWatcher::Initialize();

	Extender = MakeShareable(new FExtender);
	Extension = Extender->AddMenuBarExtension("Window",
		EExtensionHook::After, PluginCommands, FMenuBarExtensionDelegate::CreateRaw(this, &FCohtmlEditorPlugin::AddMenuBarExtension));

	RegisterSettings();
	ICoherentRenderingPlugin::Load().RegisterSettings();
	FGenericCommands::Register(); // Required for the successful load of FLevelEditorModule
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	ExtensibilityManager = LevelEditorModule.GetMenuExtensibilityManager();
	ExtensibilityManager->AddExtender(Extender);

	// Register the details customizations
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.RegisterCustomClassLayout("K2Node_CohtmlTriggerEventOneOff",
			FOnGetDetailCustomizationInstance::CreateStatic(&FCohtmlTriggerEventDetails::MakeInstance));
		PropertyModule.NotifyCustomizationModuleChanged();
	}

	FCohtmlAtlasManagerCallbacks::RegisterCallbacks();

	TSharedRef<FCohtmlAtlasAssetTypeActions> AtlasAssetTypeActions(new FCohtmlAtlasAssetTypeActions());
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetTools.RegisterAssetTypeActions(AtlasAssetTypeActions);

	COHTML_EDITOR_UE_LOG(Log, TEXT("Editor plugin initialized!"));
}


void FCohtmlEditorPlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FCohtmlEditorCommands::Unregister();
	FCohtmlEditorDirectoryWatcher::Uninitialize();
	FCohtmlAtlasDirectoryWatcher::Uninitialize();

	Extender->RemoveExtension(Extension.ToSharedRef());

	if (ExtensibilityManager.IsValid())
	{
		ExtensibilityManager->RemoveExtender(Extender);
	}
	else
	{
		ExtensibilityManager.Reset();
	}
	UnregisterSettings();

	FCohtmlAtlasManagerCallbacks::UnregisterCallbacks();

	COHTML_EDITOR_UE_LOG(Log, TEXT("Editor plugin shut-down!"));
}

void FCohtmlEditorPlugin::AddMenuBarExtension(FMenuBarBuilder& MenuBuilder)
{
#define LOCTEXT_NAMESPACE "MainMenu"

	COHTML_EDITOR_UE_LOG(Log, TEXT("Starting Extension logic"));

	MenuBuilder.AddPullDownMenu(
		LOCTEXT("CohtmlMenu", COHTML_PRODUCT),
		LOCTEXT("CohtmlMenu_Tooltip", "Open the " COHTML_PRODUCT " menu."),
		FNewMenuDelegate::CreateStatic(&FillCohtmlMenu, Extender.ToSharedRef()),
		"CohtmlMenu"
	);

#undef LOCTEXT_NAMESPACE

}

