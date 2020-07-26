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

#include "CohtmlJSEvent.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "CohtmlBlueprintFunctionLibrary.generated.h"

class UCohtmlJSEvent;

UCLASS(meta=(DisplayName = "Prysm Blueprint Function Library"))
class COHTMLPLUGIN_API UCohtmlBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
public:
	/** Creates a UCohtmlJSEvent object */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", DisplayName = "Trigger JavaScript Event", BlueprintInternalUseOnly = "true"), Category = "Prysm")
	static UCohtmlJSEvent* CreateJSEvent(UObject* WorldContextObject);

	/** Adds a Byte parameter to the event */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Prysm")
	static void AddByte(UCohtmlJSEvent* JSEvent, uint8 Arg);

	/** Adds an Integer parameter to the event */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Prysm")
	static void AddInt32(UCohtmlJSEvent* JSEvent, int32 Arg);

	/** Adds a String parameter to the event */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Prysm")
	static void AddString(UCohtmlJSEvent* JSEvent, const FString& Arg);

	/** Adds a Float parameter to the event */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Prysm")
	static void AddFloat(UCohtmlJSEvent* JSEvent, float Arg);

	/** Adds a Boolean parameter to the event */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Prysm")
	static void AddBool(UCohtmlJSEvent* JSEvent, bool Arg);

	/** Adds an Object parameter to the event */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Prysm")
	static void AddObject(UCohtmlJSEvent* JSEvent, UObject* Arg);

	/** Adds an instance of UStruct to the event */
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (CustomStructureParam = "Arg", BlueprintInternalUseOnly = "true"), Category = "Prysm")
	static void AddStructArg(UCohtmlJSEvent* JSEvent, const UStructProperty* Arg);

	/** Adds an Array of a bindable type to the event */
	UFUNCTION(BlueprintCallable, meta = (ArrayParm = "Arg", BlueprintInternalUseOnly = "true"), Category = "Prysm")
	static void AddArray(UCohtmlJSEvent* JSEvent, const TArray<int32>& Arg, int32 ArrayType);

	/** Adds an Array of UStruct instances to the event */
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (ArrayParm = "Arg", BlueprintInternalUseOnly = "true"), Category = "Prysm")
	static void AddArrayOfStructs(UCohtmlJSEvent* JSEvent, const TArray<int32>& Arg);

	/** Invokes the specified event on the component with arguments coming from JSEvent */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Prysm")
	static void TriggerJSEvent(class UCohtmlBaseComponent* Component, const FString& EventName, UCohtmlJSEvent* JSEvent);

	DECLARE_FUNCTION(execAddStructArg)
	{
		P_GET_OBJECT(UCohtmlJSEvent, JSEvent);
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<UStructProperty>(NULL);
		void* ArgAddress = Stack.MostRecentPropertyAddress;
		UStructProperty* Prop = ExactCast<UStructProperty>(Stack.MostRecentProperty);
		JSEvent->AddStructInternal(Prop, ArgAddress);
		P_FINISH;
	}

	DECLARE_FUNCTION(execAddArrayOfStructs)
	{
		P_GET_OBJECT(UCohtmlJSEvent, JSEvent);
		// Read the array from the stack, pass its address and its type to the JSEvent
		P_GET_TARRAY_REF(int32, Array);
		UArrayProperty* ArrayProperty = Cast<UArrayProperty>(Stack.MostRecentProperty);
		JSEvent->AddArrayOfStructsInternal(&Array, Cast<UStructProperty>(ArrayProperty->Inner)->Struct);
		P_FINISH;
	}
};
