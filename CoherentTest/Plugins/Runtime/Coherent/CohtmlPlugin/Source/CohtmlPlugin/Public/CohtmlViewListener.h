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

#include <cohtml/View.h>
#include <cohtml/TextInputHandler.h>
#include <cohtml/InputEvents.h>

#include "ICohtmlPlugin.h"
#include "CohtmlVirtualKeyboardEntry.h"
#include "CohtmlSettings.h"

#include "Framework/Application/SlateApplication.h"


template<typename T>
class TCohtmlViewListener : public cohtml::IViewListener, public cohtml::ITextInputHandler
{
public:

	TCohtmlViewListener(T* owner)
		: Owner(owner)
	{}

	virtual ~TCohtmlViewListener()
	{
		if (CohtmlVirtualKeyboardEntry.IsValid())
		{
			CohtmlVirtualKeyboardEntry->ClearOwningView();
		}
	}

	void OwnerDestroyed()
	{
		Owner = nullptr;
	}

	virtual bool OnNavigateTo(const char *url) override
	{
		return true;
	}

	virtual void OnScriptContextCreated() override
	{}

	/// Called when the initial version of the DOM has been built after parsing the page
	virtual void OnDOMBuilt() override
	{}

	virtual void OnLoadFailed(const char *url , const char *error) override
	{}

	virtual void OnFinishLoad(const char *url) override
	{}

	virtual void OnCursorChanged(cohtml::CursorTypes::Cursors Cursor, const char* Url,
		const float* XHotspot, const float* YHotspot) override
	{
		UNUSED_PARAM(Url);
		UNUSED_PARAM(XHotspot);
		UNUSED_PARAM(YHotspot);
		if (Owner)
		{
			Owner->OnCursorChanged(Cursor);
		}
	}

	virtual void OnReadyForBindings() override
	{
		if (Owner)
		{
			Owner->SetReadyForBindings();
			Owner->ReadyForBindings.Broadcast();
		}
	}

	virtual void OnBindingsReleased() override
	{
		if (Owner)
		{
			Owner->BindingsReleased.Broadcast();
		}
	}

	virtual cohtml::ScreenInfo OnScreenInfoRequested() override
	{
		cohtml::ScreenInfo Info;
#if !UE_SERVER
		auto Window = FSlateApplication::Get().GetActiveTopLevelWindow();
		if (Window.IsValid())
		{
			FVector2D Size = Window->GetSizeInScreen();
			Info.AvailableWidth = Size.X;
			Info.AvailableHeight = Size.Y;
			Info.ColorDepth = 24;
			Info.PixelDepth = 24;
			Info.Width = Size.X;
			Info.Height = Size.Y;
		}
#endif
		return Info;
	}

	/// Called before an event is passed to a DOM node for evaluation.
	/// The user is able to interrupt the handling and bubbling of events or
	/// let them continue normally.

	virtual cohtml::EventAction::Actions OnNodeTouched(const cohtml::INodeProxy* Node, const cohtml::TouchEventData* Event, void* UserData,
		const cohtml::InputEventPhase::PhaseType Phase) override
	{
		const auto Settings = GetDefault<UCohtmlSettings>();
		if (!Settings->HandleInputOnHTMLBody &&
			Phase == cohtml::InputEventPhase::AT_TARGET &&
			Node->GetTag() == cohtml::HTMLTag::BODY)
		{
			if (UserData)
			{
				*static_cast<bool*>(UserData) = false;
			}
			return cohtml::EventAction::Actions::InterruptHandling;
		}

		for (auto i = 0u; i < Node->GetClassesCount(); ++i)
		{
			for (const auto& CSSTransparentClass : Settings->InputTransparentCssClasses)
			{
				if (Phase == cohtml::InputEventPhase::AT_TARGET &&
					CSSTransparentClass.Compare(Node->GetClass(i), ESearchCase::IgnoreCase) == 0)
				{
					if (UserData)
					{
						*static_cast<bool*>(UserData) = false;
					}
					return cohtml::EventAction::Actions::InterruptHandling;
				}
			}
		}
		if (UserData)
		{
			*static_cast<bool*>(UserData) = true;
		}
		return cohtml::EventAction::Actions::ContinueHandling;
	}

	/// Called before an event is passed to a DOM node for evaluation.
	/// The user is able to interrupt the handling and bubbling of events or
	/// let them continue normally.
	virtual cohtml::EventAction::Actions OnNodeMouseEvent(const cohtml::INodeProxy* Node, const cohtml::MouseEventData* Event, void* UserData,
		const cohtml::InputEventPhase::PhaseType Phase) override
	{
		if (Event->Type == cohtml::MouseEventData::EventType::MouseMove ||
			Event->Type == cohtml::MouseEventData::EventType::MouseWheel)
		{
			if (UserData)
			{
				*static_cast<bool*>(UserData) = true;
			}
			return cohtml::EventAction::Actions::ContinueHandling;
		}

		const auto Settings = GetDefault<UCohtmlSettings>();
		if (!Settings->HandleInputOnHTMLBody &&
			Phase == cohtml::InputEventPhase::AT_TARGET &&
			Node->GetTag() == cohtml::HTMLTag::BODY)
		{
			if (UserData)
			{
				*static_cast<bool*>(UserData) = false;
			}
			return cohtml::EventAction::Actions::InterruptHandling;
		}

		for (auto i = 0u; i < Node->GetClassesCount(); ++i)
		{
			for (const auto& CSSTransparentClass : Settings->InputTransparentCssClasses)
			{
				if (Phase == cohtml::InputEventPhase::AT_TARGET &&
					CSSTransparentClass.Compare(Node->GetClass(i), ESearchCase::IgnoreCase) == 0)
				{
					if (UserData)
					{
						*static_cast<bool*>(UserData) = false;
					}
					return cohtml::EventAction::Actions::InterruptHandling;
				}
			}
		}
		if (UserData)
		{
			*static_cast<bool*>(UserData) = true;
		}
		return cohtml::EventAction::Actions::ContinueHandling;
	}

	/// Called before an event is passed to a DOM node for evaluation.
	/// The user is able to interrupt the handling and bubbling of events or
	/// let them continue normally.
	virtual cohtml::EventAction::Actions OnNodeKeyEvent(const cohtml::INodeProxy* Node, const cohtml::KeyEventData* Event, void* UserData,
		const cohtml::InputEventPhase::PhaseType Phase) override
	{
		return cohtml::EventAction::Actions::ContinueHandling;
	}

	virtual void OnTextInputTypeChanged(cohtml::TextInputControlType::ControlType Type) override
	{}

	virtual void OnSelectionChanged(cohtml::IInputProxy* proxy,
		cohtml::TextInput::Selection selection) override
	{}

	virtual void OnTextChanged(cohtml::IInputProxy* proxy,
		const char* addedChars, unsigned addedCount,
		const char* removedChars, unsigned removedCount,
		unsigned index) override
	{}

	virtual void OnFocus(cohtml::IInputProxy* proxy) override
	{
		if (!Owner)
		{
			return;
		}

#if PLATFORM_QUAIL
		// sets input focus to UI widget or InputActor because QUAIL VK is
		// simulating keyboard events and we need to be on focus to receive them
		Owner->SetInputFocusToUI();
#endif

		int32 UserIndex = Owner->GetUserIndex();
		CohtmlVirtualKeyboardEntry.Reset();

		auto& ShowVirtualKeyboardOverride = ICohtmlPlugin::Get().OnShowVirtualKeyboard;
		if (ShowVirtualKeyboardOverride.IsBound())
		{
			ShowVirtualKeyboardOverride.Execute(CohtmlVirtualKeyboardEntry, UserIndex, Owner->GetView(), proxy);
		}
		else
		{
			CohtmlVirtualKeyboardEntry = MakeShareable(new FCohtmlVirtualKeyboardEntry(Owner->GetView(), proxy));
			FSlateApplication::Get().ShowVirtualKeyboard(true, UserIndex, CohtmlVirtualKeyboardEntry);
		}
	}

	virtual void OnBlur(cohtml::IInputProxy* proxy) override
	{
		if (!Owner)
		{
			return;
		}
		int32 UserIndex = Owner->GetUserIndex();
		FSlateApplication::Get().ShowVirtualKeyboard(false, UserIndex);
		CohtmlVirtualKeyboardEntry.Reset();

#if PLATFORM_QUAIL
		// restores input focus to the widget previously focused or to the game
		Owner->RestoreInputFocusFromUI();
#endif
	}

	virtual void OnCaretRectChanged(int x, int y, unsigned width, unsigned height) override
	{
		if (Owner)
		{
			Owner->SetCaretRect(x, y, width, height);
		}
	}

	virtual void OnIMEShouldCancelComposition() override {}

	virtual void OnAudioStreamCreated(int Id, int BitDepth, int Channels, float SamplingRate) override
	{
		if (Owner)
		{
			Owner->OnAudioStreamCreated(Id, BitDepth, Channels, SamplingRate);
		}
	}

	virtual void OnAudioStreamClosed(int Id) override
	{
		if (Owner)
		{
			Owner->OnAudioStreamClosed(Id);
		}
	}

	virtual void OnAudioStreamPlay(int Id) override
	{
		if (Owner)
		{
			Owner->OnAudioStreamPlay(Id);
		}
	}

	virtual void OnAudioStreamPause(int Id) override
	{
		if (Owner)
		{
			Owner->OnAudioStreamPause(Id);
		}
	}

	virtual void OnAudioDataReceived(int Id, int Samples, float** Pcm, int Channels) override
	{
		if (Owner)
		{
			Owner->OnAudioDataReceived(Id, Samples, Pcm, Channels);
		}
	}

	virtual void OnAudioStreamEnded(int Id) override
	{
		if (Owner)
		{
			Owner->OnAudioStreamEnded(Id);
		}
	}

	virtual void OnAudioStreamVolumeChanged(int Id, float Volume) override
	{
		if (Owner)
		{
			Owner->OnAudioStreamVolumeChanged(Id, Volume);
		}
	}

private:
	T* Owner;
	TSharedPtr<FCohtmlVirtualKeyboardEntry> CohtmlVirtualKeyboardEntry;
};
