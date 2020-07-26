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

#include <K2Node_CallFunction.h>
#include <K2Node_Tunnel.h>
#include "EdGraph/EdGraphNodeUtils.h" // for FNodeTextCache
#include "K2Node_EditablePinBase.h"
#include "K2Node_CohtmlTriggerEventOneOff.generated.h"

UCLASS(BlueprintType, Blueprintable)
class COHTMLEDITORPLUGIN_API UK2Node_CohtmlTriggerEventOneOff : public UK2Node_EditablePinBase
{
	GENERATED_UCLASS_BODY()

	// Begin UEdGraphNode interface.
	virtual void AllocateDefaultPins() override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;
	virtual FText GetTooltipText() const override;
	virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	// End UEdGraphNode interface.

	// Begin UK2Node interface
	virtual bool IsNodeSafeToIgnore() const override { return true; }
	virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual FText GetMenuCategory() const override;
	virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;

	virtual bool ShouldShowNodeProperties() const override;
	// End UK2Node interface

	// Begin UK2Node_EditablePinBase
	virtual UEdGraphPin* CreatePinFromUserDefinition(const TSharedPtr<FUserPinInfo> NewPinInfo) override;
	// End UK2Node_EditablePinBase

	/** See if this is a user-defined pin, or a 'default' pin */
	bool IsUserDefinedPin(UEdGraphPin* Pin);

	/** See if this pin is of supported type for argument binding */
	bool IsSupportedArgumentType(UEdGraphPin* Pin);

	/** Get the then output pin */
	UEdGraphPin* GetThenPin() const;
	/** Get the event name pin */
	UEdGraphPin* GetEventNamePin(const TArray<UEdGraphPin*>* InPinsToSearch = nullptr) const;
	/** Get the Cohtml component pin */
	UEdGraphPin* GetCohtmlPin(const TArray<UEdGraphPin*>* InPinsToSearch = nullptr) const;
	/** Get the world context input pin, can return NULL */
	UEdGraphPin* GetWorldContextPin() const;

protected:
	/** Gets the default node title when no class is selected */
	FText GetBaseNodeTitle() const;
	/** Gets the node title when a class has been selected. */
	FText GetNodeTitleFormat() const;

	/**
	* Takes the specified "MutatablePin" and sets its 'PinToolTip' field (according
	* to the specified description)
	*
	* @param   MutatablePin	The pin you want to set tool-tip text on
	* @param   PinDescription	A string describing the pin's purpose
	*/
	void SetPinToolTip(UEdGraphPin& MutatablePin, const FText& PinDescription) const;

	/** Tooltip text for this node. */
	FText NodeTooltip;

private:
	/** Constructing FText strings can be costly, so we cache the node's title */
	FNodeTextCache CachedNodeTitle;
};

