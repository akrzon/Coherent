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
#include "CohtmlEventHelpers.h"

#include "UObject/Class.h"
#include "cohtml/Binding/Binding.h"
#include "cohtml/Binding/Binder.h"
#include "cohtml/Binding/EventHandler.h"
#include "CohtmlFStringBinder.h"
#include "CohtmlFVectorBinder.h"
#include "CohtmlFIntVectorBinder.h"
#include "CohtmlFColorBinder.h"

#if defined(COHTML_UE4_413_SUPPORT)
#include <UObject/ObjectBase.h>
#else
#include <UObject/UObjectBase.h>
#endif

UCohtmlEventHelpers::UCohtmlEventHelpers(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

namespace CohtmlEventHelpers
{
	template<typename T>
	void BindArray(cohtml::Binder* Binder, const TArray<T>& Array)
	{
		Binder->ArrayBegin(Array.Num());
		for (auto It = Array.CreateConstIterator(); It; ++It)
		{
			CoherentBindInternal(Binder, *It);
		}
		Binder->ArrayEnd();
	}
	template<>
	void BindArray(cohtml::Binder* Binder, const TArray<UObject*>& Array)
	{
		Binder->ArrayBegin(Array.Num());
		for (auto Element : Array)
		{
			// IMPORTANT: Manually call BindUType as CoherentBind will think that the object's type is UObject
			// due to compile-time type deduction
			BindUType(Binder, Element, Element->GetClass());
		}
		Binder->ArrayEnd();
	}
	void BindArrayOfStructs(cohtml::Binder* Binder, const TArray<uint8>& Array, const UStruct* StructType)
	{
		Binder->ArrayBegin(Array.Num());
		const auto StructSize = StructType->GetStructureSize();
		for (auto ElementOffset = 0; ElementOffset < Array.Num() * StructSize; ElementOffset += StructSize)
		{
			BindUType(Binder, Array.GetData() + ElementOffset, StructType);
		}
		Binder->ArrayEnd();
	}

	void BindArray(cohtml::Binder* Binder, const UCohtmlJSEvent::FBoundArrayData& BoundArrayData)
	{
		// Save on boilerplate
#define BIND_ARRAY_OF_TYPE(EnumType, Type)\
	case EnumType:\
		BindArray(Binder, *(TArray<Type>*)BoundArrayData.Data);\
	break
#define BIND_ARRAY_OF_STRUCTS()\
	case UCohtmlJSEvent::VT_Struct:\
		check(BoundArrayData.StructType); \
		BindArrayOfStructs(Binder, *(TArray<uint8>*)BoundArrayData.Data, BoundArrayData.StructType);\
	break

		switch (BoundArrayData.VariableType)
		{
			BIND_ARRAY_OF_TYPE(UCohtmlJSEvent::VT_Int32, int32);
			BIND_ARRAY_OF_TYPE(UCohtmlJSEvent::VT_Bool, bool);
			BIND_ARRAY_OF_TYPE(UCohtmlJSEvent::VT_Float, float);
			BIND_ARRAY_OF_TYPE(UCohtmlJSEvent::VT_String, FString);
			BIND_ARRAY_OF_STRUCTS();
			BIND_ARRAY_OF_TYPE(UCohtmlJSEvent::VT_Object, UObject*);
		default:
			COHTML_UE_LOG(Warning, TEXT("Tried to bind an array of unsupported type: %d"), (int)BoundArrayData.VariableType);
		}
#undef BIND_ARRAY_OF_TYPE
	}

	void BindData(UCohtmlJSEvent* EventData, const UCohtmlJSEvent::FVariablePair& Pair, cohtml::Binder* Binder)
	{
		switch (Pair.Type)
		{
		case UCohtmlJSEvent::VT_Object:
			// The object might have died prior to sending the event so check if it's still alive
			if (EventData->Objects[Pair.Id].IsValid())
			{
				// IMPORTANT: Manually call BindUType as CoherentBind will think that the object's type is UObject
				// due to compile-time type deduction
				BindUType(Binder, EventData->Objects[Pair.Id].Get(), EventData->Objects[Pair.Id]->GetClass());
			}
			else
			{
				Binder->BindNull();
				COHTML_UE_LOG(Warning, TEXT("Failed to bind object with argument id %d (as it was null) while triggering a JS event."), Pair.Id);
			}
			break;
		case UCohtmlJSEvent::VT_Struct:
			BindUType(Binder, EventData->StructArgs[Pair.Id].Data.GetData(), EventData->StructArgs[Pair.Id].StructType);
			break;
		case UCohtmlJSEvent::VT_Int32:
			CoherentBindInternal(Binder, EventData->Ints[Pair.Id]);
			break;
		case UCohtmlJSEvent::VT_String:
			CoherentBindInternal(Binder, EventData->Strings[Pair.Id]);
			break;
		case UCohtmlJSEvent::VT_Float:
			CoherentBindInternal(Binder, EventData->Floats[Pair.Id]);
			break;
		case UCohtmlJSEvent::VT_Bool:
			CoherentBindInternal(Binder, EventData->Bools[Pair.Id]);
			break;
		case  UCohtmlJSEvent::VT_Array:
			BindArray(Binder, EventData->Arrays[Pair.Id]);
			break;
		default:
			COHTML_UE_LOG(Warning, TEXT("Triggering JS event with unknown type!"));
			break;
		}
	}

	void TriggerJSEvent(const FString& name, UCohtmlJSEvent* eventData, cohtml::View* View)
	{
		using namespace cohtml;

		if (!eventData || eventData->OrderedVariables.Num() == 0)
		{
			View->TriggerEvent(TCHAR_TO_UTF8(*name));
			return;
		}

		auto binder = View->GetBinder();
		check(binder);
		binder->BeginEvent(TCHAR_TO_UTF8(*name), eventData->OrderedVariables.Num());

		for (auto i = 0; i < eventData->OrderedVariables.Num(); ++i)
		{
			const auto& pair = eventData->OrderedVariables[i];
			BindData(eventData, pair, binder);
		}
		binder->EndEvent();
	}
}
