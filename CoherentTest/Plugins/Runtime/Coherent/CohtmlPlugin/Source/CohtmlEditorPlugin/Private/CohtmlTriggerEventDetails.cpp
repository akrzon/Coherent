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
#include "CohtmlTriggerEventDetails.h"

#include <Kismet2/BlueprintEditorUtils.h>
#include <DetailCategoryBuilder.h>
#include <DetailLayoutBuilder.h>
#include <DetailWidgetRow.h>
#include <IDetailChildrenBuilder.h>
#include <IDetailCustomNodeBuilder.h>
#include <IDetailsView.h>
#include <PropertyCustomizationHelpers.h>
#include <ScopedTransaction.h>
#include <SPinTypeSelector.h>
#include <EdGraph/EdGraphPin.h>

#include <Engine/World.h>
#include <Widgets/Input/SEditableTextBox.h>
#include <Widgets/Input/SCheckBox.h>
#include <Widgets/Input/SButton.h>
#include <Widgets/Images/SImage.h>
#include <SlateOptMacros.h>

#include "K2Node_CohtmlTriggerEventOneOff.h"

#define LOCTEXT_NAMESPACE "CohtmlTriggerEventDetails"

#define ECheckBoxState_Coherent ECheckBoxState
typedef ECheckBoxState ECheckBoxState_Coherent_Type;

////////////////////////////////////////////////////////////////////////////////
class FCohtmlTriggerEventArgumentGroupLayout : public IDetailCustomNodeBuilder, public TSharedFromThis<FCohtmlTriggerEventArgumentGroupLayout>
{
public:
	FCohtmlTriggerEventArgumentGroupLayout(TWeakPtr<FCohtmlTriggerEventDetails> TriggerEventDetails, UK2Node_EditablePinBase* InTargetNode)
		: TriggerEventDetailsPtr(TriggerEventDetails)
		, TargetNode(InTargetNode) {}

private:
	/** IDetailCustomNodeBuilder Interface*/
	virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren) override;
	virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override {}
	virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;
	virtual void Tick(float DeltaTime) override {}
	virtual bool RequiresTick() const override { return false; }
	virtual FName GetName() const override { return NAME_None; }
	virtual bool InitiallyCollapsed() const override { return false; }

private:
	/** The parent graph action details customization */
	TWeakPtr<FCohtmlTriggerEventDetails> TriggerEventDetailsPtr;

	/** The target node that this argument is on */
	TWeakObjectPtr<UK2Node_EditablePinBase> TargetNode;
};

/** Custom struct for each argument in the function editing details */
class FCohtmlTriggerEventArgumentLayout : public IDetailCustomNodeBuilder, public TSharedFromThis<FCohtmlTriggerEventArgumentLayout>
{
public:
	FCohtmlTriggerEventArgumentLayout(TWeakPtr<FUserPinInfo> PinInfo, UK2Node_EditablePinBase* InTargetNode, TWeakPtr<FCohtmlTriggerEventDetails> TriggerEventDetails, FName InArgName, bool bInHasDefaultValue)
		: TriggerEventDetailsPtr(TriggerEventDetails)
		, ParamItemPtr(PinInfo)
		, TargetNode(InTargetNode)
		, bHasDefaultValue(bInHasDefaultValue)
		, ArgumentName(InArgName) {}

private:
	/** IDetailCustomNodeBuilder Interface*/
	virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren) override {}
	virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;
	virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;
	virtual void Tick(float DeltaTime) override {}
	virtual bool RequiresTick() const override { return false; }
	virtual FName GetName() const override { return ArgumentName; }
	virtual bool InitiallyCollapsed() const override { return true; }

private:
	/** Determines if this pin should not be editable */
	bool ShouldPinBeReadOnly() const;

	/** Callbacks for all the functionality for modifying arguments */
	void OnRemoveClicked();
	FReply OnArgMoveUp();
	FReply OnArgMoveDown();

	FText OnGetArgNameText() const;
	void OnArgNameChange(const FText& InNewText);
	void OnArgNameTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit);

	FEdGraphPinType OnGetPinInfo() const;
	void PinInfoChanged(const FEdGraphPinType& PinType);
	void OnPrePinInfoChange(const FEdGraphPinType& PinType);

	/** Returns whether the "Pass-by-Reference" checkbox is checked or not */
	ECheckBoxState_Coherent_Type IsRefChecked() const;

	/** Handles toggling the "Pass-by-Reference" checkbox */
	void OnRefCheckStateChanged(ECheckBoxState_Coherent_Type InState);

	FText OnGetArgDefaultValueText() const;
	void OnArgDefaultValueCommitted(const FText& NewText, ETextCommit::Type InTextCommit);

private:
	/** The parent graph action details customization */
	TWeakPtr<FCohtmlTriggerEventDetails> TriggerEventDetailsPtr;

	/** The argument pin that this layout reflects */
	TWeakPtr<FUserPinInfo> ParamItemPtr;

	/** The target node that this argument is on */
	UK2Node_EditablePinBase* TargetNode;

	/** Whether or not this builder should have a default value edit control (input args only) */
	bool bHasDefaultValue;

	/** The name of this argument for remembering expansion state */
	FName ArgumentName;

	/** Holds a weak pointer to the argument name widget, used for error notifications */
	TWeakPtr<SEditableTextBox> ArgumentNameWidget;
};

////////////////////////////////////////////////////////////////////////////////

void FCohtmlTriggerEventArgumentGroupLayout::SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren)
{
	TriggerEventDetailsPtr.Pin()->SetRefreshDelegate(InOnRegenerateChildren, TargetNode == TriggerEventDetailsPtr.Pin()->GetCohtmlNode().Get());
}

void FCohtmlTriggerEventArgumentGroupLayout::GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder)
{
	if (TargetNode.IsValid())
	{
		TArray<TSharedPtr<FUserPinInfo>> Pins = TargetNode->UserDefinedPins;

		bool bIsInputNode = TargetNode == TriggerEventDetailsPtr.Pin()->GetCohtmlNode().Get();
		for (int32 i = 0; i < Pins.Num(); ++i)
		{
			FString ArgumentLayoutName = (bIsInputNode ? TEXT("InputArgument") : TEXT("OutputArgument")) + FString::FromInt(i);
			TSharedRef<class FCohtmlTriggerEventArgumentLayout> BlueprintArgumentLayout = MakeShareable(new FCohtmlTriggerEventArgumentLayout(
				TWeakPtr<FUserPinInfo>(Pins[i]),
				TargetNode.Get(),
				TriggerEventDetailsPtr,
				FName(*ArgumentLayoutName),
				bIsInputNode));
#if defined(COHTML_UE4_416_SUPPORT)
			ChildrenBuilder.AddChildCustomBuilder(BlueprintArgumentLayout);
#else
			ChildrenBuilder.AddCustomBuilder(BlueprintArgumentLayout);
#endif
		}
	}
}

// Internal
static bool ShouldAllowWildcard(UK2Node_EditablePinBase* TargetNode)
{
	// allow wildcards for tunnel nodes in macro graphs
	if (TargetNode->IsA(UK2Node_Tunnel::StaticClass()))
	{
		const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
		return (K2Schema->GetGraphType(TargetNode->GetGraph()) == GT_Macro);
	}

	return false;
}

void FCohtmlTriggerEventArgumentLayout::GenerateHeaderRowContent(FDetailWidgetRow& NodeRow)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

#if !defined(COHTML_UE4_412_SUPPORT)
	ETypeTreeFilter TypeTreeFilter = static_cast<ETypeTreeFilter>(
		TargetNode->CanModifyExecutionWires() * static_cast<uint8>(ETypeTreeFilter::AllowExec) ||
		ShouldAllowWildcard(TargetNode) * static_cast<uint8>(ETypeTreeFilter::AllowWildcard));
#endif

	NodeRow
		.NameContent()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(1)
			.VAlign(VAlign_Center)
			[
				SAssignNew(ArgumentNameWidget, SEditableTextBox)
				.Text(this, &FCohtmlTriggerEventArgumentLayout::OnGetArgNameText)
				.OnTextChanged(this, &FCohtmlTriggerEventArgumentLayout::OnArgNameChange)
				.OnTextCommitted(this, &FCohtmlTriggerEventArgumentLayout::OnArgNameTextCommitted)
				.Font(IDetailLayoutBuilder::GetDetailFont())
				.IsEnabled(!ShouldPinBeReadOnly())
			]
		]
	.ValueContent()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(1)
			.VAlign(VAlign_Center)
			.Padding(0.0f, 0.0f, 4.0f, 0.0f)
			[
				SNew(SPinTypeSelector, FGetPinTypeTree::CreateUObject(K2Schema, &UEdGraphSchema_K2::GetVariableTypeTree))
				.TargetPinType(this, &FCohtmlTriggerEventArgumentLayout::OnGetPinInfo)
				.OnPinTypePreChanged(this, &FCohtmlTriggerEventArgumentLayout::OnPrePinInfoChange)
				.OnPinTypeChanged(this, &FCohtmlTriggerEventArgumentLayout::PinInfoChanged)
				.Schema(K2Schema)
#if defined (COHTML_UE4_412_SUPPORT)
				.bAllowExec(TargetNode->CanModifyExecutionWires())
				.bAllowWildcard(ShouldAllowWildcard(TargetNode))
#else
				.TypeTreeFilter(TypeTreeFilter)
#endif
				.IsEnabled(!ShouldPinBeReadOnly())
				.Font(IDetailLayoutBuilder::GetDetailFont())
			]
			+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Right)
				.VAlign(VAlign_Center)
				[
					PropertyCustomizationHelpers::MakeClearButton(FSimpleDelegate::CreateSP(this, &FCohtmlTriggerEventArgumentLayout::OnRemoveClicked))
				]
		];
}

void FCohtmlTriggerEventArgumentLayout::GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder)
{
	if (bHasDefaultValue)
	{
#if defined(COHTML_UE4_416_SUPPORT)
		ChildrenBuilder.AddChildContent(LOCTEXT("FunctionArgDetailsDefaultValue", "Default Value"))
#else
		ChildrenBuilder.AddCustomRow(LOCTEXT("FunctionArgDetailsDefaultValue", "Default Value"))
#endif
			.NameContent()
			[
				SNew(STextBlock)
				.Text(LOCTEXT("FunctionArgDetailsDefaultValue", "Default Value"))
				.ToolTipText(LOCTEXT("FunctionArgDetailsDefaultValueTooltip", "The name of the argument that will be visible to users of this graph."))
				.Font(IDetailLayoutBuilder::GetDetailFont())
			]
		.ValueContent()
			[
				SNew(SEditableTextBox)
				.Text(this, &FCohtmlTriggerEventArgumentLayout::OnGetArgDefaultValueText)
				.OnTextCommitted(this, &FCohtmlTriggerEventArgumentLayout::OnArgDefaultValueCommitted)
				.IsEnabled(!ShouldPinBeReadOnly())
				.Font(IDetailLayoutBuilder::GetDetailFont())
			];

#if defined (COHTML_UE4_416_SUPPORT)
			ChildrenBuilder.AddChildContent(LOCTEXT("FunctionArgDetailsPassByReference", "Pass-by-Reference"))
#else
			ChildrenBuilder.AddCustomRow(LOCTEXT("FunctionArgDetailsPassByReference", "Pass-by-Reference"))
#endif
			.NameContent()
			[
				SNew(STextBlock)
				.Text(LOCTEXT("FunctionArgDetailsPassByReference", "Pass-by-Reference"))
				.ToolTipText(LOCTEXT("FunctionArgDetailsPassByReferenceTooltip", "Pass this paremeter by reference?"))
				.Font(IDetailLayoutBuilder::GetDetailFont())
			]
		.ValueContent()
			[
				SNew(SCheckBox)
				.IsChecked(this, &FCohtmlTriggerEventArgumentLayout::IsRefChecked)
				.OnCheckStateChanged(this, &FCohtmlTriggerEventArgumentLayout::OnRefCheckStateChanged)
				.IsEnabled(!ShouldPinBeReadOnly())
			];
	}

#if defined(COHTML_UE4_416_SUPPORT)
		ChildrenBuilder.AddChildContent(LOCTEXT("FunctionArgDetailsMoving", "Moving"))
#else
		ChildrenBuilder.AddCustomRow(LOCTEXT("FunctionArgDetailsMoving", "Moving"))
#endif
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			[
				SNew(SSpacer)
			]
			+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(2, 0)
				[
					SNew(SButton)
					.ContentPadding(0)
					.OnClicked(this, &FCohtmlTriggerEventArgumentLayout::OnArgMoveUp)
					[
						SNew(SImage)
						.Image(FEditorStyle::GetBrush("BlueprintEditor.Details.ArgUpButton"))
					]
				]
			+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(2, 0)
				[
					SNew(SButton)
					.ContentPadding(0)
					.OnClicked(this, &FCohtmlTriggerEventArgumentLayout::OnArgMoveDown)
					[
						SNew(SImage)
						.Image(FEditorStyle::GetBrush("BlueprintEditor.Details.ArgDownButton"))
					]
				]
		];
}

void FCohtmlTriggerEventArgumentLayout::OnRemoveClicked()
{
	if (ParamItemPtr.IsValid())
	{
		const FScopedTransaction Transaction(LOCTEXT("RemoveParam", "Remove Parameter"));
		TargetNode->Modify();

		TargetNode->RemoveUserDefinedPin(ParamItemPtr.Pin());

		TriggerEventDetailsPtr.Pin()->OnParamsChanged(TargetNode, true);
	}
}

FReply FCohtmlTriggerEventArgumentLayout::OnArgMoveUp()
{
	const int32 ThisParamIndex = TargetNode->UserDefinedPins.Find(ParamItemPtr.Pin());
	const int32 NewParamIndex = ThisParamIndex - 1;
	if (ThisParamIndex != INDEX_NONE && NewParamIndex >= 0)
	{
		const FScopedTransaction Transaction(LOCTEXT("K2_MovePinUp", "Move Pin Up"));
		TargetNode->Modify();

		TargetNode->UserDefinedPins.Swap(ThisParamIndex, NewParamIndex);
		TriggerEventDetailsPtr.Pin()->OnParamsChanged(TargetNode, true);
	}
	return FReply::Handled();
}

FReply FCohtmlTriggerEventArgumentLayout::OnArgMoveDown()
{
	const int32 ThisParamIndex = TargetNode->UserDefinedPins.Find(ParamItemPtr.Pin());
	const int32 NewParamIndex = ThisParamIndex + 1;
	if (ThisParamIndex != INDEX_NONE && NewParamIndex < TargetNode->UserDefinedPins.Num())
	{
		const FScopedTransaction Transaction(LOCTEXT("K2_MovePinUp", "Move Pin Up"));
		TargetNode->Modify();

		TargetNode->UserDefinedPins.Swap(ThisParamIndex, NewParamIndex);
		TriggerEventDetailsPtr.Pin()->OnParamsChanged(TargetNode, true);
	}
	return FReply::Handled();
}

bool FCohtmlTriggerEventArgumentLayout::ShouldPinBeReadOnly() const
{
	const UEdGraphSchema_K2* Schema = GetDefault<UEdGraphSchema_K2>();

	if (TargetNode && ParamItemPtr.IsValid())
	{
		// Right now, we only care that the user is unable to edit the auto-generated "then" pin
		if ((ParamItemPtr.Pin()->PinType.PinCategory == Schema->PC_Exec) && (!TargetNode->CanModifyExecutionWires()))
		{
			return true;
		}
	}

	return false;
}

FText FCohtmlTriggerEventArgumentLayout::OnGetArgNameText() const
{
	if (ParamItemPtr.IsValid())
	{
#if defined(COHTML_UE4_418_SUPPORT)
		return FText::FromString(ParamItemPtr.Pin()->PinName);
#else
		return FText::FromName(ParamItemPtr.Pin()->PinName);
#endif
	}
	return FText();
}

void FCohtmlTriggerEventArgumentLayout::OnArgNameChange(const FText& InNewText)
{
	bool bVerified = true;

	FText ErrorMessage;

	if (InNewText.IsEmpty())
	{
		ErrorMessage = LOCTEXT("EmptyArgument", "Name cannot be empty!");
		bVerified = false;
	}
	else
	{
		const auto& OldName = ParamItemPtr.Pin()->PinName;
		bVerified = TriggerEventDetailsPtr.Pin()->OnVerifyPinRename(TargetNode, OldName, InNewText.ToString(), ErrorMessage);
	}

	if (!bVerified)
	{
		ArgumentNameWidget.Pin()->SetError(ErrorMessage);
	}
	else
	{
		ArgumentNameWidget.Pin()->SetError(FText::GetEmpty());
	}
}

void FCohtmlTriggerEventArgumentLayout::OnArgNameTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit)
{
	if (!NewText.IsEmpty() && TargetNode && ParamItemPtr.IsValid() && TriggerEventDetailsPtr.IsValid() && !ShouldPinBeReadOnly())
	{
		const auto& OldName = ParamItemPtr.Pin()->PinName;
		const FString& NewName = NewText.ToString();
#if defined(COHTML_UE4_418_SUPPORT)
		if (OldName != NewName)
#else
		if (OldName.ToString() != NewName)
#endif
		{
			if (TriggerEventDetailsPtr.Pin()->OnPinRenamed(TargetNode, OldName, NewName))
			{
#if defined(COHTML_UE4_418_SUPPORT)
				ParamItemPtr.Pin()->PinName = NewName;
#else
				ParamItemPtr.Pin()->PinName = *NewName;
#endif
			}
		}
	}
}

FEdGraphPinType FCohtmlTriggerEventArgumentLayout::OnGetPinInfo() const
{
	if (ParamItemPtr.IsValid())
	{
		return ParamItemPtr.Pin()->PinType;
	}
	return FEdGraphPinType();
}

ECheckBoxState_Coherent_Type FCohtmlTriggerEventArgumentLayout::IsRefChecked() const
{
	FEdGraphPinType PinType = OnGetPinInfo();
	return PinType.bIsReference ? ECheckBoxState_Coherent::Checked : ECheckBoxState_Coherent::Unchecked;
}

void FCohtmlTriggerEventArgumentLayout::OnRefCheckStateChanged(ECheckBoxState_Coherent_Type InState)
{
	FEdGraphPinType PinType = OnGetPinInfo();
	PinType.bIsReference = (InState == ECheckBoxState_Coherent::Checked) ? true : false;
	PinInfoChanged(PinType);
}

void FCohtmlTriggerEventArgumentLayout::PinInfoChanged(const FEdGraphPinType& PinType)
{
	if (ParamItemPtr.IsValid() && FBlueprintEditorUtils::IsPinTypeValid(PinType))
	{
		ParamItemPtr.Pin()->PinType = PinType;
		if (TriggerEventDetailsPtr.IsValid())
		{
			if (!ShouldPinBeReadOnly())
			{
				TriggerEventDetailsPtr.Pin()->OnParamsChanged(TargetNode);
			}
		}
	}
}

void FCohtmlTriggerEventArgumentLayout::OnPrePinInfoChange(const FEdGraphPinType& PinType)
{
	if (!ShouldPinBeReadOnly() && TargetNode)
	{
		TargetNode->Modify();
	}
}

FText FCohtmlTriggerEventArgumentLayout::OnGetArgDefaultValueText() const
{
	if (ParamItemPtr.IsValid())
	{
		return FText::FromString(ParamItemPtr.Pin()->PinDefaultValue);
	}
	return FText();
}

void FCohtmlTriggerEventArgumentLayout::OnArgDefaultValueCommitted(const FText& NewText, ETextCommit::Type InTextCommit)
{
	if (!NewText.IsEmpty() && !ShouldPinBeReadOnly() && (InTextCommit == ETextCommit::OnEnter || InTextCommit == ETextCommit::OnUserMovedFocus) && ParamItemPtr.IsValid())
	{
		bool bSuccess = TargetNode->ModifyUserDefinedPinDefaultValue(ParamItemPtr.Pin(), NewText.ToString());

		if (bSuccess)
		{
			TriggerEventDetailsPtr.Pin()->OnParamsChanged(TargetNode);
		}
	}
}


////////////////////////////////////////////////////////////////////////////////

TSharedRef<IDetailCustomization> FCohtmlTriggerEventDetails::MakeInstance()
{
	return MakeShareable(new FCohtmlTriggerEventDetails);
}

bool FCohtmlTriggerEventDetails::IsPinNameUnique(const FCOH_K2NodeName& TestName) const
{
	UK2Node_EditablePinBase * CohtmlNode = CohtmlNodePtr.Get();

	// Check the built in pins
	for (TArray<UEdGraphPin*>::TIterator it(CohtmlNode->Pins); it; ++it)
	{
		if ((*it)->PinName == TestName)
		{
			return false;
		}
	}

	return true;
}

void FCohtmlTriggerEventDetails::GenerateUniqueParameterName(const FString& BaseName, FCOH_K2NodeName& Result) const
{
	UK2Node_EditablePinBase * CohtmlNode = CohtmlNodePtr.Get();
	check(CohtmlNode);

#if defined(COHTML_UE4_418_SUPPORT)
	Result = BaseName;
#else
	Result = *BaseName;
#endif

	int UniqueNum = 0;
	// Prevent the unique name from being the same as another of the UFunction's properties
	while (!IsPinNameUnique(Result))
	{
#if defined(COHTML_UE4_418_SUPPORT)
		Result = FString::Printf(TEXT("%s%d"), *BaseName, ++UniqueNum);
#else
		Result = *FString::Printf(TEXT("%s%d"), *BaseName, ++UniqueNum);
#endif
	}
}

FReply FCohtmlTriggerEventDetails::OnAddNewInputClicked()
{
	UK2Node_EditablePinBase * CohtmlNode = CohtmlNodePtr.Get();

	if (CohtmlNode)
	{
		const FScopedTransaction Transaction(LOCTEXT("AddInParam", "Add In Parameter"));
		CohtmlNode->Modify();

		const UEdGraphSchema_K2* Schema = GetDefault<UEdGraphSchema_K2>();

		// Default to bool when creating a new pin
#if defined(COHTML_UE4_414_SUPPORT)
		FEdGraphPinType PinType(Schema->PC_Boolean, TEXT(""), NULL, false, false);
#elif defined(COHTML_UE4_416_SUPPORT)
		FEdGraphPinType PinType(Schema->PC_Boolean, TEXT(""), NULL, false, false, false, false, FEdGraphTerminalType());
#else
		FEdGraphPinType PinType(Schema->PC_Boolean, TEXT(""), NULL, EPinContainerType::None, false, FEdGraphTerminalType());
#endif

		FCOH_K2NodeName NewPinName;
		GenerateUniqueParameterName(TEXT("NewParam"), NewPinName);
		CohtmlNode->CreateUserDefinedPin(NewPinName, PinType, EGPD_Input);
		OnParamsChanged(CohtmlNode, true);
	}

	return FReply::Handled();
}

bool FCohtmlTriggerEventDetails::OnVerifyPinRename(UK2Node_EditablePinBase* InTargetNode, const FCOH_K2NodeName& InOldName, const FString& InNewName, FText& OutErrorMessage)
{
	// If the name is unchanged, allow the name
#if defined(COHTML_UE4_418_SUPPORT)
	if (InOldName == InNewName)
#else
	if (InOldName.ToString() == InNewName)
#endif
	{
		return true;
	}

	if (InTargetNode)
	{
#if defined(COHTML_UE4_418_SUPPORT)
		if (!IsPinNameUnique(InNewName))
#else
		if (!IsPinNameUnique(*InNewName))
#endif
		{
			OutErrorMessage = LOCTEXT("ConflictsWithProperty", "Conflicts with another another local variable or function parameter!");
			return false;
		}
	}

	return true;
}

bool FCohtmlTriggerEventDetails::OnPinRenamed(UK2Node_EditablePinBase* TargetNode, const FCOH_K2NodeName& OldName, const FString& NewName)
{
	// Before changing the name, verify the name
	FText ErrorMessage;
	if (!OnVerifyPinRename(TargetNode, OldName, NewName, ErrorMessage))
	{
		return false;
	}

	UEdGraph* Graph = GetGraph();

	if (TargetNode)
	{
#if defined(COHTML_UE4_418_SUPPORT)
		const FCOH_K2NodeName& NewPinName = NewName;
#else
		const FCOH_K2NodeName NewPinName = *NewName;
#endif

		// Test
		if (ERenamePinResult::ERenamePinResult_NameCollision == TargetNode->RenameUserDefinedPin(OldName, NewPinName, true))
		{
			return false;
		}

		// Update
		TargetNode->RenameUserDefinedPin(OldName, NewPinName, false);

		if (UBlueprint* Blueprint = TargetNode->GetBlueprint())
		{
			FBlueprintEditorUtils::MarkBlueprintAsModified(Blueprint);
		}
	}

	return true;
}

void FCohtmlTriggerEventDetails::OnParamsChanged(UK2Node_EditablePinBase* TargetNode, bool bForceRefresh)
{
	// TargetNode can be null, if we just removed the result node because there are no more out params
	if (TargetNode)
	{
		RegenerateInputsChildrenDelegate.ExecuteIfBound();
		RegenerateOutputsChildrenDelegate.ExecuteIfBound();

		// Reconstruct the entry/exit definition and recompile the blueprint to make sure the signature has changed before any fixups
		TargetNode->ReconstructNode();

		UBlueprint* Blueprint = TargetNode->GetBlueprint();
		if (Blueprint)
		{
			FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);
		}

		if (UEdGraph* Graph = GetGraph())
		{
			Graph->NotifyGraphChanged();
		}

		if (Blueprint)
		{
			FBlueprintEditorUtils::MarkBlueprintAsModified(Blueprint);
		}
	}
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void FCohtmlTriggerEventDetails::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
#if defined(COHTML_UE4_417_SUPPORT)
	ObjectsBeingEdited = DetailLayout.GetDetailsView().GetSelectedObjects();
#else
	ObjectsBeingEdited = DetailLayout.GetDetailsView()->GetSelectedObjects();
#endif

	SetCohtmlNode();

	UK2Node_EditablePinBase* CohtmlNode = CohtmlNodePtr.Get();

	IDetailCategoryBuilder& InputsCategory = DetailLayout.EditCategory("Inputs", LOCTEXT("FunctionDetailsInputs", "Inputs"));

	TSharedRef<FCohtmlTriggerEventArgumentGroupLayout> InputArgumentGroup =
		MakeShareable(new FCohtmlTriggerEventArgumentGroupLayout(SharedThis(this), CohtmlNode));
	InputsCategory.AddCustomBuilder(InputArgumentGroup);

	InputsCategory.AddCustomRow(LOCTEXT("FunctionNewInputArg", "New"))
		[
			SNew(SBox)
			.HAlign(HAlign_Right)
			[
				SNew(SButton)
				.Text(LOCTEXT("FunctionNewInputArg", "New"))
				.OnClicked(this, &FCohtmlTriggerEventDetails::OnAddNewInputClicked)
			]
		];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void FCohtmlTriggerEventDetails::SetCohtmlNode()
{
	CohtmlNodePtr = nullptr;

	if (UK2Node_EditablePinBase* Node = GetEditableNode())
	{
		CohtmlNodePtr = Node;
	}
}

UEdGraph* FCohtmlTriggerEventDetails::GetGraph() const
{
	check(ObjectsBeingEdited.Num() > 0);

	if (ObjectsBeingEdited.Num() == 1)
	{
		UObject* const Object = ObjectsBeingEdited[0].Get();
		if (!Object)
		{
			return nullptr;
		}

		if (Object->IsA<UK2Node_CohtmlTriggerEventOneOff>())
		{
			return Cast<UK2Node>(Object)->GetGraph();
		}
	}

	return nullptr;
}

UK2Node_EditablePinBase* FCohtmlTriggerEventDetails::GetEditableNode() const
{
	check(ObjectsBeingEdited.Num() > 0);

	if (ObjectsBeingEdited.Num() == 1)
	{
		UObject* const Object = ObjectsBeingEdited[0].Get();
		if (!Object)
		{
			return nullptr;
		}

		if (Object->IsA<UK2Node_CohtmlTriggerEventOneOff>())
		{
			return Cast<UK2Node_CohtmlTriggerEventOneOff>(Object);
		}
	}

	return nullptr;
}

void FCohtmlTriggerEventDetails::SetRefreshDelegate(FSimpleDelegate RefreshDelegate, bool bForInputs)
{
	((bForInputs) ? RegenerateInputsChildrenDelegate : RegenerateOutputsChildrenDelegate) = RefreshDelegate;
}

#undef LOCTEXT_NAMESPACE