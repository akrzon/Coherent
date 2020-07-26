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
#include "CohtmlBaseComponent.h"

#include "CohtmlSystem.h"
#include "CohtmlSystemHolder.h"
#include "CohtmlSettings.h"
#include "CohtmlGestureApplicationPolicy.h"

#include "cohtml/System.h"
#include "cohtml/View.h"
#include "cohtml/ResourceHandler.h"
#include "cohtml/Binding/Binding.h"
#include "cohtml/Binding/Binder.h"
#include "cohtml/Binding/EventHandler.h"

#include "CohtmlFStringBinder.h"
#include "CohtmlHelpers.h"
#include "CohtmlInputActor.h"
#include "CohtmlInputHelpers.h"
#include "SceneUtils.h"
#include "EngineUtils.h"
#include "Components/StaticMeshComponent.h"
#include "CohtmlMeshData.h"
#include "CohtmlAudioWrapper.inl"

#include <Widgets/SViewport.h>

template TCohtmlAudioWrapper<UCohtmlBaseComponent>::TCohtmlAudioWrapper();
template TCohtmlAudioWrapper<UCohtmlBaseComponent>::~TCohtmlAudioWrapper();

void UCohtmlBaseComponent::GesturePolicyDeleter::operator()(FCohtmlGesturePolicy* Ptr) const
{
	delete Ptr;
};

UCohtmlBaseComponent::UCohtmlBaseComponent(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
	const auto Settings = GetDefault<UCohtmlSettings>();

	bAutoActivate = true;
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.TickGroup = TG_StartPhysics;
	PrimaryComponentTick.bTickEvenWhenPaused = Settings->TickWhileGameIsPaused;

	bEnableComplexCSSSupport = true;
	bWantsInitializeComponent = true;
	bIsLoadingMeshData = false;
	bHasMeshData = false;
	bReceiveInput = true;
	CurrentMouseCursor = EMouseCursor::Default;
	bDelayedUpdate = false;
	AudioWrapper.SetOwner(this);

	LastFocusedWidgetBeforeUI.Reset();
}

UCohtmlBaseComponent::~UCohtmlBaseComponent()
{
	if (Listener.IsValid())
	{
		Listener->OwnerDestroyed();
	}
}

void UCohtmlBaseComponent::InitializeComponent()
{
	Super::InitializeComponent();

	CreateSystemIfNecessary(GetWorld());

	Listener = TSharedPtr<TCohtmlViewListener<UCohtmlBaseComponent>>(new TCohtmlViewListener<UCohtmlBaseComponent>(this));
	RenderWrapper.Reset(new FCohtmlRenderWrapper(Listener, Listener, &Texture, &Filter));

	bIsLoadingMeshData = false;
	bHasMeshData = false;

	SystemActor = GetSystemActor(GetWorld());
	SystemActor->RegisterComponent(this);

	if (bDelayedUpdate)
	{
		EnableDelayedUpdate(true);
	}

	// We are using MarkRenderDynamicDataDirty() which
	// works only if we have RenderState created
	RecreateRenderState_Concurrent();
}

bool UCohtmlBaseComponent::IsReadyToCreateView() const
{
	return FCohtmlSystemHolder::IsReady();
}

void UCohtmlBaseComponent::CreateSystemIfNecessary(UWorld* World)
{
	if (GetSystemActor(World))
		return;

	FActorSpawnParameters Params;
	Params.bAllowDuringConstructionScript = true;
	World->SpawnActor<ACohtmlSystem>(Params);
}

ACohtmlSystem* UCohtmlBaseComponent::GetSystemActor(UWorld* World)
{
	for (TActorIterator<ACohtmlSystem> It(World); It; ++It)
	{
		return *It;
	}

	return nullptr;
}

void UCohtmlBaseComponent::Resize(int32 width, int32 height)
{
	RenderWrapper->Resize(width, height);
}

void UCohtmlBaseComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (RenderWrapper->Tick(DeltaTime))
	{
		// Mark the component for render data update just before starting rendering of the scene
		// in order to give time for Layout/RecordRendering to finish on the worker thread.
		// Otherwise Paint call will block on them.
		MarkRenderDynamicDataDirty();
	}
}

void UCohtmlBaseComponent::SendRenderDynamicData_Concurrent()
{
	// This is called just before starting Scene rendering which is the last possible time to issue
	// our Paint command which will wait for Layout/RecordRendering to finish before painting.
	// This is called on the Game Thread as we have overridden RequiresGameThreadEndOfFrameUpdates()
	UActorComponent::SendRenderDynamicData_Concurrent();
	RenderWrapper->Paint_GameThread();
}

UCohtmlBaseComponent::WeakCohtmlComponentsArray::TIterator UCohtmlBaseComponent::GetUCohtmlBaseComponentIterator(UWorld* world)
{
	for (TActorIterator<ACohtmlSystem> It(world); It; ++It)
	{
		return (*It)->GetCohtmlComponentsIterator();
	}

	static WeakCohtmlComponentsArray EmptyComponentsArray;
	return EmptyComponentsArray.CreateIterator();
}

namespace
{

#ifndef UI_TEXTURE_NAME
#define UI_TEXTURE_NAME TEXT("UITexture")
#endif

bool HasCoherentUIView(UStaticMeshComponent* Mesh)
{
	auto MaterialsCount = Mesh->GetNumMaterials();
	for (auto m = 0; m != MaterialsCount; ++m)
	{
		auto Material = Mesh->GetMaterial(m);
		UTexture* Texture = nullptr;

		if (Material && Material->GetTextureParameterValue(UI_TEXTURE_NAME, Texture))
		{
			return true;
		}
	}
	return false;
}
}

bool UCohtmlBaseComponent::EnsureMeshData()
{
	auto Owner = GetOwner();
	if (!bHasMeshData && Owner && !bIsLoadingMeshData)
	{
		bIsLoadingMeshData = true;
		TArray<UStaticMeshComponent*> StaticMeshes;
		Owner->GetComponents<UStaticMeshComponent>(StaticMeshes);

		TArray<TWeakObjectPtr<UStaticMeshComponent>> WeakMeshes;

		auto NumMeshes = StaticMeshes.Num();
		for (auto Index = 0u; Index != NumMeshes; ++Index)
		{
			if (HasCoherentUIView(StaticMeshes[Index]))
			{
				WeakMeshes.Add(StaticMeshes[Index]);
			}
		}

		ENQUEUE_COHTML_RENDERING_COMMAND_TWOPARAMETER(CohtmlLoadMeshData,
			TWeakObjectPtr<UCohtmlBaseComponent>, ViewComponent, this,
			TArray<TWeakObjectPtr<UStaticMeshComponent>>, Meshes, WeakMeshes,
			{
				if (ViewComponent.IsValid())
				{
					ViewComponent->LoadMeshData(Meshes);
				}
			});
	}
	return bHasMeshData;
}

void UCohtmlBaseComponent::LoadMeshData(const TArray<TWeakObjectPtr<UStaticMeshComponent>>& Meshes)
{
	auto NumMeshes = Meshes.Num();
	MeshData.Reserve(NumMeshes);
	for (auto Index = 0u; Index != NumMeshes; ++Index)
	{
		if (Meshes[Index].IsValid())
		{
			MeshData.Add(::LoadCohtmlMeshData(Meshes[Index].Get()));
		}
	}
	bHasMeshData = true;
}

void UCohtmlBaseComponent::BeginDestroy()
{
	Super::BeginDestroy();
	if (RenderWrapper)
	{
		RenderWrapper->BeginDestroy();
	}
}

bool UCohtmlBaseComponent::IsReadyForFinishDestroy()
{
	auto ready = Super::IsReadyForFinishDestroy();
	if (RenderWrapper)
	{
		return ready && RenderWrapper->IsReadyForFinishDestroy();
	}
	return ready;
}

void UCohtmlBaseComponent::FinishDestroy()
{
	if (RenderWrapper)
	{
		RenderWrapper->FinishDestroy();
		RenderWrapper.Reset();
	}
	if (SystemActor && FCohtmlSystemHolder::IsReady())
	{
		SystemActor->UnregisterComponent(this);
	}
	Super::FinishDestroy();
}

cohtml::ViewRenderer* UCohtmlBaseComponent::GetViewRenderer() const
{
	return RenderWrapper->GetViewRenderer();
}

FCohtmlGesturePolicy* UCohtmlBaseComponent::GetGesturePolicy()
{
	if (!GesturePolicy)
	{
		GesturePolicy.Reset(new FCohtmlGesturePolicy());
		GesturePolicy->Initialize(RenderWrapper->GetView());
	}
	return GesturePolicy.Get();
}

void UCohtmlBaseComponent::CreateView(
	const cohtml::ViewSettings& info,
	const FString& url)
{
	cohtml::ViewSettings Info = info;
	Info.EnableComplexCSSSelectorsStyling = bEnableComplexCSSSupport;
	RenderWrapper->CreateView(Info, url);
}

cohtml::View* UCohtmlBaseComponent::GetView() const
{
	return RenderWrapper->GetView();
}

bool UCohtmlBaseComponent::HasRequestedView() const
{
	return RenderWrapper->HasRequestedView();
}

void UCohtmlBaseComponent::ShowPaintRects(bool Show)
{
	if (RenderWrapper->GetView())
	{
		RenderWrapper->GetView()->ShowPaintRectangles(Show);
	}
}

void UCohtmlBaseComponent::Load(const FString& path)
{
	if (RenderWrapper->GetView())
	{
		RenderWrapper->GetView()->LoadURL(TCHAR_TO_UTF8(*path));
	}
}

void UCohtmlBaseComponent::Reload()
{
	if (RenderWrapper->GetView())
		RenderWrapper->GetView()->Reload();
}

void UCohtmlBaseComponent::DebugSaveNextFrame()
{
	if (RenderWrapper->GetView())
	{
		RenderWrapper->GetView()->CaptureSingleDebugFrame(nullptr, Helpers::SaveCaptureToDisk);
	}
}

void UCohtmlBaseComponent::BeginDebugFrameSave()
{
	if (RenderWrapper->GetView())
	{
		RenderWrapper->GetView()->BeginCaptureDebugFrame(nullptr, Helpers::SaveCaptureToDisk);
	}
}

void UCohtmlBaseComponent::EndDebugFrameSave()
{
	if (RenderWrapper->GetView())
	{
		RenderWrapper->GetView()->EndCaptureDebugFrame();
	}
}

void UCohtmlBaseComponent::EnableDelayedUpdate(bool bEnabled)
{
	bDelayedUpdate = bEnabled;

	if (bEnabled)
	{
		GetOwner()->PrimaryActorTick.TickGroup = TG_PostUpdateWork;
		AddTickPrerequisiteActor(GetOwner());
	}
	else
	{
		GetOwner()->PrimaryActorTick.TickGroup = TG_StartPhysics;
		RemoveTickPrerequisiteActor(GetOwner());
	}
}

void UCohtmlBaseComponent::OnCursorChanged(cohtml::CursorTypes::Cursors Cursor)
{
	CurrentMouseCursor = CohtmlInputHelpers::TranslateCurrentCohtmlMouseCursor(Cursor);
}

void UCohtmlBaseComponent::SetReadyForBindings()
{
	// Do nothing if we were already destroyed. May happen in async if the view
	// is destroyed before its first layout and async event processing happens only in the destructor.
	if (!HasAnyFlags(RF_BeginDestroyed))
	{
		GetView()->BindCall("ScriptingReady", cohtml::MakeHandler(
			&ScriptingReady,
			&FCohtmlScriptingReady::Broadcast));
	}
}

bool UCohtmlBaseComponent::IsReadyForBindings() const
{
	auto View = GetView();
	return View ? View->IsReadyForBindings() : false;
}

UCohtmlJSEvent* UCohtmlBaseComponent::CreateJSEvent()
{
	return NewObject<UCohtmlJSEvent>();
}

void UCohtmlBaseComponent::TriggerJSEvent(const FString& name, UCohtmlJSEvent* eventData) const
{
	if (!IsReadyForBindings())
		return;

	CohtmlEventHelpers::TriggerJSEvent(name, eventData, RenderWrapper->GetView());
}

void UCohtmlBaseComponent::CreateDataModelFromObject(const FString& Name, UObject* Model)
{
	if (!IsReadyForBindings())
	{
		COHTML_UE_LOG(Warning, TEXT("CreateDataModelFromObject is called before the system is ready for binding."));
		return;
	}
	CohtmlDataBindingHelpers::CreateModel(GetView(), Name, Model, Model->GetClass());
}

void UCohtmlBaseComponent::CreateDataModelFromStruct(const FString& Name, const UStructProperty* Arg)
{
	// This is only a stub.
	// It should never be called, there's a custom thunk implementation in the header
	check(0);
}

void UCohtmlBaseComponent::UpdateWholeDataModelFromObject(UObject* Model) const
{
	if (!IsReadyForBindings())
	{
		COHTML_UE_LOG(Warning, TEXT("UpdateWholeDataModelFromObject is called before the system is ready for binding."));
		return;
	}
	CohtmlDataBindingHelpers::UpdateWholeModel(GetView(), Model, Model->GetClass());
}

void UCohtmlBaseComponent::UpdateWholeDataModelFromStruct(const UStructProperty* Struct) const
{
	// This is only a stub.
	// It should never be called, there's a custom thunk implementation in the header
	check(0);
}

void UCohtmlBaseComponent::SynchronizeModels() const
{
	if (!IsReadyForBindings())
	{
		COHTML_UE_LOG(Warning, TEXT("SynchronizeModels is called before the system is ready for binding."));
		return;
	}

	CohtmlDataBindingHelpers::SynchronizeModels(GetView());
}

void UCohtmlBaseComponent::SetSoundAttenuation(const FSoundAttenuationSettings& Settings)
{
	AudioWrapper.SetAttenuation(Settings);
}

void UCohtmlBaseComponent::OnAudioStreamCreated(int Id, int BitDepth, int Channels, float SamplingRate)
{
	AudioWrapper.CreateStream(Id, BitDepth, Channels, SamplingRate);
}

void UCohtmlBaseComponent::OnAudioStreamClosed(int Id)
{
	AudioWrapper.DestroyStream(Id);
}

void UCohtmlBaseComponent::OnAudioStreamPlay(int Id)
{
	AudioWrapper.PlayStream(Id);
}

void UCohtmlBaseComponent::OnAudioStreamPause(int Id)
{
	AudioWrapper.PauseStream(Id);
}

void UCohtmlBaseComponent::OnAudioDataReceived(int Id, int Samples, float** Pcm, int Channels)
{
	AudioWrapper.ReceiveDataForStream(Id, Samples, Pcm, Channels);
}

void UCohtmlBaseComponent::OnAudioStreamEnded(int Id)
{
	AudioWrapper.StreamEnded(Id);
}

void UCohtmlBaseComponent::OnAudioStreamVolumeChanged(int Id, float Volume)
{
	AudioWrapper.ChangeStreamVolume(Id, Volume);
}

const FCohtmlCaretRect& UCohtmlBaseComponent::GetCaretRect() const
{
	return CaretRect;
}

void UCohtmlBaseComponent::SetCaretRect(int x, int y, unsigned width, unsigned height)
{
	CaretRect = FCohtmlCaretRect(x, y, width, height);
}

namespace {
ACohtmlInputActor* FindCohtmlInputActor(UWorld* World)
{
	for (auto Actor : TActorRange<ACohtmlInputActor>(World))
	{
		return Actor;
	}
	return nullptr;
}
}

void UCohtmlBaseComponent::SetInputFocusToUI()
{
	ACohtmlInputActor* CohtmlInputActor = FindCohtmlInputActor(GetWorld());
	if (!CohtmlInputActor)
	{
		return;
	}

	FSlateApplication& SlateApp = FSlateApplication::Get();
	LastFocusedWidgetBeforeUI = SlateApp.GetUserFocusedWidget(GetUserIndex());

	CohtmlInputActor->SetCohtmlViewFocus(this);
	CohtmlInputActor->SetCohtmlInputFocus(true);
}

void UCohtmlBaseComponent::RestoreInputFocusFromUI(bool bForceFocusToGame)
{
	ACohtmlInputActor* CohtmlInputActor = FindCohtmlInputActor(GetWorld());
	if (!CohtmlInputActor)
	{
		return;
	}

	FSlateApplication& SlateApp = FSlateApplication::Get();
	TSharedPtr<SViewport> ViewportWidget = SlateApp.GetGameViewport();

	if (!LastFocusedWidgetBeforeUI.IsValid() || bForceFocusToGame || LastFocusedWidgetBeforeUI == ViewportWidget)
	{
		// focus input to ViewportWidget with mouse locking
		CohtmlInputActor->SetCohtmlInputFocus(false);
	}
	else
	{
		// focus input to LastFocusedWidgetBeforeUI without mouse locking
		SlateApp.SetAllUserFocus(LastFocusedWidgetBeforeUI);
	}
	LastFocusedWidgetBeforeUI.Reset();
}

#if !defined(COHTML_UE4_418_SUPPORT)
DEFINE_FUNCTION(UCohtmlBaseComponent::execCreateDataModelFromStruct)
{
	P_GET_PROPERTY(UStrProperty, Name);
	Stack.StepCompiledIn<UStructProperty>(NULL);
	void* ArgAddress = Stack.MostRecentPropertyAddress;
	UStructProperty* Prop = Cast<UStructProperty>(Stack.MostRecentProperty);

	if (Prop)
	{
		if(P_THIS->IsReadyForBindings())
		{
			CohtmlDataBindingHelpers::CreateModel(P_THIS->GetView(), Name, ArgAddress, Prop->Struct);
		}
		else
		{
			COHTML_UE_LOG(Error, TEXT("Unable to create a model from %s."
									  "The View should be ready for bindings first."),
									  *Prop->Struct->GetFName().ToString());
		}
	}
	P_FINISH;
};

DEFINE_FUNCTION(UCohtmlBaseComponent::execUpdateWholeDataModelFromStruct)
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
