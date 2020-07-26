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

#include "cohtml/View.h"

#include "CohtmlSystem.h"
#include "CohtmlEventHelpers.h"
#include "CohtmlViewListener.h"
#include "CohtmlRenderWrapper.h"
#include "CohtmlAudioWrapper.h"
#include "CohtmlDataBinding.h"
#include "CohtmlBaseComponent.generated.h"

namespace cohtml
{
class SystemRenderer;
}

class FCohtmlGesturePolicy;
struct FCohtmlMeshData;

UCLASS(BlueprintType, meta=(DisplayName = "Prysm Base Component"))
class COHTMLPLUGIN_API UCohtmlBaseComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()
public:
	/** Sets the AttenuationSettings for the Sound Components
	Note: Sound is 2D by default. It can be changed to 3D if appropriate AttenuationSettings is set.
	for more details look at Unreal's documentation for AttenuationSettings */
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void SetSoundAttenuation(const FSoundAttenuationSettings& Settings);

	/** When fired, the View is ready for binding events. Any event bound prior to this will be ignored */
	UPROPERTY(BlueprintAssignable)
	FCohtmlReadyForBindingsSignature ReadyForBindings;

	/** When fired, the View has released its bindings. */
	UPROPERTY(BlueprintAssignable)
	FCohtmlBindingsReleasedSignature BindingsReleased;

	/** Called when the View is ready to accept events */
	UPROPERTY(BlueprintAssignable)
	FCohtmlScriptingReady ScriptingReady;

	/** Resizes the View */
	UFUNCTION(BlueprintCallable, Category = "View")
	virtual void Resize(/*uint32*/ int32 width, /*uint32*/ int32 height);

	/** Tells if the View is ready to be created */
	UFUNCTION(BlueprintCallable, Category = "View")
	bool IsReadyToCreateView() const;

	/** Tells if the View is ready to be created */
	UFUNCTION(BlueprintCallable, Category = "View")
	bool IsReadyForBindings() const;

	/** Tells if a View has been scheduled for creation */
	UFUNCTION(BlueprintCallable, Category = "View")
	bool HasRequestedView() const;

	/** Tells the view to show/hide debug paint rectangles */
	UFUNCTION(BlueprintCallable, Category = "View")
	void ShowPaintRects(bool show);

	/** Requests a new URL to be loaded in the View */
	UFUNCTION(BlueprintCallable, Category = "View")
	void Load(const FString& path);

	/** Requests the View to reload the current URL */
	UFUNCTION(BlueprintCallable, Category = "View")
	void Reload();

	/** Saves next render frame to disk */
	UFUNCTION(BlueprintCallable, Category = "View")
	void DebugSaveNextFrame();

	/** Starts saving render frames to disk */
	UFUNCTION(BlueprintCallable, Category = "View")
	void BeginDebugFrameSave();

	/** Stops saving render frames to disk */
	UFUNCTION(BlueprintCallable, Category = "View")
	void EndDebugFrameSave();

	/** Delays UI updates until after cameras are updated. Read the section in the FAQ page of the documentation before using */
	UFUNCTION(BlueprintCallable, Category = "View")
	void EnableDelayedUpdate(bool bEnabled);

	/** Creates an event that will be executed in JavaScript */
	UFUNCTION(BlueprintCallable, Category = "ViewScripting")
	UCohtmlJSEvent* CreateJSEvent();

	/** Triggers an event in JavaScript */
	UFUNCTION(BlueprintCallable, Category = "ViewScripting")
	void TriggerJSEvent(const FString& name, UCohtmlJSEvent* eventData) const;

	/** Creates a global variable (data model) in JavaScript from an UObject */
	UFUNCTION(BlueprintCallable, Category = "ViewScripting")
	void CreateDataModelFromObject(const FString& Name, UObject* Model);

	/** Creates a global variable (data model) in JavaScript from a UStruct */
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (CustomStructureParam = "Arg"), Category = "ViewScripting")
	void CreateDataModelFromStruct(const FString& Name, const UStructProperty* Arg);

	/** Marks an Object model for update. The UI using this data model will be updated during the next
	call to SynchronizeModels. For optimum performance, call SynchronizeModels as rarely as possible.
	(e.g. once per frame)*/
	UFUNCTION(BlueprintCallable, Category = "ViewScripting")
	void UpdateWholeDataModelFromObject(UObject* Model) const;

	/** Marks a Struct model for update. The UI using this data model will be updated during the next
	call to SynchronizeModels. For optimum performance, call SynchronizeModels as rarely as possible.
	(e.g. once per frame)*/
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (CustomStructureParam = "Struct"), Category = "ViewScripting")
	void UpdateWholeDataModelFromStruct(const UStructProperty* Struct) const;

	/** Synchronize all models marked for update. */
	UFUNCTION(BlueprintCallable, Category = "ViewScripting")
	void SynchronizeModels() const;

	/** Whether to enable support for complex CSS selectors (e.g. div > p, div ~ p)*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View", DisplayName = "Enable Complex CSS Selector Support")
	bool bEnableComplexCSSSupport;

	/** Gives access to the UI Texture */
	UPROPERTY(BlueprintReadOnly, Category = "View")
	UTextureRenderTarget2D* Texture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View", AdvancedDisplay)
	TEnumAsByte<enum TextureFilter> Filter;

	/** Indicates whether input is forwarded to this view */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")
	bool bReceiveInput;

	/** Changes this component's tick group to TG_PostUpdateWork and sends bindings before drawing.
	For more information refer to the FAQ section of the documentation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")
	bool bDelayedUpdate;

	static void CreateSystemIfNecessary(UWorld* World);
	static class ACohtmlSystem* GetSystemActor(UWorld* World);

	virtual ~UCohtmlBaseComponent();
	virtual void InitializeComponent() override;
	virtual void BeginDestroy() override;
	virtual bool IsReadyForFinishDestroy() override;
	virtual void FinishDestroy() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	bool EnsureMeshData();
	TArray<FCohtmlMeshData> MeshData;

	typedef TArray<TWeakObjectPtr<UCohtmlBaseComponent>> WeakCohtmlComponentsArray;
	static WeakCohtmlComponentsArray::TIterator GetUCohtmlBaseComponentIterator(UWorld* world);

	cohtml::View* GetView() const;
	cohtml::ViewRenderer* GetViewRenderer() const;
	FCohtmlGesturePolicy* GetGesturePolicy();

	const FCohtmlCaretRect& GetCaretRect() const;
	void SetCaretRect(int x, int y, unsigned width, unsigned height);

	EMouseCursor::Type CurrentMouseCursor;

	// This method is meant to be used in inherited classes only.
	virtual int32 GetUserIndex() { return 0; }

	void SetInputFocusToUI();
	void RestoreInputFocusFromUI(bool bForceFocusToGame = false);

protected:
	void CreateView(const cohtml::ViewSettings& info, const FString& url);

	virtual void SendRenderDynamicData_Concurrent() override;
	virtual bool RequiresGameThreadEndOfFrameUpdates() const override { return true; }

private:
	friend class TCohtmlViewListener<UCohtmlBaseComponent>;

	void OnAudioStreamCreated(int Id, int BitDepth, int Channels,
		float samplingRate);
	void OnAudioStreamClosed(int Id);
	void OnAudioStreamPlay(int Id);
	void OnAudioStreamPause(int Id);
	void OnAudioDataReceived(int Id, int Samples, float** Pcm,
		int channels);
	void OnAudioStreamEnded(int Id);
	void OnAudioStreamVolumeChanged(int Id, float Volume);

	TCohtmlAudioWrapper<UCohtmlBaseComponent> AudioWrapper;

	void OnCursorChanged(cohtml::CursorTypes::Cursors Cursor);

	void SetReadyForBindings();

	FCohtmlCaretRect CaretRect;
	TSharedPtr<TCohtmlViewListener<UCohtmlBaseComponent>> Listener;
	TUniquePtr<FCohtmlRenderWrapper> RenderWrapper;

	TSharedPtr<SWidget> LastFocusedWidgetBeforeUI;

	// Custom deleter function is used so we can use a forward declaration of GesturePolicy
	struct GesturePolicyDeleter
	{
		void operator()(FCohtmlGesturePolicy* Ptr) const;
	};
	TUniquePtr<FCohtmlGesturePolicy, GesturePolicyDeleter> GesturePolicy;

	ACohtmlSystem* SystemActor;
	cohtml::SystemRenderer* SystemRenderer;

	bool bIsLoadingMeshData;
	bool bHasMeshData;

	void LoadMeshData(const TArray<TWeakObjectPtr<UStaticMeshComponent>>& Meshes);

	unsigned PendingLayout;

public:
#if defined(COHTML_UE4_418_SUPPORT)
	DECLARE_FUNCTION(execCreateDataModelFromStruct)
	{
		if (!IsReadyForBindings())
		{
			return;
		}
		P_GET_PROPERTY(UStrProperty, Name);

		Stack.StepCompiledIn<UStructProperty>(NULL);
		void* ArgAddress = Stack.MostRecentPropertyAddress;
		UStructProperty* Prop = Cast<UStructProperty>(Stack.MostRecentProperty);

		if (Prop)
		{
			CohtmlDataBindingHelpers::CreateModel(GetView(), Name, ArgAddress, Prop->Struct);
		}
		P_FINISH;
	}

	DECLARE_FUNCTION(execUpdateWholeDataModelFromStruct)
	{
		if (!IsReadyForBindings())
		{
			return;
		}

		Stack.StepCompiledIn<UStructProperty>(NULL);
		void* ArgAddress = Stack.MostRecentPropertyAddress;
		UStructProperty* Prop = Cast<UStructProperty>(Stack.MostRecentProperty);
		CohtmlDataBindingHelpers::UpdateWholeModel(GetView(), ArgAddress, Prop->Struct);
		P_FINISH;
	}
#else
	//declared here and defined in the cpp file
	DECLARE_FUNCTION(execCreateDataModelFromStruct);
	DECLARE_FUNCTION(execUpdateWholeDataModelFromStruct);
#endif
};

