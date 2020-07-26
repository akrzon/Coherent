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

#include <Sound/SoundAttenuation.h>
#include "Runtime/UMG/Public/Components/Widget.h"
#include <GameFramework/PlayerController.h>
#include <Engine/LocalPlayer.h>

#include "SCohtmlWidget.h"
#include "CohtmlEventHelpers.h"
#include "CohtmlViewListener.h"
#include "CohtmlAudioWrapper.h"

#include "CohtmlWidget.generated.h"

namespace cohtml
{
class View;
}

/** A HTML5 control powered by Prysm. */
UCLASS(Category = "Prysm", meta=(DisplayName = "Prysm Widget"))
class COHTMLPLUGIN_API UCohtmlWidget : public UWidget
{
	GENERATED_UCLASS_BODY()

public:
	virtual ~UCohtmlWidget();
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

protected:
	TSharedPtr<SCohtmlWidget> CoherentWidget;

private:
	void OnViewCreated(cohtml::View* View);

	friend class TCohtmlViewListener<UCohtmlWidget>;

	// During destruction we will lose the ref to the slate widget
	// which means that can't access its view (which will be in the process of destruction, yet still alive).
	// We need the view so that we can replay any events left over in async mode so store it here.
	// In other words - this is only used during destruction and shouldn't even be used directly, use GetView() instead
	cohtml::View* CachedView;

public:
	/** Gets or sets the Actor containing any LiveViewComponents. */
	UPROPERTY(BlueprintReadWrite, Category = "View")
	AActor* Owner;

	// BASE COMPONENT COPY START

	/** Sets the AttenuationSettings for the Sound Components
	Note: Sound is 2D by default. It can be changed to 3D if appropriate AttenuationSettings is set.
	for more details look at Unreal's documentation for AttenuationSettings */
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void SetSoundAttenuation(const FSoundAttenuationSettings& Settings);

	/** Sets the type of input that the widget will propagate to the game */
	UFUNCTION(BlueprintCallable, Category = "View")
	void SetInputPropagationBehaviour(ECohtmlInputPropagationBehaviour::Type Propagation);

	/** Gets the type of input that the widget will propagate to the game */
	UFUNCTION(BlueprintCallable, Category = "View")
	ECohtmlInputPropagationBehaviour::Type GetInputPropagationBehaviour() const;

	/** When fired, the View is ready for binding events. Any event bound prior to this will be ignored */
	UPROPERTY(BlueprintAssignable)
	FCohtmlReadyForBindingsSignature ReadyForBindings;

	/** When fired, the View has released its bindings. */
	UPROPERTY(BlueprintAssignable)
	FCohtmlBindingsReleasedSignature BindingsReleased;

	/** Called when the View is ready to accept events */
	UPROPERTY(BlueprintAssignable)
	FCohtmlScriptingReady ScriptingReady;

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

	/** Whether to enable support for complex CSS selectors (e.g. div > p, div ~ p)*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View", DisplayName = "Enable Complex CSS Selector Support")
	bool bEnableComplexCSSSupport;

	/** Gives access to the UI Texture */
	UFUNCTION(BlueprintCallable, Category = "View")
	UTextureRenderTarget2D* GetRenderTexture() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View", AdvancedDisplay)
	TEnumAsByte<enum TextureFilter> Filter;

	/** Indicates whether input is forwarded to this view */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")
	bool bReceiveInput;

	/** Indicates the type of input this view forwards to the game */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")
	TEnumAsByte<ECohtmlInputPropagationBehaviour::Type> InputPropagationBehaviour;

	/** Whether this widget's material should be gamma corrected or not.
	Set to true if the widget is used for HUD.
	Set to false if it is used for in-game surface. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")
	bool bGammaCorrectedMaterial;

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
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (CustomStructureParam = "Struct"), Category = "ViewScripting")
	void CreateDataModelFromStruct(const FString& Name, const UStructProperty* Struct);

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

	inline cohtml::View* GetView() const
	{
		if (CoherentWidget.IsValid())
		{
			return CoherentWidget->GetView();
		}
		return CachedView;
	}

	virtual void BeginDestroy() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	int32 GetUserIndex();

	void SetInputFocusToUI();
	void RestoreInputFocusFromUI(bool bForceFocusToGame = false);

	FCohtmlCaretRect GetCaretRect() const;
	void SetCaretRect(int x, int y, unsigned width, unsigned height);

private:
	void OnAudioStreamCreated(int Id, int BitDepth, int Channels, float SamplingRate);
	void OnAudioStreamClosed(int Id);
	void OnAudioStreamPlay(int Id);
	void OnAudioStreamPause(int Id);
	void OnAudioDataReceived(int Id, int Samples, float** Pcm, int Channels);
	void OnAudioStreamEnded(int Id);
	void OnAudioStreamVolumeChanged(int Id, float Volume);

	TCohtmlAudioWrapper<AActor> AudioWrapper;

	void OnCursorChanged(cohtml::CursorTypes::Cursors Cursor);

	void SetReadyForBindings();

	TSharedPtr<TCohtmlViewListener<UCohtmlWidget>> Listener;

	TSharedPtr<SWidget> LastFocusedWidgetBeforeUI;

	cohtml::ViewSettings LastSavedViewSettings;

	// BASE COMPONENT COPY END

	// COMPONENT COPY BEGIN. DON'T COPY WIDTH AND HEIGHT
public:
	/** The URL to load when the View is created */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")
	FString URL;

	// COMPONENT COPY END
};
