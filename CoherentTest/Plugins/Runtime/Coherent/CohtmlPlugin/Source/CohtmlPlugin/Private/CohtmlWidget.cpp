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
#include "CohtmlWidget.h"

#include "CohtmlSettings.h"
#include "CohtmlInputHelpers.h"
#include <cohtml/View.h>
#include <cohtml/Binding/Binding.h>
#include <cohtml/Binding/EventHandler.h>

#include "CohtmlFStringBinder.h"
#include "CohtmlSystemHolder.h"

#include "CohtmlAudioWrapper.inl"

#include <Widgets/SViewport.h>

template TCohtmlAudioWrapper<AActor>::TCohtmlAudioWrapper();
template TCohtmlAudioWrapper<AActor>::~TCohtmlAudioWrapper();

UCohtmlWidget::UCohtmlWidget(const FObjectInitializer& PCIP)
	: Super(PCIP)
	, CachedView(nullptr)
{
	bReceiveInput = true;
	bGammaCorrectedMaterial = true;
	bEnableComplexCSSSupport = true;
	LastFocusedWidgetBeforeUI.Reset();
}

UCohtmlWidget::~UCohtmlWidget()
{
	if (Listener.IsValid())
	{
		Listener->OwnerDestroyed();
	}
}

namespace
{

cohtml::ViewSettings CreateViewSettings(UCohtmlWidget* Widget)
{
	cohtml::ViewSettings Info;
	Info.EnableComplexCSSSelectorsStyling = Widget->bEnableComplexCSSSupport;
	return Info;
}

}

TSharedRef<SWidget> UCohtmlWidget::RebuildWidget()
{
	if (!CoherentWidget.IsValid())
	{
		if (auto World = GetWorld())
		{
			UCohtmlBaseComponent::CreateSystemIfNecessary(World);
		}

		Listener = TSharedPtr<TCohtmlViewListener<UCohtmlWidget>>(new TCohtmlViewListener<UCohtmlWidget>(this));

		cohtml::ViewSettings Info = CreateViewSettings(this);
		CoherentWidget = SNew(SCohtmlWidget);

		CoherentWidget->CreateView(Info, URL, Listener, Listener);

		LastSavedViewSettings = Info;

		LastFocusedWidgetBeforeUI.Reset();
	}
	return CoherentWidget.ToSharedRef();
}

#if WITH_EDITOR
const FText UCohtmlWidget::GetPaletteCategory()
{
	static FText Category = FText::FromString(FString(TEXT(COHTML_PRODUCT)));
	return Category;
}
#endif


void UCohtmlWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (CoherentWidget.IsValid())
	{
		if (CoherentWidget->GetFilter() != Filter)
		{
			CoherentWidget->SetFilter(Filter);
		}
		CoherentWidget->SetReceiveInput(bReceiveInput);
		CoherentWidget->SetIsMaterialGammaCorrected(bGammaCorrectedMaterial);
		CoherentWidget->SetInputPropagationBehaviour(InputPropagationBehaviour);

		auto View = CoherentWidget->GetView();
		if (View)
		{
			if (!URL.IsEmpty())
			{
				View->LoadURL(TCHAR_TO_UTF8(*URL));
			}
		}
	}
}

// Base Component interface

bool UCohtmlWidget::IsReadyToCreateView() const
{
	return FCohtmlSystemHolder::IsReady();
}

void UCohtmlWidget::BeginDestroy()
{
	Super::BeginDestroy();
	if (CoherentWidget.IsValid())
	{
		CachedView = CoherentWidget->GetView();
	}
}

void UCohtmlWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	CoherentWidget.Reset();
}

bool UCohtmlWidget::HasRequestedView() const
{
	if (CoherentWidget.IsValid())
	{
		return CoherentWidget->HasRequestedView();
	}
	return false;
}

void UCohtmlWidget::ShowPaintRects(bool show)
{
	if (GetView())
		GetView()->ShowPaintRectangles(show);
}

void UCohtmlWidget::Load(const FString& Path)
{
	if (!CoherentWidget.IsValid())
	{
		URL = Path;
	}
	else if (CoherentWidget->GetView())
	{
		CoherentWidget->GetView()->LoadURL(TCHAR_TO_UTF8(*Path));
	}
	else
	{
		CoherentWidget->RecreateView(LastSavedViewSettings, Path, Listener, Listener);
	}
}

void UCohtmlWidget::Reload()
{
	if (GetView())
	{
		GetView()->Reload();
	}
}

UTextureRenderTarget2D* UCohtmlWidget::GetRenderTexture() const
{
	if (CoherentWidget.IsValid())
	{
		return CoherentWidget->GetRenderTexture();
	}
	return nullptr;
}

void UCohtmlWidget::OnCursorChanged(cohtml::CursorTypes::Cursors CursorType)
{
	if (CoherentWidget.IsValid())
	{
		CoherentWidget->CurrentMouseCursor =
			CohtmlInputHelpers::TranslateCurrentCohtmlMouseCursor(CursorType);
	}
}

void UCohtmlWidget::SetReadyForBindings()
{
	// Do nothing if we were already destroyed. May happen in async if the view
	// is destroyed before its first layout and async event processing happens only in the destructor.
	if (!HasAnyFlags(RF_BeginDestroyed))
	{
		CoherentWidget->GetView()->BindCall("ScriptingReady", cohtml::MakeHandler(
			&ScriptingReady,
			&FCohtmlScriptingReady::Broadcast));
	}
}

bool UCohtmlWidget::IsReadyForBindings() const
{
	auto View = GetView();
	return View ? View->IsReadyForBindings() : false;
}

UCohtmlJSEvent* UCohtmlWidget::CreateJSEvent()
{
	return NewObject<UCohtmlJSEvent>();
}

void UCohtmlWidget::TriggerJSEvent(const FString& name, UCohtmlJSEvent* eventData) const
{
	if (!IsReadyForBindings())
		return;

	CohtmlEventHelpers::TriggerJSEvent(name, eventData, GetView());
}

void UCohtmlWidget::CreateDataModelFromObject(const FString& Name, UObject* Model)
{
	if (!IsReadyForBindings())
	{
		COHTML_UE_LOG(Warning, TEXT("CreateDataModelFromObject is called before the system is ready for binding."));
		return;
	}
	CohtmlDataBindingHelpers::CreateModel(GetView(), Name, Model, Model->GetClass());
}

void UCohtmlWidget::CreateDataModelFromStruct(const FString& Name, const UStructProperty* Arg)
{
	// This is only a stub. It should never be called, there's a custom thunk implementation, instead.
	check(0);
}

void UCohtmlWidget::UpdateWholeDataModelFromObject(UObject* Model) const
{
	if (!IsReadyForBindings())
	{
		COHTML_UE_LOG(Warning, TEXT("UpdateWholeDataModelFromObject is called before the system is ready for binding."));
		return;
	}
	CohtmlDataBindingHelpers::UpdateWholeModel(GetView(), Model, Model->GetClass());
}

void UCohtmlWidget::UpdateWholeDataModelFromStruct(const UStructProperty* Struct) const
{
	// This is only a stub. It should never be called, there's a custom thunk implementation, instead.
	check(0);
}

void UCohtmlWidget::SynchronizeModels() const
{
	if (!IsReadyForBindings())
	{
		COHTML_UE_LOG(Warning, TEXT("SynchronizeModels is called before the system is ready for binding."));
		return;
	}

	CohtmlDataBindingHelpers::SynchronizeModels(GetView());
}

#if !defined(COHTML_UE4_418_SUPPORT)
DEFINE_FUNCTION(UCohtmlWidget::execCreateDataModelFromStruct)
{
	if (!P_THIS->IsReadyForBindings())
	{
		return;
	}
	P_GET_PROPERTY(UStrProperty, Name);

	Stack.StepCompiledIn<UStructProperty>(NULL);
	void* ArgAddress = Stack.MostRecentPropertyAddress;
	UStructProperty* Prop = Cast<UStructProperty>(Stack.MostRecentProperty);

	if (Prop)
	{
		CohtmlDataBindingHelpers::CreateModel(P_THIS->GetView(), Name, ArgAddress, Prop->Struct);
	}
	P_FINISH;
};

DEFINE_FUNCTION(UCohtmlWidget::execUpdateWholeDataModelFromStruct)
{
	if (!P_THIS->IsReadyForBindings())
	{
		return;
	}

	Stack.StepCompiledIn<UStructProperty>(NULL);
	void* ArgAddress = Stack.MostRecentPropertyAddress;
	UStructProperty* Prop = Cast<UStructProperty>(Stack.MostRecentProperty);
	CohtmlDataBindingHelpers::UpdateWholeModel(P_THIS->GetView(), ArgAddress, Prop->Struct);
	P_FINISH;
};
#endif

FCohtmlCaretRect UCohtmlWidget::GetCaretRect() const
{
	if (CoherentWidget.IsValid())
	{
		return CoherentWidget->CaretRect;
	}
	return FCohtmlCaretRect();
}

void UCohtmlWidget::SetCaretRect(int x, int y, unsigned width, unsigned height)
{
	if (CoherentWidget.IsValid())
	{
		CoherentWidget->CaretRect = FCohtmlCaretRect(x, y, width, height);
	}
}

void UCohtmlWidget::SetSoundAttenuation(const FSoundAttenuationSettings& Settings)
{
	if (AudioWrapper.HasOwner())
	{
		AudioWrapper.SetAttenuation(Settings);
	}
}

void UCohtmlWidget::SetInputPropagationBehaviour(ECohtmlInputPropagationBehaviour::Type Propagation)
{
	InputPropagationBehaviour = Propagation;
	if (CoherentWidget.IsValid())
	{
		CoherentWidget->SetInputPropagationBehaviour(Propagation);
	}
}

ECohtmlInputPropagationBehaviour::Type UCohtmlWidget::GetInputPropagationBehaviour() const
{
	return InputPropagationBehaviour;
}

void UCohtmlWidget::OnAudioStreamCreated(int Id, int BitDepth, int Channels, float SamplingRate)
{
	if (Owner && !AudioWrapper.HasOwner())
	{
		AudioWrapper.SetOwner(Owner);
	}

	if (AudioWrapper.HasOwner())
	{
		AudioWrapper.CreateStream(Id, BitDepth, Channels, SamplingRate);
	}
}

void UCohtmlWidget::OnAudioStreamClosed(int Id)
{
	if (AudioWrapper.HasOwner())
	{
		AudioWrapper.DestroyStream(Id);
	}
}

void UCohtmlWidget::OnAudioStreamPlay(int Id)
{
	if (AudioWrapper.HasOwner())
	{
		AudioWrapper.PlayStream(Id);
	}
}

void UCohtmlWidget::OnAudioStreamPause(int Id)
{
	if (AudioWrapper.HasOwner())
	{
		AudioWrapper.PauseStream(Id);
	}
}

void UCohtmlWidget::OnAudioDataReceived(int Id, int Samples, float** Pcm, int Channels)
{
	if (AudioWrapper.HasOwner())
	{
		AudioWrapper.ReceiveDataForStream(Id, Samples, Pcm, Channels);
	}
}

void UCohtmlWidget::OnAudioStreamEnded(int Id)
{
	if (AudioWrapper.HasOwner())
	{
		AudioWrapper.StreamEnded(Id);
	}
}

void UCohtmlWidget::OnAudioStreamVolumeChanged(int Id, float Volume)
{
	if (AudioWrapper.HasOwner())
	{
		AudioWrapper.ChangeStreamVolume(Id, Volume);
	}
}

int32 UCohtmlWidget::GetUserIndex()
{
	// When previewing a widget in-editor there is no owning player
	if (!GetWorld() || GetWorld()->IsPreviewWorld())
	{
		return 0;
	}

	APlayerController* OwningPlayer = GetOwningPlayer();
	if (!OwningPlayer)
	{
		COHTML_UE_LOG(Warning, TEXT("Current CohtmlWidget has no owning Player attached"
			"- defaulting to Player 0"));
		return 0;
	}

	ULocalPlayer* LocalPlayer = OwningPlayer->GetLocalPlayer();
	return LocalPlayer ? LocalPlayer->GetControllerId() : 0;
}

void UCohtmlWidget::SetInputFocusToUI()
{
	FSlateApplication& SlateApp = FSlateApplication::Get();
	LastFocusedWidgetBeforeUI = SlateApp.GetUserFocusedWidget(GetUserIndex());
	FWidgetPath WidgetPath;
	if (CoherentWidget.IsValid() && SlateApp.GeneratePathToWidgetUnchecked(CoherentWidget.ToSharedRef(), WidgetPath))
	{
		SlateApp.ResetToDefaultInputSettings();
		SlateApp.SetAllUserFocus(CoherentWidget);
	}
}

void UCohtmlWidget::RestoreInputFocusFromUI(bool bForceFocusToGame)
{
	FSlateApplication& SlateApp = FSlateApplication::Get();
	TSharedPtr<SViewport> ViewportWidget = SlateApp.GetGameViewport();
	if (!LastFocusedWidgetBeforeUI.IsValid() || bForceFocusToGame || LastFocusedWidgetBeforeUI == ViewportWidget)
	{
		// focus input to ViewportWidget with mouse locking
		FWidgetPath ViewportWidgetPath;
		if (ViewportWidget.IsValid() && SlateApp.GeneratePathToWidgetUnchecked(ViewportWidget.ToSharedRef(), ViewportWidgetPath))
		{
			// See FSceneViewport::OnKeyboardFocusReceived for conditions that need to be met to lock the mouse cursor
			APlayerController* LocalPC = GEngine->GetFirstLocalPlayerController(GetWorld());
			LocalPC->CurrentMouseCursor = EMouseCursor::None;

			FReply Reply = FReply::Handled();
			Reply.SetUserFocus(ViewportWidget.ToSharedRef(), EFocusCause::Mouse);

			Reply.UseHighPrecisionMouseMovement(ViewportWidget.ToSharedRef());
			Reply.PreventThrottling();
			SlateApp.ProcessReply(ViewportWidgetPath, Reply, nullptr, nullptr);
		}
	}
	else
	{
		// focus input to LastFocusedWidgetBeforeUI without mouse locking
		SlateApp.SetAllUserFocus(LastFocusedWidgetBeforeUI);
	}
	LastFocusedWidgetBeforeUI.Reset();
}
