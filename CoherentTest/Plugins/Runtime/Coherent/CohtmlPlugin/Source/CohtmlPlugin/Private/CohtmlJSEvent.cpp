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
#include "CohtmlJSEvent.h"

UCohtmlJSEvent::UCohtmlJSEvent(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

void UCohtmlJSEvent::AddByte(uint8 byte)
{
	// Put bytes into ints
	AddInt32(byte);
}

void UCohtmlJSEvent::AddInt32(int32 integer)
{
	Ints.Add(integer);
	FVariablePair pair;
	pair.Type = VT_Int32;
	pair.Id = Ints.Num() - 1;
	OrderedVariables.Add(pair);
}

void UCohtmlJSEvent::AddFloat(float fl)
{
	Floats.Add(fl);
	FVariablePair pair;
	pair.Type = VT_Float;
	pair.Id = Floats.Num() - 1;
	OrderedVariables.Add(pair);
}

void UCohtmlJSEvent::AddBool(bool b)
{
	Bools.Add(b);
	FVariablePair pair;
	pair.Type = VT_Bool;
	pair.Id = Bools.Num() - 1;
	OrderedVariables.Add(pair);
}

void UCohtmlJSEvent::AddString(const FString& str)
{
	Strings.Add(str);
	FVariablePair pair;
	pair.Type = VT_String;
	pair.Id = Strings.Num() - 1;
	OrderedVariables.Add(pair);
}

void UCohtmlJSEvent::AddName(const FName& name)
{
	Strings.Add(name.ToString());
	FVariablePair pair;
	pair.Type = VT_String;
	pair.Id = Strings.Num() - 1;
	OrderedVariables.Add(pair);
}

void UCohtmlJSEvent::AddText(const FText& text)
{
	Strings.Add(text.ToString());
	FVariablePair pair;
	pair.Type = VT_String;
	pair.Id = Strings.Num() - 1;
	OrderedVariables.Add(pair);
}

void UCohtmlJSEvent::AddObject(UObject* object)
{
	Objects.Add(object);
	FVariablePair pair;
	pair.Type = VT_Object;
	pair.Id = Objects.Num() - 1;
	OrderedVariables.Add(pair);
}

void UCohtmlJSEvent::AddArray(const TArray<int32>& Array)
{
	// This is only a stub.
	// It should never be called, there's a custom thunk implementation in the header
	check(0);
}

void UCohtmlJSEvent::AddStructArg(const UStructProperty* Arg)
{
	// This is only a stub.
	// It should never be called, there's a custom thunk implementation in the header
	check(0);
}


namespace
{
UCohtmlJSEvent::EVariableType GetPropertyType(const UProperty* Property)
{
	if (Property->IsA(UIntProperty::StaticClass()))
		return UCohtmlJSEvent::VT_Int32;
	if (Property->IsA(UBoolProperty::StaticClass()))
		return UCohtmlJSEvent::VT_Bool;
	if (Property->IsA(UFloatProperty::StaticClass()))
		return UCohtmlJSEvent::VT_Float;
	if (Property->IsA(UStrProperty::StaticClass()))
		return UCohtmlJSEvent::VT_String;
	if (Property->IsA(UStructProperty::StaticClass()))
		return UCohtmlJSEvent::VT_Struct;
	if (Property->IsA(UObjectProperty::StaticClass()))
		return UCohtmlJSEvent::VT_Object;

	return UCohtmlJSEvent::VT_Count;
}
}

void UCohtmlJSEvent::AddGenericArray(const UArrayProperty* ArrayProperty, void* ArrayAddress)
{
	const UProperty* InnerProp = ArrayProperty->Inner;

	EVariableType Type = GetPropertyType(InnerProp);
	if (Type == VT_Count)
	{
		COHTML_UE_LOG(Error, TEXT("Tried to bind an array of unsupported type: %s"), *InnerProp->GetCPPType());
		return;
	}
	FBoundArrayData ArrayData;
	ArrayData.Data = ArrayAddress;
	ArrayData.VariableType = Type;
	if (Type == VT_Struct)
	{
		ArrayData.StructType = Cast<UStructProperty>(InnerProp)->Struct;
	}
	Arrays.Add(ArrayData);

	FVariablePair Pair;
	Pair.Type = VT_Array;
	Pair.Id = Arrays.Num() - 1;
	OrderedVariables.Add(Pair);
}

void UCohtmlJSEvent::AddArrayInternal(void* Array, EVariableType ArrayType)
{
	verify(ArrayType != VT_Struct);

	FBoundArrayData ArrayData;
	ArrayData.Data = Array;
	ArrayData.VariableType = ArrayType;
	Arrays.Add(ArrayData);

	FVariablePair Pair;
	Pair.Type = VT_Array;
	Pair.Id = Arrays.Num() - 1;
	OrderedVariables.Add(Pair);
}

void UCohtmlJSEvent::AddArrayOfStructsInternal(void* Array, UStruct* StructType)
{
	FBoundArrayData ArrayData;
	ArrayData.Data = Array;
	ArrayData.VariableType = VT_Struct;
	ArrayData.StructType = StructType;
	Arrays.Add(ArrayData);

	FVariablePair Pair;
	Pair.Type = VT_Array;
	Pair.Id = Arrays.Num() - 1;
	OrderedVariables.Add(Pair);

	// Added to keep the UObject alive
	StructTypes.Add(StructType);
}

void UCohtmlJSEvent::AddGenericStructArg(const UStructProperty* PropertyType, void* ArgAddress)
{
	FBoundStructArg ArgData;
	ArgData.StructType = PropertyType->Struct;
	ArgData.Data.SetNumUninitialized(PropertyType->GetSize());
	PropertyType->InitializeValue(ArgData.Data.GetData());
	PropertyType->CopyCompleteValue(ArgData.Data.GetData(), ArgAddress);
	StructArgs.Add(MoveTemp(ArgData));

	FVariablePair Pair;
	Pair.Type = VT_Struct;
	Pair.Id = StructArgs.Num() - 1;
	OrderedVariables.Add(Pair);

	// Added to keep the UObject alive
	StructTypes.Add(PropertyType->Struct);
}

void UCohtmlJSEvent::AddStructInternal(const UStructProperty* PropertyType, void* ArgAddress)
{
	AddGenericStructArg(PropertyType, ArgAddress);
}

void UCohtmlJSEvent::BeginDestroy()
{
	for (auto& arg : StructArgs)
	{
		arg.StructType->DestroyStruct(arg.Data.GetData());
	}
	StructArgs.Empty();
	Arrays.Empty();
	StructTypes.Empty();

	Super::BeginDestroy();
}

UCohtmlJSEvent::~UCohtmlJSEvent()
{
	check(StructArgs.Num() == 0);
}

#if !defined(COHTML_UE4_418_SUPPORT)
DEFINE_FUNCTION(UCohtmlJSEvent::execAddArray)
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
	P_THIS->AddGenericArray(ArrayProperty, ArrayAddress);
	P_FINISH;
};

DEFINE_FUNCTION(UCohtmlJSEvent::execAddStructArg)
{
	Stack.MostRecentProperty = nullptr;
	Stack.StepCompiledIn<UStructProperty>(NULL);
	void* ArgAddress = Stack.MostRecentPropertyAddress;
	UStructProperty* Prop = ExactCast<UStructProperty>(Stack.MostRecentProperty);
	P_THIS->AddGenericStructArg(Prop, ArgAddress);
	P_FINISH;
};
#endif
