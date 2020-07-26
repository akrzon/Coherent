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
#include "CohtmlAtlasManager.h"
#include "CohtmlAtlasBuilder.h"
#include "CohtmlAtlasMappingData.h"
#include "CohtmlSettings.h"

#include <Editor.h>
#include <Settings/ProjectPackagingSettings.h>
#include <AssetRegistryModule.h>
#include <Engine/TextureRenderTarget2D.h>
#include <IAssetRegistry.h>
#include <AssetToolsModule.h>
#include <ContentBrowserModule.h>
#include <ObjectTools.h>
#include <Interfaces/IMainFrameModule.h>
#include <PipelineStateCache.h>
#include <Framework/Application/SlateApplication.h>
#include <Widgets/SNullWidget.h>
#include <Settings/ProjectPackagingSettings.h>
#include <HAL/PlatformFilemanager.h>

#include <Framework/MultiBox/MultiBoxBuilder.h>
#include <PropertyCustomizationHelpers.h>
#include <Editor/PropertyEditor/Public/IStructureDetailsView.h>
#include <PropertyEditorModule.h>
#include <Widgets/Images/SImage.h>
#include <Widgets/Input/SButton.h>
#include <Widgets/Input/SEditableTextBox.h>
#include <Widgets/Input/SNumericEntryBox.h>
#include <Widgets/Layout/SBorder.h>
#include <Widgets/Layout/SGridPanel.h>
#include <Widgets/Text/STextBlock.h>
#include <Widgets/Views/STableRow.h>
#include <Widgets/Views/SListView.h>
#if defined(COHTML_UE4_419_SUPPORT)
#include <Brushes/SlateImageBrush.h>
#else
#include <Slate/DeferredCleanupSlateBrush.h>
#endif

// So that we can check if we're cooking in Editor
#include <Developer/LauncherServices/Public/ILauncherWorker.h>
#include <Async/Async.h>

#define LOCTEXT_NAMESPACE "CohtmlAtlasManager"

namespace
{
	template <typename ObjectType>
	static ObjectType* FindOrLoadObject(const FString& ObjectPath)
	{
		ObjectType* Object = FindObject<ObjectType>(nullptr, *ObjectPath);
		if (!Object)
		{
			Object = LoadObject<ObjectType>(nullptr, *ObjectPath);
		}

		return Object;
	}
}


class SAtlasInfoItem : public SMultiColumnTableRow<AtlasInfoPtr>
{
public:
	SLATE_BEGIN_ARGS(SAtlasInfoItem)
	    : _AtlasInfo()
	{
	}
	SLATE_ARGUMENT(AtlasInfoPtr, AtlasInfo)

	SLATE_END_ARGS()

	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override
	{
		auto PreviewHandler = [this]() -> FReply {
			FCohtmlAtlasManager::Get().LaunchAtlasPreview(*AtlasInfo->AtlasPath);
			return FReply::Handled();
		};

		auto DeleteHandler = [this]() -> FReply {
			TArray<UObject*> AtlasesToDelete;
			UTexture2D* AtlasToDelete = FindOrLoadObject<UTexture2D>(*AtlasInfo->AtlasPath);
			AtlasesToDelete.Add(AtlasToDelete);
			ObjectTools::DeleteObjects(AtlasesToDelete);
			return FReply::Handled();
		};

		auto RebuildHandler = [this]() -> FReply {
			FCohtmlAtlasManager::Get().RebuildAtlas(*AtlasInfo->AtlasPath);
			return FReply::Handled();
		};

		if (ColumnName == TEXT("AtlasName"))
		{
			FString ShortAtlasName;
			AtlasInfo->AtlasPath.Split(".", nullptr, &ShortAtlasName);
			return SAssignNew(AtlasTextBox, SEditableTextBox)
				.Text(FText::Format(LOCTEXT("TextureAtlasName", "{0}"), FText::FromString(*ShortAtlasName)))
				.Justification(ETextJustify::Right)
				.RevertTextOnEscape(true)
				.SelectAllTextWhenFocused(true)
				.OnTextCommitted_Lambda([&, ShortAtlasName](const FText& InText, ETextCommit::Type InCommitType) {
					auto Atlases = FCohtmlAtlasManager::Get().GetAtlases();
					bool bAtlasAlreadyExists = false;
					FString TempAtlasShortName;
					for (const auto& Atlas : Atlases)
					{
						Atlas->AtlasPath.Split(".", nullptr, &TempAtlasShortName);
						if (TempAtlasShortName == InText.ToString())
						{
							bAtlasAlreadyExists = true;
							break;
						}
					}
					// If the user clicks escape after changing the name and before it's committed
					// OR if we already have an atlas with the specified name, we want to discard
					// the content of the text box and revert its previous one
					if (InCommitType != ETextCommit::OnCleared && !bAtlasAlreadyExists)
					{
						TWeakObjectPtr<UTexture2D> AtlasToRename = LoadObject<UTexture2D>(nullptr, *AtlasInfo->AtlasPath);
						IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
						TArray<FAssetRenameData> AssetsAndNames;
						const FString PackagePath = FPackageName::GetLongPackagePath(AtlasToRename->GetOutermost()->GetName());
						new(AssetsAndNames) FAssetRenameData(AtlasToRename, PackagePath, InText.ToString());
						AssetTools.RenameAssets(AssetsAndNames);
					}
					else
					{
						AtlasTextBox->SetText(FText::FromString(ShortAtlasName));
					}
				});
		}
		if (ColumnName == TEXT("PreviewButton"))
		{
			return SNew(SButton)
				.Text(FText::FromString("Preview"))
				.OnClicked_Lambda(PreviewHandler);
		}
		if (ColumnName == TEXT("DeleteButton"))
		{
			return SNew(SButton)
				.Text(FText::FromString("Delete"))
				.OnClicked_Lambda(DeleteHandler);
		}
		if (ColumnName == TEXT("NeedsRebuild"))
		{
			return SNew(SButton)
				.Text(FText::FromString("Rebuild"))
				.OnClicked_Lambda(RebuildHandler);
		}
		return SNullWidget::NullWidget;
	}

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)
	{
		AtlasInfo = InArgs._AtlasInfo;

		FSuperRowType::Construct(FSuperRowType::FArguments().Padding(1),
			InOwnerTableView);
	}

	AtlasInfoPtr AtlasInfo;
	TSharedPtr<SEditableTextBox> AtlasTextBox;
};

FDelegateHandle FCohtmlAtlasManagerCallbacks::ContentBrowserPathExtenderDelegateHandle;
FDelegateHandle FCohtmlAtlasManagerCallbacks::OnAssetRemovedDelegateHandle;
FDelegateHandle FCohtmlAtlasManagerCallbacks::OnAssetRenamedDelegateHandle;
FDelegateHandle FCohtmlAtlasManagerCallbacks::OnAssetSavedDelegateHandle;
FDelegateHandle FCohtmlAtlasManagerCallbacks::OnLaunchCompletedDelegateHandle;
FDelegateHandle FCohtmlAtlasManagerCallbacks::OnLaunchCanceledDelegateHandle;

void FCohtmlAtlasManagerCallbacks::RegisterCallbacks()
{
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

	// Add a "Add to atlas" context menu entry for folders
	TArray<FContentBrowserMenuExtender_SelectedPaths>& CBPathExtenderDelegates = ContentBrowserModule.GetAllPathViewContextMenuExtenders();
	CBPathExtenderDelegates.Add(FContentBrowserMenuExtender_SelectedPaths::CreateStatic(&FCohtmlAtlasManagerCallbacks::OnExtendContentBrowserPathSelectionMenu));
	ContentBrowserPathExtenderDelegateHandle = CBPathExtenderDelegates.Last().GetHandle();

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::GetModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	OnAssetRemovedDelegateHandle = AssetRegistryModule.Get().OnAssetRemoved().AddStatic(&FCohtmlAtlasManagerCallbacks::OnAssetRemoved);
	OnAssetRenamedDelegateHandle = AssetRegistryModule.Get().OnAssetRenamed().AddStatic(&FCohtmlAtlasManagerCallbacks::OnAssetRenamed);

	OnAssetSavedDelegateHandle = UPackage::PackageSavedEvent.AddStatic(&FCohtmlAtlasManagerCallbacks::OnAssetSaved);
}

void FCohtmlAtlasManagerCallbacks::UnregisterCallbacks()
{
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	TArray<FContentBrowserMenuExtender_SelectedPaths>& CBPathExtenderDelegates = ContentBrowserModule.GetAllPathViewContextMenuExtenders();
	CBPathExtenderDelegates.RemoveAll([](const FContentBrowserMenuExtender_SelectedPaths& Delegate) { return Delegate.GetHandle() == ContentBrowserPathExtenderDelegateHandle; });

	// Unregister the property modification handler
	UPackage::PackageSavedEvent.Remove(OnAssetSavedDelegateHandle);
}

void FCohtmlAtlasManagerCallbacks::OnAddAtlasButtonClicked()
{
	FCohtmlAtlasManager::Get().CreateAtlas();
}

const FSlateBrush* FCohtmlAtlasManagerCallbacks::OnGetAtlasPreviewImageBrush()
{
	return FCohtmlAtlasManager::Get().GetPreviewImage();
}

TSharedRef<ITableRow> FCohtmlAtlasManagerCallbacks::OnGenerateRowForAtlasViewer(AtlasInfoPtr AtlasInfo, const TSharedRef<STableViewBase>& OwnerTable)
{
	return FCohtmlAtlasManager::Get().GenerateRow(AtlasInfo, OwnerTable);
}

void FCohtmlAtlasManagerCallbacks::OnAssetSaved(const FString& PackageFileName, UObject* Outer)
{
	// The cook server re-saves assets which triggers constant atlas rebuilds.
	// The only meaningful re-save could come from manual changes, so when
	// running the editor as a commandlet (i.e. as a command line tool, without
	// any GUI) we don't want to do anything
	if (IsRunningCommandlet())
	{
		return;
	}

	if (!FCohtmlAtlasManager::Get().GetHandleOnAssetSaved())
	{
		return;
	}

	TArray<UObject*> ContainedObjects;
	GetObjectsWithOuter(Outer, ContainedObjects);
	for (UObject* Object : ContainedObjects)
	{
		UTexture2D* Texture = Cast<UTexture2D>(Object);

		if (Texture)
		{
			FString AssetPath = Texture->GetPathName();
			if (AssetPath.Contains("/Atlases/"))
			{
				continue;
			}

			FString AtlasPath = FCohtmlAtlasManager::Get().GetAssetAtlasPath(AssetPath);
			if (!AtlasPath.IsEmpty())
			{
				// TODO: Find a way to detect which PackageSavedEvent notifications
				// come from the cook server and which come from us
				//
				// When launching from the Unreal Editor, we want to defer the
				// rebuilding for after the launch process finishes to avoid
				// the constant rebuilding.
				if (FCohtmlAtlasManager::Get().IsLaunchingFromEditor())
				{
					FCohtmlAtlasManager::Get().ScheduleAtlasForRebuild(AtlasPath);
				}
				else
				{
					FCohtmlAtlasManager::Get().AtlasMetaData.SetAtlasNeedsRebuild(AtlasPath, true);
					FCohtmlAtlasManager::Get().RebuildStaleAtlases();
				}
			}
		}
	}
}

void FCohtmlAtlasManagerCallbacks::OnAssetRemoved(const FAssetData& AssetData)
{
	if (!FCohtmlAtlasManager::Get().GetHandleOnAssetRemoved())
	{
		return;
	}

	FString AssetPath = AssetData.ObjectPath.ToString();
	if (AssetPath.Contains("/Atlases/"))
	{
		FCohtmlAtlasManager::Get().RemoveAtlas(AssetPath);
	}
	else
	{
		FString AtlasPath = FCohtmlAtlasManager::Get().GetAssetAtlasPath(AssetPath);
		if (!AtlasPath.IsEmpty())
		{
			FCohtmlAtlasManager::Get().RemoveAtlasedAsset(AssetPath, AtlasPath);
			FCohtmlAtlasManager::Get().RebuildAtlas(AtlasPath);
		}
	}
}

void FCohtmlAtlasManagerCallbacks::OnAssetRenamed(const FAssetData& RenamedAssetData, const FString& OldObjectPath)
{
	FString AssetPath = RenamedAssetData.ObjectPath.ToString();
	if (OldObjectPath.Contains("/Atlases/"))
	{
		FCohtmlAtlasManager::Get().RenameAtlas(OldObjectPath, AssetPath);
	}
	else
	{
		FString AtlasPath = FCohtmlAtlasManager::Get().GetAssetAtlasPath(OldObjectPath);
		if (!AtlasPath.IsEmpty())
		{
			FCohtmlAtlasManager::Get().RenameAtlasedAsset(OldObjectPath, AssetPath);
		}
	}
}

void FCohtmlAtlasManagerCallbacks::OnAddAssetsToAtlas(FString AtlasPath, TArray<FAssetData> AssetsToAtlas)
{
	TSet<UTexture2D*> TexturesToAtlas;
	for (const auto& Asset : AssetsToAtlas)
	{
		UTexture2D* Texture = Cast<UTexture2D>(Asset.GetAsset());
		if (Texture)
		{
			TexturesToAtlas.Add(Texture);
		}
	}
	FCohtmlAtlasManager::Get().BatchTexturesInAtlas(AtlasPath, TexturesToAtlas);
}

void FCohtmlAtlasManagerCallbacks::OnAddAssetsToNewAtlas(TArray<FAssetData> AssetsToAtlas)
{
	TSet<UTexture2D*> TexturesToAtlas;
	for (const auto& Asset : AssetsToAtlas)
	{
		UTexture2D* Texture = Cast<UTexture2D>(Asset.GetAsset());
		if (Texture)
		{
			TexturesToAtlas.Add(Texture);
		}
	}
	FCohtmlAtlasManager::Get().BatchTexturesInNewAtlas(TexturesToAtlas);
}

void FCohtmlAtlasManagerCallbacks::OnLaunchCompleted(bool, double, int32)
{
	AsyncTask(ENamedThreads::GameThread, []() {
		FCohtmlAtlasManager::Get().RebuildStaleAtlases();
	});
}

void FCohtmlAtlasManagerCallbacks::OnLaunchCanceled(double)
{
	AsyncTask(ENamedThreads::GameThread, []() {
		FCohtmlAtlasManager::Get().RebuildStaleAtlases();
	});
}

FCohtmlAtlasManager::FCohtmlAtlasManager()
	: AtlasRebuildIntervalSeconds(0.5f)
	, bShouldHandleOnAssetSaved(true)
	, bShouldHandleOnAssetRemoved(true)
{
	if (!IsRunningCommandlet())
	{
		AtlasMetaData.LoadAtlasMetaData();
	}
	AtlasBuilder = MakeUnique<FCohtmlAtlasBuilder>();
}

FCohtmlAtlasManager& FCohtmlAtlasManager::Get()
{
	static FCohtmlAtlasManager Singleton;
	return Singleton;
}

bool FCohtmlAtlasManager::CreateAtlas()
{
	if (!AtlasBuilder->BuildNewEmptyAtlas(AtlasMetaData))
	{
		return false;
	}
	AtlasMetaData.SerializeAtlasMetaData();
	RefreshAtlasViewerWidget();

	return true;
}

bool FCohtmlAtlasManager::RebuildAtlas(const FString& AtlasToRebuild)
{
	if (!AtlasMetaData.AtlasDetails.Contains(AtlasToRebuild))
	{
		return false;
	}

	AtlasMetaData.RemoveAllAssetsFromAtlas(AtlasToRebuild);

	if (!AtlasBuilder->RebuildAtlas(AtlasToRebuild, AtlasMetaData))
	{
		return false;
	}
	AtlasMetaData.SerializeAtlasMetaData();
	RefreshAtlasViewerWidget();
	return true;
}

bool FCohtmlAtlasManager::BatchTexturesInNewAtlas(const TSet<UTexture2D*>& Textures)
{
	if (!AtlasBuilder->BuildNewAtlasFromTextures(Textures, AtlasMetaData))
	{
		return false;
	}
	AtlasMetaData.SerializeAtlasMetaData();
	RefreshAtlasViewerWidget();

	return true;
}

bool FCohtmlAtlasManager::BatchTexturesInAtlas(FString AtlasPath, const TSet<UTexture2D*>& Textures)
{
	if (!AtlasBuilder->RebuildAtlasWithAddedTextures(AtlasPath, Textures, AtlasMetaData))
	{
		return false;
	}
	AtlasMetaData.SerializeAtlasMetaData();
	RefreshAtlasViewerWidget();
	return true;
}

void FCohtmlAtlasManager::RenameAtlas(const FString& OldAtlasPath, const FString& NewAtlasPath)
{
	auto ContainedTexturesForAtlas = AtlasMetaData.AtlasContainedTextures.Find(OldAtlasPath);
	if (ContainedTexturesForAtlas)
	{
		AtlasMetaData.AtlasContainedTextures.Remove(OldAtlasPath);
		AtlasMetaData.AtlasContainedTextures.Add(NewAtlasPath, *ContainedTexturesForAtlas);
	}

	auto AtlasDetails = AtlasMetaData.AtlasDetails.Find(OldAtlasPath);
	if (AtlasDetails)
	{
		AtlasMetaData.AtlasDetails.Remove(OldAtlasPath);
		(*AtlasDetails)->AtlasPath = NewAtlasPath;
		AtlasMetaData.AtlasDetails.Add(NewAtlasPath, *AtlasDetails);
	}

	AtlasMetaData.RenameAtlas(OldAtlasPath, NewAtlasPath);

	RefreshAtlasViewerWidget();
	if (AtlasPreviewWindow.IsValid() && AtlasPreviewWindow.Pin()->GetTitle().ToString().Contains(OldAtlasPath))
	{
		AtlasPreviewWindow.Pin()->SetTitle(FText::FromString("Preview atlas - " + NewAtlasPath));
	}

	AtlasMetaData.SerializeAtlasMetaData();
}

void FCohtmlAtlasManager::RenameAtlasedAsset(const FString& OldAssetName, const FString& NewAssetName)
{
	AtlasMetaData.RenameAtlasedAsset(OldAssetName, NewAssetName);

	AtlasMetaData.SerializeAtlasMetaData();
}

void FCohtmlAtlasManager::RemoveAtlas(const FString& AtlasPath)
{
	AtlasMetaData.AtlasContainedTextures.Remove(AtlasPath);
	AtlasMetaData.AtlasDetails.Remove(AtlasPath);

	AtlasMetaData.RemoveAtlas(AtlasPath);

	RefreshAtlasViewerWidget();
	CloseAtlasPreviewWindow(AtlasPath);

	// If someone has deleted the entire Atlases folder, we want to exit right after
	// updating the metadata held in memory and before serializing it because that
	// will recreate the folder
	FString FullAtlasesPath = FPaths::ConvertRelativePathToFull(CohtmlGetProjectContentDir() / "Atlases");
	if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*FullAtlasesPath))
	{
		return;
	}

	AtlasMetaData.SerializeAtlasMetaData();
}

void FCohtmlAtlasManager::RemoveAtlasedAsset(const FString& AssetName, const FString& AtlasPath)
{
	for (UTexture2D* Texture : AtlasMetaData.AtlasContainedTextures[AtlasPath]->Textures)
	{
		if (Texture && Texture->GetPathName() == AssetName)
		{
			AtlasMetaData.AtlasContainedTextures[AtlasPath]->Textures.Remove(Texture);
			break;
		}
	}

	AtlasMetaData.RemoveAtlasedAsset(AssetName);

	AtlasMetaData.SerializeAtlasMetaData();
}

bool FCohtmlAtlasManager::GetHandleOnAssetSaved()
{
	return bShouldHandleOnAssetSaved;
}

bool FCohtmlAtlasManager::GetHandleOnAssetRemoved()
{
	return bShouldHandleOnAssetRemoved;
}

void FCohtmlAtlasManager::SetHandleOnAssetSaved(bool ShouldHandleOnAssetSaved)
{
	bShouldHandleOnAssetSaved = ShouldHandleOnAssetSaved;
}

void FCohtmlAtlasManager::SetHandleOnAssetRemoved(bool ShouldHandleOnAssetRemoved)
{
	bShouldHandleOnAssetRemoved = ShouldHandleOnAssetRemoved;
}

void FCohtmlAtlasManager::SetAutoConfirmMessageBoxes(bool ShouldAutoConfirmMessageBoxes)
{
	AtlasBuilder->SetAutoConfirmMessageBoxes(ShouldAutoConfirmMessageBoxes);
}

void FCohtmlAtlasManager::LaunchAtlasViewer()
{
	if (AtlasViewerWindow.IsValid())
	{
		FSlateApplication::Get().SetUserFocus(0, AtlasViewerWindow.Pin());
		return;
	}

	TSharedRef<SWidget> AddButton = PropertyCustomizationHelpers::MakeAddButton(FSimpleDelegate::CreateStatic(&FCohtmlAtlasManagerCallbacks::OnAddAtlasButtonClicked),
		LOCTEXT("AddAtlasButtonToolTip", "Adds a new atlas"), /*IsEnabled=*/true);

	auto NewWindow = SNew(SWindow)
		.Title(LOCTEXT("AtlasViewerDialog", "Manage the built atlases"))
		.ClientSize(FVector2D(800, 400))
		.SupportsMaximize(false)
		.SupportsMinimize(false)
		[
			SAssignNew(AtlasTableWidget, SListView<AtlasInfoPtr>)
			.ItemHeight(24)
			.SelectionMode(ESelectionMode::Single)
			.ListItemsSource(&AtlasMetaData.GetAtlases())
			.OnGenerateRow_Static(&FCohtmlAtlasManagerCallbacks::OnGenerateRowForAtlasViewer)
			.HeaderRow
			(
				SNew(SHeaderRow)
				+ SHeaderRow::Column("AtlasName")
					.DefaultLabel(FText::FromString("Atlas Name"))
					.HAlignHeader(EHorizontalAlignment::HAlign_Left)
					.HAlignCell(EHorizontalAlignment::HAlign_Left)
					.ToolTipText(FText::FromString("The name of the texture atlas"))
					.FillWidth(0.64)
				+ SHeaderRow::Column("PreviewButton")
					.DefaultLabel(FText::FromString(""))
					.HAlignHeader(EHorizontalAlignment::HAlign_Center)
					.HAlignCell(EHorizontalAlignment::HAlign_Center)
					.ToolTipText(FText::FromString("Open atlas preview widget"))
					.FillWidth(0.12)
				+ SHeaderRow::Column("DeleteButton")
					.DefaultLabel(FText::FromString(""))
					.HAlignHeader(EHorizontalAlignment::HAlign_Center)
					.HAlignCell(EHorizontalAlignment::HAlign_Center)
					.ToolTipText(FText::FromString("Delete atlas"))
					.FillWidth(0.12)
				+ SHeaderRow::Column("NeedsRebuild")
					.DefaultLabel(FText::FromString(""))
					.HAlignHeader(EHorizontalAlignment::HAlign_Center)
					.HAlignCell(EHorizontalAlignment::HAlign_Center)
					.ToolTipText(FText::FromString("Add new atlas"))
					.FillWidth(0.12)
					.HeaderContent()
					[
						AddButton
					]
			)
		];

	IMainFrameModule& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));

	if (MainFrameModule.GetParentWindow().IsValid())
	{
		FSlateApplication::Get().AddWindowAsNativeChild(NewWindow, MainFrameModule.GetParentWindow().ToSharedRef());
	}
	else
	{
		FSlateApplication::Get().AddWindow(NewWindow);
	}
	AtlasViewerWindow = NewWindow;
}

void FCohtmlAtlasManager::LaunchAtlasPreview(const FString& AtlasPath)
{
	if (AtlasPreviewWindow.IsValid())
	{
		FSlateApplication::Get().SetUserFocus(0, AtlasPreviewWindow.Pin());
		return;
	}

	UTexture2D* AtlasImage = LoadObject<UTexture2D>(nullptr, *AtlasPath, nullptr, LOAD_None, nullptr);
	const float MaxSize = FMath::Max(AtlasImage->GetSizeX(), AtlasImage->GetSizeY());
	const float AspectRatioX = AtlasImage->GetSizeX() / MaxSize;
	const float AspectRatioY = AtlasImage->GetSizeY() / MaxSize;
#if defined(COHTML_UE4_419_SUPPORT)
	if (PreviewImageBrush.IsValid())
	{
		PreviewImageBrush->SetResourceObject(nullptr);
	}
	PreviewImageBrush = MakeShareable(new FSlateDynamicImageBrush(AtlasImage, FVector2D(512 * AspectRatioX, 512 * AspectRatioY), FName("AtlasImage")));
#else
	PreviewImageBrush = FDeferredCleanupSlateBrush::CreateBrush(AtlasImage, FVector2D(512 * AspectRatioX, 512 * AspectRatioY));
#endif

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs Args;
	Args.bHideSelectionTip = true;
	Args.bAllowSearch = false;

	TSharedRef<IDetailsView> AtlasDetailsView = PropertyEditorModule.CreateDetailView(Args);

	auto AtlasDetailsViewChangedHandler = [AtlasPath, this](const FPropertyChangedEvent& PropertyChangedEvent) {
		FName PropertyName = PropertyChangedEvent.GetPropertyName();
		if (PropertyName.IsEqual("MaxAtlasWidth"))
		{
			AtlasMetaData.AtlasDetails[*AtlasPath]->MaxAtlasWidth = FMath::Min<uint32>(FMath::RoundUpToPowerOfTwo(AtlasMetaData.AtlasDetails[*AtlasPath]->MaxAtlasWidth), FTextureAtlasMetaData::GDefaultMaxAtlasSize);
			AtlasMetaData.AtlasDetails[*AtlasPath]->MaxTextureWidth = FMath::Min(AtlasMetaData.AtlasDetails[*AtlasPath]->MaxTextureWidth, AtlasMetaData.AtlasDetails[*AtlasPath]->MaxAtlasWidth);
		}
		else if (PropertyName.IsEqual("MaxAtlasHeight"))
		{
			AtlasMetaData.AtlasDetails[*AtlasPath]->MaxAtlasHeight = FMath::Min<uint32>(FMath::RoundUpToPowerOfTwo(AtlasMetaData.AtlasDetails[*AtlasPath]->MaxAtlasHeight), FTextureAtlasMetaData::GDefaultMaxAtlasSize);
			AtlasMetaData.AtlasDetails[*AtlasPath]->MaxTextureHeight = FMath::Min(AtlasMetaData.AtlasDetails[*AtlasPath]->MaxTextureHeight, AtlasMetaData.AtlasDetails[*AtlasPath]->MaxAtlasHeight);
		}
		else if (PropertyName.IsEqual("MaxTextureWidth"))
		{
			AtlasMetaData.AtlasDetails[*AtlasPath]->MaxTextureWidth = FMath::Min(AtlasMetaData.AtlasDetails[*AtlasPath]->MaxTextureWidth, AtlasMetaData.AtlasDetails[*AtlasPath]->MaxAtlasWidth);
		}
		else if (PropertyName.IsEqual("MaxTextureHeight"))
		{
			AtlasMetaData.AtlasDetails[*AtlasPath]->MaxTextureHeight = FMath::Min(AtlasMetaData.AtlasDetails[*AtlasPath]->MaxTextureHeight, AtlasMetaData.AtlasDetails[*AtlasPath]->MaxAtlasHeight);
		}

		// Do not rebuild if we receive a notification about any of the read-only properties
		// or if we're notified for a change more than once in a single Tick (this can
		// happen if any other window is created and consumes the focus i.e. a dialog
		// that informs the user that some textures are about to be dropped from the atlas
		// or the progress bar displayed by UE4 when saving a package after rebuilding an
		// atlas).
		if (!PropertyName.IsEqual("AtlasPath") &&
			!PropertyName.IsEqual("Width") &&
			!PropertyName.IsEqual("Height") &&
			!PropertyName.IsEqual("PixelFormat") &&
			!bIsCurrentlyUpdatingProperty)
		{
			bIsCurrentlyUpdatingProperty = true;
			// We need to reset the focus after rebuilding the atlas because saving the
			// package displays a progress bar which appears to be consuming the focus,
			// leading to uneditable fields in the details view
			auto FocusedWidget = FSlateApplication::Get().GetUserFocusedWidget(0);
			FCohtmlAtlasManager::Get().RebuildAtlas(AtlasPath);
			FWidgetPath PathToFocusedWidget;
			FSlateApplication::Get().FindPathToWidget(FocusedWidget.ToSharedRef(), PathToFocusedWidget);
			FSlateApplication::Get().SetAllUserFocus(PathToFocusedWidget, EFocusCause::SetDirectly);
			bIsCurrentlyUpdatingProperty = false;
		}
	};

	AtlasDetailsView->SetObject(AtlasMetaData.AtlasDetails[*AtlasPath]);
	AtlasDetailsView->OnFinishedChangingProperties().AddLambda(AtlasDetailsViewChangedHandler);

	TSharedRef<IDetailsView> AtlasContainedTexturesView = PropertyEditorModule.CreateDetailView(Args);

	auto AtlasTexturesViewChangedHandler = [AtlasPath, this](const FPropertyChangedEvent& PropertyChangedEvent) {
		if (PropertyChangedEvent.ChangeType != EPropertyChangeType::ArrayAdd)
		{
			FCohtmlAtlasManager::Get().RebuildAtlas(AtlasPath);
		}
	};

	AtlasContainedTexturesView->SetObject(AtlasMetaData.AtlasContainedTextures[*AtlasPath]);
	AtlasContainedTexturesView->OnFinishedChangingProperties().AddLambda(AtlasTexturesViewChangedHandler);

	auto NewWindow = SNew(SWindow)
		.Title(FText::FromString("Preview atlas - " + AtlasPath))
		.ClientSize(FVector2D(1000, 950))
		.SupportsMaximize(false)
		.SupportsMinimize(false)
		[
			SNew(SGridPanel)
			.FillColumn(0, 0.5f)
			.FillColumn(1, 0.5f)
			.FillRow(1, 1.0f)
			+ SGridPanel::Slot(0, 0)
				.Padding(8.0f, 0.0f, 10.0f, 0.0f)
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Center)
				[
					SNew(SImage)
					.Image_Static(&FCohtmlAtlasManagerCallbacks::OnGetAtlasPreviewImageBrush)
					.ForceVolatile(true)
				]
			+ SGridPanel::Slot(1, 0)
				.Padding(10.0f, 0.0f, 8.0f, 0.0f)
				.VAlign(VAlign_Top)
				[
					AtlasDetailsView
				]
			+ SGridPanel::Slot(0, 1)
				.Padding(0.0f, 0.0f, 0.0f, 20.0f)
				.VAlign(VAlign_Top)
				.HAlign(HAlign_Fill)
				.ColumnSpan(2)
				[
					AtlasContainedTexturesView
				]
		];

	IMainFrameModule& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));

	if (MainFrameModule.GetParentWindow().IsValid())
	{
		FSlateApplication::Get().AddWindowAsNativeChild(NewWindow, MainFrameModule.GetParentWindow().ToSharedRef());
	}
	else
	{
		FSlateApplication::Get().AddWindow(NewWindow);
	}
	AtlasPreviewWindow = NewWindow;
}

void FCohtmlAtlasManager::RefreshAtlasViewerWidget()
{
	if (AtlasTableWidget.IsValid() && AtlasViewerWindow.IsValid())
	{
		AtlasTableWidget.Pin()->RequestListRefresh();
		AtlasMetaData.SerializeAtlasMetaData();
	}
}

void FCohtmlAtlasManager::CloseAtlasPreviewWindow(const FString& AtlasPath)
{
	if (AtlasPreviewWindow.IsValid() && AtlasPreviewWindow.Pin()->GetTitle().ToString().Contains(AtlasPath))
	{
		AtlasPreviewWindow.Pin()->RequestDestroyWindow();
	}
}

void FCohtmlAtlasManagerCallbacks::OnCreateAtlasListContextSubmenu(FMenuBuilder& MenuBuilder, TArray<FString> SelectedPaths, bool AreFolders)
{
	const TArray<AtlasInfoPtr> Atlases = FCohtmlAtlasManager::Get().GetAtlases();
	FAssetRegistryModule& AssetModule = FModuleManager::GetModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	TArray<FAssetData> OutAssetData;
	if (AreFolders)
	{
		for (const auto& Path : SelectedPaths)
		{
			AssetModule.Get().GetAssetsByPath(FName(*Path), OutAssetData, true, false);
		}
	}
	else
	{
		for (const auto& AssetPath : SelectedPaths)
		{
			OutAssetData.Add(AssetModule.Get().GetAssetByObjectPath(FName(*AssetPath)));
		}
	}

	MenuBuilder.AddMenuEntry(
		LOCTEXT("CohtmlCreateNewAtlas", "New Atlas"),
		LOCTEXT("CohtmlCreateNewAtlasToolTip", "Add assets to a new " COHTML_PRODUCT " atlas"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateStatic(&FCohtmlAtlasManagerCallbacks::OnAddAssetsToNewAtlas, OutAssetData))
	);

	for (auto& AtlasInfo : Atlases)
	{
		MenuBuilder.AddMenuEntry(
			FText::FromString(AtlasInfo->AtlasPath),
			LOCTEXT("CohtmlCreateNewAtlasToolTip", "Add assets to the specified atlas"),
			FSlateIcon(),
			FUIAction(FExecuteAction::CreateStatic(&FCohtmlAtlasManagerCallbacks::OnAddAssetsToAtlas, AtlasInfo->AtlasPath, OutAssetData))
		);
	}
}

void FCohtmlAtlasManagerCallbacks::OnCreateAtlasAssetContextMenu(FMenuBuilder& MenuBuilder, TArray<FString> SelectedPaths)
{
	for (const auto& Path : SelectedPaths)
	{
		if (Path.Contains("/Game/Atlases"))
		{
			return;
		}
	}
	MenuBuilder.BeginSection("CohtmlAtlasOperations", LOCTEXT("CohtmlAtlasMenuHeading", "Atlas Operations"));
	{
		MenuBuilder.AddSubMenu(
			LOCTEXT("CohtmlAtlasAssetsInFolder", "Atlas assets in folder"),
			LOCTEXT("CohtmlAtlasAssetsInFolderToolTip", "Adds the textures in this folder to a " COHTML_PRODUCT " atlas"),
			FNewMenuDelegate::CreateStatic(&FCohtmlAtlasManagerCallbacks::OnCreateAtlasListContextSubmenu, SelectedPaths, /*AreFolders=*/true)
		);
	}
	MenuBuilder.EndSection();
}

TSharedRef<FExtender> FCohtmlAtlasManagerCallbacks::OnExtendContentBrowserPathSelectionMenu(const TArray<FString>& SelectedPaths)
{
	TSharedRef<FExtender> Extender(new FExtender());

	Extender->AddMenuExtension(
		"PathContextBulkOperations",
		EExtensionHook::Before,
		nullptr,
		FMenuExtensionDelegate::CreateStatic(&FCohtmlAtlasManagerCallbacks::OnCreateAtlasAssetContextMenu, SelectedPaths));

	return Extender;
}

FString FCohtmlAtlasManager::GetAssetAtlasPath(const FString& AssetName)
{
	auto TextureAssetInfo = AtlasMetaData.GetAtlasedTextures().Find(AssetName);
	return TextureAssetInfo ? TextureAssetInfo->AtlasPath : "";
}

bool FCohtmlAtlasManager::IsLaunchingFromEditor() const
{
	if (!GEditor || !GEditor->LauncherWorker.IsValid())
	{
		return false;
	}

	ELauncherWorkerStatus::Type Status = GEditor->LauncherWorker->GetStatus();
	return Status == ELauncherWorkerStatus::Busy || Status == ELauncherWorkerStatus::Canceling;
}

void FCohtmlAtlasManager::ScheduleAtlasForRebuild(const FString& AtlasPath)
{
	AtlasMetaData.SetAtlasNeedsRebuild(AtlasPath, true);

	if (!GEditor || !GEditor->LauncherWorker.IsValid())
	{
		return;
	}

	ILauncherWorkerPtr Launcher = GEditor->LauncherWorker;
	Launcher->OnCompleted().Remove(FCohtmlAtlasManagerCallbacks::OnLaunchCompletedDelegateHandle);
	FCohtmlAtlasManagerCallbacks::OnLaunchCompletedDelegateHandle = Launcher->OnCompleted()
		.AddStatic(FCohtmlAtlasManagerCallbacks::OnLaunchCompleted);

	Launcher->OnCanceled().Remove(FCohtmlAtlasManagerCallbacks::OnLaunchCanceledDelegateHandle);
	FCohtmlAtlasManagerCallbacks::OnLaunchCanceledDelegateHandle = Launcher->OnCanceled()
		.AddStatic(FCohtmlAtlasManagerCallbacks::OnLaunchCanceled);
}

void FCohtmlAtlasManager::RebuildStaleAtlases()
{
	auto& Atlases = AtlasMetaData.GetAtlases();
	for (auto AtlasIndex = 0; AtlasIndex < Atlases.Num(); AtlasIndex++)
	{
		if (Atlases[AtlasIndex]->bNeedsRebuild && GEditor)
		{
			FString AtlasPath = Atlases[AtlasIndex]->AtlasPath;
			auto TimerManager = GEditor->GetTimerManager();
			TimerManager->SetTimer(Atlases[AtlasIndex]->RebuildTimerHandle, [AtlasPath, this]() {
				RebuildAtlas(AtlasPath);
				AtlasMetaData.SetAtlasNeedsRebuild(AtlasPath, false);
			}, AtlasRebuildIntervalSeconds + AtlasIndex * AtlasRebuildIntervalSeconds, false);
		}
	}
}

const TArray<AtlasInfoPtr>& FCohtmlAtlasManager::GetAtlases()
{
	return AtlasMetaData.GetAtlases();
}

void FCohtmlAtlasManager::ReloadAtlasMetaData()
{
	AtlasMetaData.LoadAtlasMetaData();
}

const FTextureAtlasMetaData& FCohtmlAtlasManager::GetAtlasMetaData()
{
	return AtlasMetaData;
}

TSharedRef<ITableRow> FCohtmlAtlasManager::GenerateRow(AtlasInfoPtr AtlasInfo, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(SAtlasInfoItem, OwnerTable)
			.AtlasInfo(AtlasInfo);
}

const FSlateBrush* FCohtmlAtlasManager::GetPreviewImage() const
{
#if defined(COHTML_UE4_419_SUPPORT)
	return PreviewImageBrush.Get();
#else
	return PreviewImageBrush->GetSlateBrush();
#endif
}
#undef LOCTEXT_NAMESPACE