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

#if !defined(COHTML_UE4_419_SUPPORT)
// Needed because UE 4.20.0 seems to have a missing-include-bug.
// Adding a BlueprintCallable function taking an FText tries to use UTextProperty
// which seems not to be included.
#include <UObject/TextProperty.h>
#endif
#include "CohtmlJSEvent.generated.h"

/**
* The class represents an event triggered by the game that will be processed
* in the JavaScript of the View. Use this class to pass parameters to JavaScript.
*/
UCLASS(BlueprintType, Blueprintable, notplaceable, meta=(DisplayName = "Prysm JS Event"))
class COHTMLPLUGIN_API UCohtmlJSEvent : public UObject
{
	GENERATED_UCLASS_BODY()
public:

	/** Adds a Byte parameter to the event */
	UFUNCTION(BlueprintCallable, Category = "ViewScripting")
	void AddByte(uint8 byte);

	/** Adds an Integer parameter to the event */
	UFUNCTION(BlueprintCallable, Category = "ViewScripting")
	void AddInt32(int32 integer);

	/** Adds a String parameter to the event */
	UFUNCTION(BlueprintCallable, Category = "ViewScripting")
	void AddString(const FString& str);

	/** Adds a Name parameter to the event */
	UFUNCTION(BlueprintCallable, Category = "ViewScripting")
	void AddName(const FName& name);

	/** Adds a Text parameter to the event */
	UFUNCTION(BlueprintCallable, Category = "ViewScripting")
	void AddText(const FText& text);

	/** Adds a Float parameter to the event */
	UFUNCTION(BlueprintCallable, Category = "ViewScripting")
	void AddFloat(float fl);

	/** Adds a Boolean parameter to the event */
	UFUNCTION(BlueprintCallable, Category = "ViewScripting")
	void AddBool(bool b);

	/** Adds an instance of UStruct to the event */
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (CustomStructureParam = "Arg"), Category = "ViewScripting")
	void AddStructArg(const UStructProperty* Arg);

	/** Adds an Object parameter to the event */
	UFUNCTION(BlueprintCallable, Category = "ViewScripting")
	void AddObject(UObject* object);

	/** Adds an Array of a bindable type parameter to the event */
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (ArrayParm = "Array"), Category = "ViewScripting")
	void AddArray(const TArray<int32>& Array);

	enum EVariableType
	{
		VT_Int32,
		VT_Float,
		VT_Bool,
		VT_String,
		VT_Struct,
		VT_Object,
		VT_Array,

		VT_Count
	};

	/** Adds an TArray parameter to the event. Clients should never call directly this. */
	void AddArrayInternal(void* Array, EVariableType ArrayType);
	void AddArrayOfStructsInternal(void* Array, UStruct* StructType);
	void AddStructInternal(const UStructProperty* PropertyType, void* ArgAddress);

	TArray<int32> Ints;
	TArray<FString> Strings;
	TArray<float> Floats;
	TArray<bool> Bools;
	TArray<TWeakObjectPtr<UObject>> Objects;

	struct FBoundStructArg
	{
		const UStruct* StructType;
		TArray<uint8> Data;
	};
	TArray<FBoundStructArg> StructArgs;

	struct FBoundArrayData
	{
		const void* Data;
		EVariableType VariableType;
		// Only used when the array is of type VT_Struct as we need to know the actual element type
		UStruct* StructType;

		FBoundArrayData()
			: Data(nullptr)
			, StructType(nullptr)
		{}
	};
	TArray<FBoundArrayData> Arrays;

	struct FVariablePair
	{
		EVariableType Type;
		int32 Id;
	};
	TArray<FVariablePair> OrderedVariables;

	UPROPERTY(Transient)
	TArray<const UStruct*> StructTypes;

private:
	void AddGenericArray(const UArrayProperty* ArrayProperty, void* ArrayAddress);
	void AddGenericStructArg(const UStructProperty* PropertyType, void* ArgAddress);

public:

#if defined(COHTML_UE4_418_SUPPORT)
	DECLARE_FUNCTION(execAddArray)
	{
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<UArrayProperty>(NULL);
		void* ArrayAddress = Stack.MostRecentPropertyAddress;
		UArrayProperty* ArrayProperty = Cast<UArrayProperty>(Stack.MostRecentProperty);
		if (!ArrayProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}
		AddGenericArray(ArrayProperty, ArrayAddress);
		P_FINISH;
	}

	DECLARE_FUNCTION(execAddStructArg)
	{
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<UStructProperty>(NULL);
		void* ArgAddress = Stack.MostRecentPropertyAddress;
		UStructProperty* Prop = ExactCast<UStructProperty>(Stack.MostRecentProperty);
		AddGenericStructArg(Prop, ArgAddress);
		P_FINISH;
	}
#else
	//declared here and defined in the cpp file
	DECLARE_FUNCTION(execAddArray);
	DECLARE_FUNCTION(execAddStructArg);
#endif

	virtual void BeginDestroy();

	~UCohtmlJSEvent();
};
