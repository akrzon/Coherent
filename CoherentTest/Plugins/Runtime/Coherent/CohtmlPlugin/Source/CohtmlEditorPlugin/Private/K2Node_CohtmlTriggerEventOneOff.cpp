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
#include "K2Node_CohtmlTriggerEventOneOff.h"

#include "CohtmlBaseComponent.h"
#include "CohtmlJSEvent.h"
#include "CohtmlBlueprintFunctionLibrary.h"

#include <KismetCompiler.h>
#include <EditorCategoryUtils.h>
#include <BlueprintActionDatabaseRegistrar.h>
#include <Kismet2/BlueprintEditorUtils.h>
#include <BlueprintNodeSpawner.h>

struct FK2Node_CohtmlEditorBPNodeHelper
{
	static FCOH_K2NodeName WorldContextPinName;
	static FCOH_K2NodeName EventNamePinName;
	static FCOH_K2NodeName CohtmlPinName;
};

FCOH_K2NodeName FK2Node_CohtmlEditorBPNodeHelper::WorldContextPinName(TEXT("WorldContextObject"));
FCOH_K2NodeName FK2Node_CohtmlEditorBPNodeHelper::EventNamePinName(TEXT("EventName"));
FCOH_K2NodeName FK2Node_CohtmlEditorBPNodeHelper::CohtmlPinName(TEXT("Component"));

#define LOCTEXT_NAMESPACE "K2Node_CohtmlEditorBPNode"

UK2Node_CohtmlTriggerEventOneOff::UK2Node_CohtmlTriggerEventOneOff(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeTooltip = LOCTEXT("NodeTooltip", "Triggers JavaScript Event");
}


void UK2Node_CohtmlTriggerEventOneOff::AllocateDefaultPins()
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Add execution pins
#if defined(COHTML_UE4_418_SUPPORT)
	CreatePin(EGPD_Input, K2Schema->PC_Exec, TEXT(""), NULL, false, false, K2Schema->PN_Execute);
	CreatePin(EGPD_Output, K2Schema->PC_Exec, TEXT(""), NULL, false, false, K2Schema->PN_Then);
#else
	CreatePin(EGPD_Input, K2Schema->PC_Exec, TEXT(""), K2Schema->PN_Execute);
	CreatePin(EGPD_Output, K2Schema->PC_Exec, TEXT(""), K2Schema->PN_Then);
#endif

	// If required add the world context pin
	if (GetBlueprint()->ParentClass->HasMetaData(FBlueprintMetadata::MD_ShowWorldContextPin))
	{
		CreatePin(EGPD_Input, K2Schema->PC_Object, TEXT(""), UObject::StaticClass(),
#if defined(COHTML_UE4_418_SUPPORT)
			false, false,
#endif
			FK2Node_CohtmlEditorBPNodeHelper::WorldContextPinName);
	}

	// Add Cohtml Component pin
	UEdGraphPin* CohtmlPin = CreatePin(EGPD_Input, K2Schema->PC_Object, TEXT(""), UCohtmlBaseComponent::StaticClass(),
#if defined(COHTML_UE4_418_SUPPORT)
		false, false,
#endif
		FK2Node_CohtmlEditorBPNodeHelper::CohtmlPinName);

	// Add event name pin
	UEdGraphPin* EventNamePin = CreatePin(EGPD_Input, K2Schema->PC_String, TEXT(""),
#if defined(COHTML_UE4_418_SUPPORT)
		nullptr, false, false,
#endif
		FK2Node_CohtmlEditorBPNodeHelper::EventNamePinName);

	SetPinToolTip(*EventNamePin, LOCTEXT("EventNamePinDescription", "The name of the JavaScript event that will be triggered."));

	Super::AllocateDefaultPins();
}

void UK2Node_CohtmlTriggerEventOneOff::SetPinToolTip(UEdGraphPin& MutatablePin, const FText& PinDescription) const
{
	MutatablePin.PinToolTip = UEdGraphSchema_K2::TypeToText(MutatablePin.PinType).ToString();

	UEdGraphSchema_K2 const* const K2Schema = Cast<const UEdGraphSchema_K2>(GetSchema());
	if (K2Schema != nullptr)
	{
		MutatablePin.PinToolTip += TEXT(" ");
		MutatablePin.PinToolTip += K2Schema->GetPinDisplayName(&MutatablePin).ToString();
	}

	MutatablePin.PinToolTip += FString(TEXT("\n")) + PinDescription.ToString();
}

UEdGraphPin* UK2Node_CohtmlTriggerEventOneOff::CreatePinFromUserDefinition(const TSharedPtr<FUserPinInfo> NewPinInfo)
{
#if !defined(COHTML_UE4_418_SUPPORT)
	FCreatePinParams PinParams;
	PinParams.ContainerType = NewPinInfo->PinType.ContainerType;
	PinParams.bIsReference = NewPinInfo->PinType.bIsReference;
#endif

	UEdGraphPin* NewPin = CreatePin(
		EGPD_Input,
		NewPinInfo->PinType.PinCategory,
		NewPinInfo->PinType.PinSubCategory,
		NewPinInfo->PinType.PinSubCategoryObject.Get(),
#if defined(COHTML_UE4_416_SUPPORT)
		NewPinInfo->PinType.bIsArray,
		NewPinInfo->PinType.bIsReference,
		NewPinInfo->PinName
#elif defined(COHTML_UE4_418_SUPPORT)
		NewPinInfo->PinName,
		NewPinInfo->PinType.ContainerType,
		NewPinInfo->PinType.bIsReference
#else
		NewPinInfo->PinName,
		PinParams
#endif
	);
	NewPin->DefaultValue = NewPin->AutogeneratedDefaultValue = NewPinInfo->PinDefaultValue;
	return NewPin;
}

void UK2Node_CohtmlTriggerEventOneOff::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
	AllocateDefaultPins();
}

bool UK2Node_CohtmlTriggerEventOneOff::IsUserDefinedPin(UEdGraphPin* Pin)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	return(Pin->PinName != K2Schema->PN_Execute &&
		Pin->PinName != K2Schema->PN_Then &&
		Pin->PinName != K2Schema->PN_ReturnValue &&
		Pin->PinName != FK2Node_CohtmlEditorBPNodeHelper::CohtmlPinName &&
		Pin->PinName != FK2Node_CohtmlEditorBPNodeHelper::EventNamePinName &&
		Pin->PinName != FK2Node_CohtmlEditorBPNodeHelper::WorldContextPinName);
}

bool UK2Node_CohtmlTriggerEventOneOff::IsSupportedArgumentType(UEdGraphPin* Pin)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	const auto& ArgType = Pin->PinType.PinCategory;
	return(ArgType == K2Schema->PC_Boolean ||
		ArgType == K2Schema->PC_Byte ||
		ArgType == K2Schema->PC_Int ||
		ArgType == K2Schema->PC_Float ||
		ArgType == K2Schema->PC_String ||
		ArgType == K2Schema->PC_Struct ||
		ArgType == K2Schema->PC_Object);
}

void UK2Node_CohtmlTriggerEventOneOff::PinDefaultValueChanged(UEdGraphPin* ChangedPin)
{
	if (ChangedPin->PinName == FK2Node_CohtmlEditorBPNodeHelper::EventNamePinName)
	{
		CachedNodeTitle.MarkDirty();
	}

	// Refresh the UI for the graph so the pin changes show up
	UEdGraph* Graph = GetGraph();
	Graph->NotifyGraphChanged();

	// Mark dirty
	FBlueprintEditorUtils::MarkBlueprintAsModified(GetBlueprint());
}

FText UK2Node_CohtmlTriggerEventOneOff::GetTooltipText() const
{
	return NodeTooltip;
}

UEdGraphPin* UK2Node_CohtmlTriggerEventOneOff::GetThenPin()const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	UEdGraphPin* Pin = FindPinChecked(K2Schema->PN_Then);
	check(Pin->Direction == EGPD_Output);
	return Pin;
}

UEdGraphPin* UK2Node_CohtmlTriggerEventOneOff::GetEventNamePin(const TArray<UEdGraphPin*>* InPinsToSearch /*= NULL*/) const
{
	const TArray<UEdGraphPin*>* PinsToSearch = InPinsToSearch ? InPinsToSearch : &Pins;

	UEdGraphPin* Pin = NULL;
	for (auto PinIt = PinsToSearch->CreateConstIterator(); PinIt; ++PinIt)
	{
		UEdGraphPin* TestPin = *PinIt;
		if (TestPin && TestPin->PinName == FK2Node_CohtmlEditorBPNodeHelper::EventNamePinName)
		{
			Pin = TestPin;
			break;
		}
	}
	check(Pin == NULL || Pin->Direction == EGPD_Input);
	return Pin;
}

UEdGraphPin* UK2Node_CohtmlTriggerEventOneOff::GetCohtmlPin(const TArray<UEdGraphPin*>* InPinsToSearch /*= NULL*/) const
{
	const TArray<UEdGraphPin*>* PinsToSearch = InPinsToSearch ? InPinsToSearch : &Pins;

	UEdGraphPin* Pin = NULL;
	for (auto PinIt = PinsToSearch->CreateConstIterator(); PinIt; ++PinIt)
	{
		UEdGraphPin* TestPin = *PinIt;
		if (TestPin && TestPin->PinName == FK2Node_CohtmlEditorBPNodeHelper::CohtmlPinName)
		{
			Pin = TestPin;
			break;
		}
	}
	check(Pin == NULL || Pin->Direction == EGPD_Input);
	return Pin;
}


UEdGraphPin* UK2Node_CohtmlTriggerEventOneOff::GetWorldContextPin() const
{
	UEdGraphPin* Pin = FindPin(FK2Node_CohtmlEditorBPNodeHelper::WorldContextPinName);
	check(Pin == NULL || Pin->Direction == EGPD_Input);
	return Pin;
}

FLinearColor UK2Node_CohtmlTriggerEventOneOff::GetNodeTitleColor() const
{
	return Super::GetNodeTitleColor();
}

FText UK2Node_CohtmlTriggerEventOneOff::GetBaseNodeTitle() const
{
	return NSLOCTEXT("K2Node", "CohtmlTriggerEvent_BaseTitle", "Trigger JavaScript Event");
}

FText UK2Node_CohtmlTriggerEventOneOff::GetNodeTitleFormat() const
{
	return NSLOCTEXT("K2Node", "CohtmlTriggerEvent", "Trigger JavaScript Event \"{EventName}\"");
}

FText UK2Node_CohtmlTriggerEventOneOff::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (TitleType == ENodeTitleType::ListView || TitleType == ENodeTitleType::MenuTitle)
	{
		return GetBaseNodeTitle();
	}
	else if (UEdGraphPin* EventNamePin = GetEventNamePin())
	{
		if (EventNamePin->LinkedTo.Num() > 0)
		{
			// Blueprint will be determined dynamically, so we don't have the name in this case
			return NSLOCTEXT("K2Node", "CohtmlTriggerEvent_Title_Unknown", "Trigger JavaScript Event");
		}
		else if (EventNamePin->DefaultObject == nullptr)
		{
			return NSLOCTEXT("K2Node", "CohtmlTriggerEvent_Title_NONE", "Trigger JavaScript Event");
		}
		else if (CachedNodeTitle.IsOutOfDate((UEdGraphNode*) nullptr))
		{
			FFormatNamedArguments Args;
			Args.Add(TEXT("EventName"), FText::FromString(EventNamePin->DefaultObject->GetName()));
			// FText::Format() is slow, so we cache this to save on performance

			CachedNodeTitle.SetCachedText(FText::Format(GetNodeTitleFormat(), Args), (UEdGraphNode*) nullptr);
		}
	}
	else
	{
		return NSLOCTEXT("K2Node", "CohtmlTriggerEvent_Title_NONE", "Trigger JavaScript Event");
	}

	return CachedNodeTitle;
}

void UK2Node_CohtmlTriggerEventOneOff::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	// actions get registered under specific object-keys; the idea is that
	// actions might have to be updated (or deleted) if their object-key is
	// mutated (or removed)... here we use the node's class (so if the node
	// type disappears, then the action should go with it)
	UClass* ActionKey = GetClass();
	// to keep from needlessly instantiating a UBlueprintNodeSpawner, first
	// check to make sure that the registrar is looking for actions of this type
	// (could be regenerating actions for a specific asset, and therefore the
	// registrar would only accept actions corresponding to that asset)
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

FText UK2Node_CohtmlTriggerEventOneOff::GetMenuCategory() const
{
	return FText::FromString(TEXT(COHTML_PRODUCT));
}

FNodeHandlingFunctor* UK2Node_CohtmlTriggerEventOneOff::CreateNodeHandler(FKismetCompilerContext& CompilerContext) const
{
	return new FNodeHandlingFunctor(CompilerContext);
}

bool UK2Node_CohtmlTriggerEventOneOff::ShouldShowNodeProperties() const
{
	return true;
}

namespace
{
FString GetVariableType(const FCOH_K2NodeName& TypeName, const UEdGraphSchema_K2* K2Schema)
{
	UCohtmlJSEvent::EVariableType Result = UCohtmlJSEvent::VT_Count;
	if (TypeName == K2Schema->PC_Boolean)
	{
		Result = UCohtmlJSEvent::VT_Bool;
	}
	else if (TypeName == K2Schema->PC_Byte)
	{
		Result = UCohtmlJSEvent::VT_Int32;
	}
	else if (TypeName == K2Schema->PC_Int)
	{
		Result = UCohtmlJSEvent::VT_Int32;
	}
	else if (TypeName == K2Schema->PC_Float)
	{
		Result = UCohtmlJSEvent::VT_Float;
	}
	else if (TypeName == K2Schema->PC_String)
	{
		Result = UCohtmlJSEvent::VT_String;
	}
	else if (TypeName == K2Schema->PC_Struct)
	{
		Result = UCohtmlJSEvent::VT_Struct;
	}
	else if (TypeName == K2Schema->PC_Object)
	{
		Result = UCohtmlJSEvent::VT_Object;
	}
	return FString::FormatAsNumber(Result);
}
}

void UK2Node_CohtmlTriggerEventOneOff::ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	static const FName CreateJSEvent_FunctionName = GET_FUNCTION_NAME_CHECKED(UCohtmlBlueprintFunctionLibrary, CreateJSEvent);
	static const FName AddBoolean_FunctionName = GET_FUNCTION_NAME_CHECKED(UCohtmlBlueprintFunctionLibrary, AddBool);
	static const FName AddByte_FunctionName = GET_FUNCTION_NAME_CHECKED(UCohtmlBlueprintFunctionLibrary, AddByte);
	static const FName AddInt32_FunctionName = GET_FUNCTION_NAME_CHECKED(UCohtmlBlueprintFunctionLibrary, AddInt32);
	static const FName AddFloat_FunctionName = GET_FUNCTION_NAME_CHECKED(UCohtmlBlueprintFunctionLibrary, AddFloat);
	static const FName AddString_FunctionName = GET_FUNCTION_NAME_CHECKED(UCohtmlBlueprintFunctionLibrary, AddString);
	static const FName AddObject_FunctionName = GET_FUNCTION_NAME_CHECKED(UCohtmlBlueprintFunctionLibrary, AddObject);
	static const FName AddStruct_FunctionName = GET_FUNCTION_NAME_CHECKED(UCohtmlBlueprintFunctionLibrary, AddStructArg);
	static const FName AddArray_FunctionName = GET_FUNCTION_NAME_CHECKED(UCohtmlBlueprintFunctionLibrary, AddArray);
	static const FName AddArrayOfStructs_FunctionName = GET_FUNCTION_NAME_CHECKED(UCohtmlBlueprintFunctionLibrary, AddArrayOfStructs);
	static const FName TriggerJSEvent_FunctionName = GET_FUNCTION_NAME_CHECKED(UCohtmlBlueprintFunctionLibrary, TriggerJSEvent);

	static const FString JSEvent_ParamName = FString(TEXT("JSEvent"));
	static const FString Arg_ParamName = FString(TEXT("Arg"));
	static const FString ArrayType_ParamName = FString(TEXT("ArrayType"));
	static const FString EventName_ParamName = FString(TEXT("EventName"));
	static const FString Compononent_ParamName = FString(TEXT("Component"));

	UK2Node_CohtmlTriggerEventOneOff* TriggerEventNode = this;

	UEdGraphPin* ExecPin = TriggerEventNode->GetExecPin();
	UEdGraphPin* WorldContextPin = TriggerEventNode->GetWorldContextPin();
	UEdGraphPin* CohtmlPin = TriggerEventNode->GetCohtmlPin();
	UEdGraphPin* EventNamePin = TriggerEventNode->GetEventNamePin();
	UEdGraphPin* ThenPin = TriggerEventNode->GetThenPin();

	if (EventNamePin->LinkedTo.Num() == 0 && EventNamePin->DefaultValue.IsEmpty())
	{
		CompilerContext.MessageLog.Error(
			*LOCTEXT("UK2Node_CohtmlTriggerEventOneOff_Invalid_event_name",
			"Node @@ requires a non-empty event name").ToString(), TriggerEventNode);
		TriggerEventNode->BreakAllNodeLinks();
		return;
	}
	else if (CohtmlPin->LinkedTo.Num() != 1)
	{
		CompilerContext.MessageLog.Error(
			*LOCTEXT("UK2Node_CohtmlTriggerEventOneOff_No_Coherent_component",
			"Node @@ requires a valid " COHTML_PRODUCT " component connection").ToString(), TriggerEventNode);
		TriggerEventNode->BreakAllNodeLinks();
		return;
	}

	////////////////////////////////////////////////////////////////////////////
	// Create 'UCohtmlBlueprintFunctionLibrary::CreateJSEvent' call node
	UK2Node_CallFunction* CallCreateNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(TriggerEventNode, SourceGraph);
	CallCreateNode->FunctionReference.SetExternalMember(CreateJSEvent_FunctionName, UCohtmlBlueprintFunctionLibrary::StaticClass());
	CallCreateNode->AllocateDefaultPins();

	UEdGraphPin* CallCreateExec = CallCreateNode->GetExecPin();
	UEdGraphPin* CallCreateWorldContextPin = CallCreateNode->FindPinChecked(FK2Node_CohtmlEditorBPNodeHelper::WorldContextPinName);
	UEdGraphPin* CallCreateResult = CallCreateNode->GetReturnValuePin();

	// Move 'exec' connection from original node to 'UCohtmlBlueprintFunctionLibrary::CreateJSEvent'
	CompilerContext.MovePinLinksToIntermediate(*ExecPin, *CallCreateExec);

	// Copy the world context connection from the original node to 'UCohtmlBlueprintFunctionLibrary::CreateJSEvent' if necessary
	if (WorldContextPin)
	{
		CompilerContext.MovePinLinksToIntermediate(*WorldContextPin, *CallCreateWorldContextPin);
	}

	////////////////////////////////////////////////////////////////////////////
	// Create "Add" nodes for each pin
	UEdGraphPin* LastThen = CallCreateNode->GetThenPin();

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	for (int32 i = 0; i < TriggerEventNode->Pins.Num(); ++i)
	{
		UEdGraphPin* OriginalPin = TriggerEventNode->Pins[i];
		if (IsUserDefinedPin(OriginalPin))
		{
			if (!IsSupportedArgumentType(OriginalPin))
			{
				auto PinType = OriginalPin->PinType.PinCategory;
				if (OriginalPin->PinType.PinSubCategoryObject.IsValid())
				{
					// Try to get as specific as possible
#if defined(COHTML_UE4_418_SUPPORT)
					PinType = OriginalPin->PinType.PinSubCategoryObject->GetName();
#else
					PinType = OriginalPin->PinType.PinSubCategoryObject->GetFName();
#endif
				}

				CompilerContext.MessageLog.Error(
					*FString::Printf(
						TEXT("Trigger event node @@ supports only primitive types, strings and UCLASS objects. Type \"%s\" of argument \"%s\" is invalid."),
#if defined(COHTML_UE4_418_SUPPORT)
						*PinType, *OriginalPin->PinName),
#else
						*PinType.ToString(), *OriginalPin->PinName.ToString()),
#endif
					TriggerEventNode);
				TriggerEventNode->BreakAllNodeLinks();
				return;
			}

			// Call the specific function for each supported type
			const auto& ArgType = OriginalPin->PinType.PinCategory;
			FName AddArgFuncName;
			bool bIsTypeArray =
#if defined(COHTML_UE4_416_SUPPORT)
				OriginalPin->PinType.bIsArray;
#else
				OriginalPin->PinType.IsArray();
#endif
			if (bIsTypeArray && ArgType != K2Schema->PC_Struct)
			{
				AddArgFuncName = AddArray_FunctionName;
			}
			else if (bIsTypeArray && ArgType == K2Schema->PC_Struct)
			{
				AddArgFuncName = AddArrayOfStructs_FunctionName;
			}
			else if (ArgType == K2Schema->PC_Boolean)
			{
				AddArgFuncName = AddBoolean_FunctionName;
			}
			else if (ArgType == K2Schema->PC_Byte)
			{
				AddArgFuncName = AddByte_FunctionName;
			}
			else if (ArgType == K2Schema->PC_Int)
			{
				AddArgFuncName = AddInt32_FunctionName;
			}
			else if (ArgType == K2Schema->PC_Float)
			{
				AddArgFuncName = AddFloat_FunctionName;
			}
			else if (ArgType == K2Schema->PC_String)
			{
				AddArgFuncName = AddString_FunctionName;
			}
			else if (ArgType == K2Schema->PC_Struct)
			{
				AddArgFuncName = AddStruct_FunctionName;
			}
			else if (ArgType == K2Schema->PC_Object)
			{
				AddArgFuncName = AddObject_FunctionName;
			}

			UK2Node_CallFunction* AddArgNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(TriggerEventNode, SourceGraph);
			AddArgNode->FunctionReference.SetExternalMember(AddArgFuncName, UCohtmlBlueprintFunctionLibrary::StaticClass());
			AddArgNode->AllocateDefaultPins();

			UEdGraphPin* AddArgExec = AddArgNode->GetExecPin();
			UEdGraphPin* AddArgJSEventPin = AddArgNode->FindPinChecked(JSEvent_ParamName);
			UEdGraphPin* AddArgArgPin = AddArgNode->FindPinChecked(Arg_ParamName);
			UEdGraphPin* ArrayTypePin = bIsTypeArray && ArgType != K2Schema->PC_Struct ? AddArgNode->FindPinChecked(ArrayType_ParamName) : nullptr;
			UEdGraphPin* AddArgThen = AddArgNode->GetThenPin();

			if (ArrayTypePin)
			{
				ArrayTypePin->DefaultValue = GetVariableType(ArgType, K2Schema);
			}

			AddArgArgPin->PinType = OriginalPin->PinType;
			// Connect the LastThen node to the add argument's Exec node
			LastThen->MakeLinkTo(AddArgExec);

			// Connect the JSEvent instance
			CallCreateResult->MakeLinkTo(AddArgJSEventPin);

			// Move the argument link from the original node to the new one, if any
			if (OriginalPin->LinkedTo.Num() > 0)
			{
				CompilerContext.MovePinLinksToIntermediate(*OriginalPin, *AddArgArgPin);
			}
			else
			{
				AddArgArgPin->DefaultValue = OriginalPin->DefaultValue;
			}

			// Update the LastThen pin
			LastThen = AddArgThen;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// Create a "Trigger event" node
	UK2Node_CallFunction* InvokeTriggerNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(TriggerEventNode, SourceGraph);
	InvokeTriggerNode->FunctionReference.SetExternalMember(TriggerJSEvent_FunctionName, UCohtmlBlueprintFunctionLibrary::StaticClass());
	InvokeTriggerNode->AllocateDefaultPins();

	UEdGraphPin* InvokeTriggerExec = InvokeTriggerNode->GetExecPin();
	UEdGraphPin* InvokeTriggerComponentPin = InvokeTriggerNode->FindPinChecked(Compononent_ParamName);
	UEdGraphPin* InvokeTriggerEventNamePin = InvokeTriggerNode->FindPinChecked(EventName_ParamName);
	UEdGraphPin* InvokeTriggerJSEventPin = InvokeTriggerNode->FindPinChecked(JSEvent_ParamName);
	UEdGraphPin* InvokeTriggerThen = InvokeTriggerNode->GetThenPin();

	// Connect the LastThen node to the Invoke Exec node
	LastThen->MakeLinkTo(InvokeTriggerExec);
	LastThen = InvokeTriggerThen;

	// Move the Cohtml component pin
	CompilerContext.MovePinLinksToIntermediate(*CohtmlPin, *InvokeTriggerComponentPin);

	// Move the event name pin
	CompilerContext.MovePinLinksToIntermediate(*EventNamePin, *InvokeTriggerEventNamePin);

	// Link the UCohtmlBlueprintFunctionLibrary::Create node to the Invoke input
	CallCreateResult->MakeLinkTo(InvokeTriggerJSEventPin);

	//////////////////////////////////////////////////////////////////////////
	// Move 'then' connection from the original node to the last 'then'
	CompilerContext.MovePinLinksToIntermediate(*ThenPin, *LastThen);

	TriggerEventNode->BreakAllNodeLinks();
}

#undef LOCTEXT_NAMESPACE
