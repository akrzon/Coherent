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
#include "CohtmlInputActor.h"

#include "CohtmlInputBindings.h"

#include <Widgets/SViewport.h>
#include <Widgets/SWeakWidget.h>
#include <Widgets/Input/SVirtualJoystick.h>
#include <Engine/GameViewportClient.h>
#include <TimerManager.h>
#include <GameFramework/PlayerController.h>

ACohtmlInputActor::ACohtmlInputActor(const FObjectInitializer& PCIP)
	: Super(PCIP)
	, InputPropagationBehaviour(ECohtmlInputPropagationBehaviour::None)
{
}

void ACohtmlInputActor::Initialize(ECollisionChannel CollisionChannel, TextureAddress AddressMode, ECohtmlInputWidgetRaycastQuality RaycastQuality, int32 UVChannel)
{
	if (GetWorld()->GetNetMode() == NM_DedicatedServer)
	{
		return;
	}

	// Setup the input sink widget
	CohtmlInputForwardWidget = SNew(SCohtmlInputForward).Owner(this);
	if (GEngine->IsValidLowLevel())
	{
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(CohtmlInputForwardWidget.ToSharedRef()));
	}
	if (CohtmlInputForwardWidget.IsValid())
	{
		CohtmlInputForwardWidget->SetVisibility(EVisibility::Visible);
		CohtmlInputForwardWidget->SetRaycastCollisionGroup(CollisionChannel);
		CohtmlInputForwardWidget->SetRaycastTextureAddressMode(AddressMode);
		CohtmlInputForwardWidget->SetRaycastQuality(RaycastQuality);
		CohtmlInputForwardWidget->SetRaycastUVChannel(uint32(UVChannel));

		CohtmlInputForwardWidget->OnCohtmlInputWidgetMouseButtonDown.AddUObject(this, &ACohtmlInputActor::OnCohtmlInputWidgetMouseButtonDown);
		CohtmlInputForwardWidget->OnCohtmlInputWidgetMouseButtonUp.AddUObject(this, &ACohtmlInputActor::OnCohtmlInputWidgetMouseButtonUp);
		CohtmlInputForwardWidget->OnCohtmlInputWidgetKeyDown.AddUObject(this, &ACohtmlInputActor::OnCohtmlInputWidgetKeyDown);
		CohtmlInputForwardWidget->OnCohtmlInputWidgetKeyUp.AddUObject(this, &ACohtmlInputActor::OnCohtmlInputWidgetKeyUp);
	}
}

void ACohtmlInputActor::AttachVirtualJoystick(TSharedRef<SVirtualJoystick> Joystick)
{
	GEngine->GameViewport->RemoveViewportWidgetContent(Joystick);
	CohtmlInputForwardWidget->AttachVirtualJoystick(Joystick);
}

void ACohtmlInputActor::DetachVirtualJoystick()
{
	CohtmlInputForwardWidget->DetachVirtualJoystick();
}

void ACohtmlInputActor::SetCohtmlInputFocus(bool FocusUI)
{
	if (!CohtmlInputForwardWidget.IsValid())
	{
		COHTML_UE_LOG(Error, TEXT("Trying to set focus to the UI, but the Slate widget is not available!"));
		return;
	}

	FSlateApplication& SlateApp = FSlateApplication::Get();
	if (FocusUI)
	{
		// Capture all input; the propagation mode will decide whether to send
		// input to the engine in the event handlers of SCohtmlWidget
		FWidgetPath WidgetPath;
		if (CohtmlInputForwardWidget.IsValid() && SlateApp.GeneratePathToWidgetUnchecked(CohtmlInputForwardWidget.ToSharedRef(), WidgetPath))
		{
			SlateApp.ResetToDefaultInputSettings();
			SlateApp.SetAllUserFocus(CohtmlInputForwardWidget);
		}
		else
		{
			// Unable to set focus due to slate not entirely initialized yet; Try again after 33ms
			FTimerDelegate TimerDelegate = FTimerDelegate::CreateLambda([&]()
			{
				SlateApp.ResetToDefaultInputSettings();
				SlateApp.SetAllUserFocus(CohtmlInputForwardWidget);
			});
			FTimerHandle Handler;
			GetWorldTimerManager().SetTimer(Handler, TimerDelegate, 0.033f, false);
		}
	}
	else
	{
		if (IsCohtmlFocused())
		{
			// The ViewportWidget is only held as WeakPtr in FSlateApplication - may be null
			TSharedPtr<SViewport> ViewportWidget = SlateApp.GetGameViewport();
			FWidgetPath ViewportWidgetPath;
			if (ViewportWidget.IsValid() && SlateApp.GeneratePathToWidgetUnchecked(ViewportWidget.ToSharedRef(), ViewportWidgetPath))
			{
				// See FSceneViewport::OnKeyboardFocusReceived for conditions that need to be met to lock the mouse cursor
				APlayerController* LocalPC = GEngine->GetFirstLocalPlayerController(GetWorld());
				LocalPC->CurrentMouseCursor = EMouseCursor::None;

				FReply TheReply = FReply::Handled();
				TheReply.SetUserFocus(ViewportWidget.ToSharedRef(), EFocusCause::Mouse);

				TheReply.UseHighPrecisionMouseMovement(ViewportWidget.ToSharedRef());
				TheReply.PreventThrottling();
				SlateApp.ProcessReply(ViewportWidgetPath, TheReply, nullptr, nullptr);
			}
			else
			{
				COHTML_UE_LOG(Error, TEXT("Trying to set focus to the game viewport, but cannot obtain the widget path for it!"));
			}
		}
	}
}

bool ACohtmlInputActor::IsCohtmlFocused() const
{
	return FSlateApplication::Get().GetKeyboardFocusedWidget() == CohtmlInputForwardWidget;
}

void ACohtmlInputActor::ToggleCohtmlInputFocus()
{
	SetCohtmlInputFocus(!IsCohtmlFocused());
}

void ACohtmlInputActor::SetCohtmlViewFocus(UCohtmlBaseComponent* NewFocusedView)
{
	if (CohtmlInputForwardWidget.IsValid())
	{
		CohtmlInputForwardWidget->RefocusView(NewFocusedView);
	}
}

void ACohtmlInputActor::SetInputPropagationBehaviour(ECohtmlInputPropagationBehaviour::Type Propagation)
{
	InputPropagationBehaviour = Propagation;
	if (CohtmlInputForwardWidget.IsValid())
	{
		CohtmlInputForwardWidget->SetInputPropagationBehaviour(Propagation);
	}
}

ECohtmlInputPropagationBehaviour::Type ACohtmlInputActor::GetInputPropagationBehaviour() const
{
	return InputPropagationBehaviour;
}

void ACohtmlInputActor::AlwaysAcceptMouseInput(bool bAccept)
{
	if (CohtmlInputForwardWidget.IsValid())
	{
		CohtmlInputForwardWidget->SetAlwaysAcceptMouseInputEvents(bAccept);
	}
}

void ACohtmlInputActor::SetLineTraceMode(ECohtmlInputWidgetLineTraceMode Mode)
{
	if (CohtmlInputForwardWidget.IsValid())
	{
		CohtmlInputForwardWidget->SetLineTraceMode(Mode);
	}
}

static ECohtmlKeys::Type FKeyToEnum(const FKey& Key)
{
#define COMPARE_FKEY_AND_RETURN_ENUM(FKey, CoherentVK) \
	if (EKeys::FKey == Key) return ECohtmlKeys::FKey; \

	FKEY_MACRO_ITERATOR(COMPARE_FKEY_AND_RETURN_ENUM);

#undef COMPARE_FKEY_AND_RETURN_ENUM

	return ECohtmlKeys::Unknown;
}

void ACohtmlInputActor::OnCohtmlInputWidgetMouseButtonDown(const FKey& Button)
{
	OnCohtmlInputActorMouseButtonDown.Broadcast(FKeyToEnum(Button));
}

void ACohtmlInputActor::OnCohtmlInputWidgetMouseButtonUp(const FKey& Button)
{
	OnCohtmlInputActorMouseButtonUp.Broadcast(FKeyToEnum(Button));
}

void ACohtmlInputActor::OnCohtmlInputWidgetKeyDown(const FKey& Key)
{
	OnCohtmlInputActorKeyDown.Broadcast(FKeyToEnum(Key));
}

void ACohtmlInputActor::OnCohtmlInputWidgetKeyUp(const FKey& Key)
{
	OnCohtmlInputActorKeyUp.Broadcast(FKeyToEnum(Key));
}

TSharedPtr<SCohtmlInputForward> ACohtmlInputActor::GetWidget()
{
	return CohtmlInputForwardWidget;
}

FCohtmlGamepadBehaviourOnFocusLostDelegate& ACohtmlInputActor::GetGamepadBehaviourDelegate()
{
	return CohtmlInputForwardWidget.Get()->GamepadBehaviourOnFocusLostDelegate;
}
