/*
This file is part of Cohtml, Gameface and Prysm -
modern user interface technologies for games. Release $RELEASE$. Build $VERSION$ for $LICENSEE$.

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
#include "CohtmlIMEManager.h"

#include "CohtmlTextInputMethodContextGeneric.h"
#include "CohtmlTextInputMethodContextWin8AndAbove.h"
#include "SCohtmlWidget.h"
#include "SCohtmlInputForward.h"


FCohtmlIMEManager::FCohtmlIMEManager(const TWeakPtr<SWidget> Widget)
	: OwningWidget(Widget)
{
	FString OSVersion, OSSubVersion;
	FPlatformMisc::GetOSVersions(OSVersion, OSSubVersion);

	if (OSVersion == FString(TEXT("Windows 8"))
		|| OSVersion == FString(TEXT("Windows 8.1"))
		|| OSVersion == FString(TEXT("Windows 10")))
	{
		TextInputMethodContext = MakeShareable(new FCohtmlTextInputMethodContextWin8AndAbove(this));
	}
	else
	{
		TextInputMethodContext = MakeShareable(new FCohtmlTextInputMethodContextGeneric(this));
	}
	ITextInputMethodSystem* const TextInputMethodSystem = FSlateApplication::Get().GetTextInputMethodSystem();
	if (TextInputMethodSystem)
	{
		TextInputMethodChangeNotifier = TextInputMethodSystem->RegisterContext(TextInputMethodContext.ToSharedRef());
	}
	if (TextInputMethodChangeNotifier.IsValid())
	{
		TextInputMethodChangeNotifier->NotifyLayoutChanged(ITextInputMethodChangeNotifier::ELayoutChangeType::Created);
	}
}

FCohtmlIMEManager::~FCohtmlIMEManager()
{
	ITextInputMethodSystem* const TextInputMethodSystem = FSlateApplication::IsInitialized() ? FSlateApplication::Get().GetTextInputMethodSystem() : nullptr;
	if (TextInputMethodSystem)
	{
		TSharedRef<ITextInputMethodContext> TextInputMethodContextRef = TextInputMethodContext.ToSharedRef();
		if (TextInputMethodSystem->IsActiveContext(TextInputMethodContextRef))
		{
			// This can happen if an entire tree of widgets is culled, as Slate isn't notified of the focus loss, the widget is just deleted
			TextInputMethodSystem->DeactivateContext(TextInputMethodContextRef);
		}

		TextInputMethodSystem->UnregisterContext(TextInputMethodContextRef);
	}
}

TSharedPtr<FGenericWindow> FCohtmlIMEManager::GetWindow()
{
	TSharedPtr<FGenericWindow> Window;
	const TSharedPtr<SWidget> OwningWidgetPtr = OwningWidget.Pin();
	if (OwningWidgetPtr.IsValid())
	{
		const TSharedPtr<SWindow> SlateWindow = FSlateApplication::Get().FindWidgetWindow(OwningWidgetPtr.ToSharedRef());
		Window = SlateWindow.IsValid() ? SlateWindow->GetNativeWindow() : nullptr;
	}
	return Window;
}

void FCohtmlIMEManager::ActivateTextInputMethodSystemContext(bool bActivate)
{
	// From SEditableText
	FSlateApplication& SlateApplication = FSlateApplication::Get();
#if defined(COHTML_UE4_417_SUPPORT)
	if (FPlatformMisc::GetRequiresVirtualKeyboard())
#else
	if (FPlatformMisc::SupportsTouchInput())
#endif
	{
		SlateApplication.ShowVirtualKeyboard(false, 0);
	}
	else
	{
		ITextInputMethodSystem* const TextInputMethodSystem = SlateApplication.GetTextInputMethodSystem();
		if (TextInputMethodSystem)
		{
			if (bActivate)
			{
				TextInputMethodSystem->ActivateContext(TextInputMethodContext.ToSharedRef());
			}
			else
			{
				TextInputMethodSystem->DeactivateContext(TextInputMethodContext.ToSharedRef());
			}
		}
	}
}


bool FCohtmlIMEManager::IsValid() const
{
	return OwningWidget.IsValid();
}


FCohtmlInputForwardIME::FCohtmlInputForwardIME(const TWeakPtr<SCohtmlInputForward> Widget)
	: FCohtmlIMEManager(Widget)
{
}

cohtml::View* FCohtmlInputForwardIME::GetView()
{
	auto Widget = StaticCastSharedPtr<SCohtmlInputForward>(OwningWidget.Pin());
	if (Widget.IsValid() && Widget->FocusedViewComponent.Get() != nullptr)
	{
		return Widget->FocusedViewComponent->GetView();
	}
	return nullptr;
}

FCohtmlCaretRect FCohtmlInputForwardIME::GetCaretRect()
{
	auto OwningWidgetPtr = StaticCastSharedPtr<SCohtmlInputForward>(OwningWidget.Pin());
	if (OwningWidgetPtr.IsValid() && OwningWidgetPtr->FocusedViewComponent.Get() != nullptr)
	{
		return OwningWidgetPtr->FocusedViewComponent->GetCaretRect();
	}
	return FCohtmlCaretRect();
}

bool FCohtmlInputForwardIME::RequiresProjection() const
{
	auto OwningWidgetPtr = StaticCastSharedPtr<SCohtmlInputForward>(OwningWidget.Pin());
	if (OwningWidgetPtr.IsValid() && OwningWidgetPtr->FocusedViewComponent.Get() != nullptr)
	{
		return OwningWidgetPtr->FocusedViewComponent->GetClass() == UCohtmlComponent::StaticClass();
	}
	return false;
}


FCohtmlWidgetIME::FCohtmlWidgetIME(const TWeakPtr<SCohtmlWidget> Widget)
	: FCohtmlIMEManager(Widget)
{
}

cohtml::View* FCohtmlWidgetIME::GetView()
{
	auto OwningWidgetPtr = StaticCastSharedPtr<SCohtmlWidget>(OwningWidget.Pin());
	if (OwningWidgetPtr.IsValid())
	{
		return OwningWidgetPtr->GetView();
	}
	return nullptr;
}

FCohtmlCaretRect FCohtmlWidgetIME::GetCaretRect()
{
	auto OwningWidgetPtr = StaticCastSharedPtr<SCohtmlWidget>(OwningWidget.Pin());
	if (OwningWidgetPtr.IsValid())
	{
		return OwningWidgetPtr->CaretRect;
	}
	return FCohtmlCaretRect();
}

bool FCohtmlWidgetIME::RequiresProjection() const
{
	return false;
}
