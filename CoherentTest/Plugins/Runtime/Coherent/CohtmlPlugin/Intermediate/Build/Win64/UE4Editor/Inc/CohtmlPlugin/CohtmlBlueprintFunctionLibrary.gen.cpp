// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CohtmlPlugin/Classes/CohtmlBlueprintFunctionLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCohtmlBlueprintFunctionLibrary() {}
// Cross Module References
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary_NoRegister();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlJSEvent_NoRegister();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddBool();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddByte();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddFloat();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddInt32();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddObject();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddString();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddStructArg();
	COREUOBJECT_API UClass* Z_Construct_UClass_UStructProperty();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_CreateJSEvent();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlBaseComponent_NoRegister();
// End Cross Module References
	void UCohtmlBlueprintFunctionLibrary::StaticRegisterNativesUCohtmlBlueprintFunctionLibrary()
	{
		UClass* Class = UCohtmlBlueprintFunctionLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AddArray", &UCohtmlBlueprintFunctionLibrary::execAddArray },
			{ "AddArrayOfStructs", &UCohtmlBlueprintFunctionLibrary::execAddArrayOfStructs },
			{ "AddBool", &UCohtmlBlueprintFunctionLibrary::execAddBool },
			{ "AddByte", &UCohtmlBlueprintFunctionLibrary::execAddByte },
			{ "AddFloat", &UCohtmlBlueprintFunctionLibrary::execAddFloat },
			{ "AddInt32", &UCohtmlBlueprintFunctionLibrary::execAddInt32 },
			{ "AddObject", &UCohtmlBlueprintFunctionLibrary::execAddObject },
			{ "AddString", &UCohtmlBlueprintFunctionLibrary::execAddString },
			{ "AddStructArg", &UCohtmlBlueprintFunctionLibrary::execAddStructArg },
			{ "CreateJSEvent", &UCohtmlBlueprintFunctionLibrary::execCreateJSEvent },
			{ "TriggerJSEvent", &UCohtmlBlueprintFunctionLibrary::execTriggerJSEvent },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray_Statics
	{
		struct CohtmlBlueprintFunctionLibrary_eventAddArray_Parms
		{
			UCohtmlJSEvent* JSEvent;
			TArray<int32> Arg;
			int32 ArrayType;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ArrayType;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Arg_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Arg;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Arg_Inner;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_JSEvent;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray_Statics::NewProp_ArrayType = { "ArrayType", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventAddArray_Parms, ArrayType), METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray_Statics::NewProp_Arg_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray_Statics::NewProp_Arg = { "Arg", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventAddArray_Parms, Arg), METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray_Statics::NewProp_Arg_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray_Statics::NewProp_Arg_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray_Statics::NewProp_Arg_Inner = { "Arg", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray_Statics::NewProp_JSEvent = { "JSEvent", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventAddArray_Parms, JSEvent), Z_Construct_UClass_UCohtmlJSEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray_Statics::NewProp_ArrayType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray_Statics::NewProp_Arg,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray_Statics::NewProp_Arg_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray_Statics::NewProp_JSEvent,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray_Statics::Function_MetaDataParams[] = {
		{ "ArrayParm", "Arg" },
		{ "BlueprintInternalUseOnly", "true" },
		{ "Category", "Prysm" },
		{ "Comment", "/** Adds an Array of a bindable type to the event */" },
		{ "ModuleRelativePath", "Classes/CohtmlBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Adds an Array of a bindable type to the event" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary, nullptr, "AddArray", nullptr, nullptr, sizeof(CohtmlBlueprintFunctionLibrary_eventAddArray_Parms), Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs_Statics
	{
		struct CohtmlBlueprintFunctionLibrary_eventAddArrayOfStructs_Parms
		{
			UCohtmlJSEvent* JSEvent;
			TArray<int32> Arg;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Arg_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Arg;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Arg_Inner;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_JSEvent;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs_Statics::NewProp_Arg_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs_Statics::NewProp_Arg = { "Arg", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventAddArrayOfStructs_Parms, Arg), METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs_Statics::NewProp_Arg_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs_Statics::NewProp_Arg_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs_Statics::NewProp_Arg_Inner = { "Arg", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs_Statics::NewProp_JSEvent = { "JSEvent", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventAddArrayOfStructs_Parms, JSEvent), Z_Construct_UClass_UCohtmlJSEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs_Statics::NewProp_Arg,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs_Statics::NewProp_Arg_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs_Statics::NewProp_JSEvent,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs_Statics::Function_MetaDataParams[] = {
		{ "ArrayParm", "Arg" },
		{ "BlueprintInternalUseOnly", "true" },
		{ "Category", "Prysm" },
		{ "Comment", "/** Adds an Array of UStruct instances to the event */" },
		{ "CustomThunk", "true" },
		{ "ModuleRelativePath", "Classes/CohtmlBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Adds an Array of UStruct instances to the event" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary, nullptr, "AddArrayOfStructs", nullptr, nullptr, sizeof(CohtmlBlueprintFunctionLibrary_eventAddArrayOfStructs_Parms), Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddBool_Statics
	{
		struct CohtmlBlueprintFunctionLibrary_eventAddBool_Parms
		{
			UCohtmlJSEvent* JSEvent;
			bool Arg;
		};
		static void NewProp_Arg_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_Arg;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_JSEvent;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddBool_Statics::NewProp_Arg_SetBit(void* Obj)
	{
		((CohtmlBlueprintFunctionLibrary_eventAddBool_Parms*)Obj)->Arg = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddBool_Statics::NewProp_Arg = { "Arg", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CohtmlBlueprintFunctionLibrary_eventAddBool_Parms), &Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddBool_Statics::NewProp_Arg_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddBool_Statics::NewProp_JSEvent = { "JSEvent", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventAddBool_Parms, JSEvent), Z_Construct_UClass_UCohtmlJSEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddBool_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddBool_Statics::NewProp_Arg,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddBool_Statics::NewProp_JSEvent,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddBool_Statics::Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "Category", "Prysm" },
		{ "Comment", "/** Adds a Boolean parameter to the event */" },
		{ "ModuleRelativePath", "Classes/CohtmlBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Adds a Boolean parameter to the event" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddBool_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary, nullptr, "AddBool", nullptr, nullptr, sizeof(CohtmlBlueprintFunctionLibrary_eventAddBool_Parms), Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddBool_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddBool_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddBool_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddBool_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddBool()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddBool_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddByte_Statics
	{
		struct CohtmlBlueprintFunctionLibrary_eventAddByte_Parms
		{
			UCohtmlJSEvent* JSEvent;
			uint8 Arg;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Arg;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_JSEvent;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddByte_Statics::NewProp_Arg = { "Arg", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventAddByte_Parms, Arg), nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddByte_Statics::NewProp_JSEvent = { "JSEvent", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventAddByte_Parms, JSEvent), Z_Construct_UClass_UCohtmlJSEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddByte_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddByte_Statics::NewProp_Arg,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddByte_Statics::NewProp_JSEvent,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddByte_Statics::Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "Category", "Prysm" },
		{ "Comment", "/** Adds a Byte parameter to the event */" },
		{ "ModuleRelativePath", "Classes/CohtmlBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Adds a Byte parameter to the event" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddByte_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary, nullptr, "AddByte", nullptr, nullptr, sizeof(CohtmlBlueprintFunctionLibrary_eventAddByte_Parms), Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddByte_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddByte_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddByte_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddByte_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddByte()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddByte_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddFloat_Statics
	{
		struct CohtmlBlueprintFunctionLibrary_eventAddFloat_Parms
		{
			UCohtmlJSEvent* JSEvent;
			float Arg;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Arg;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_JSEvent;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddFloat_Statics::NewProp_Arg = { "Arg", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventAddFloat_Parms, Arg), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddFloat_Statics::NewProp_JSEvent = { "JSEvent", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventAddFloat_Parms, JSEvent), Z_Construct_UClass_UCohtmlJSEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddFloat_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddFloat_Statics::NewProp_Arg,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddFloat_Statics::NewProp_JSEvent,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddFloat_Statics::Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "Category", "Prysm" },
		{ "Comment", "/** Adds a Float parameter to the event */" },
		{ "ModuleRelativePath", "Classes/CohtmlBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Adds a Float parameter to the event" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddFloat_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary, nullptr, "AddFloat", nullptr, nullptr, sizeof(CohtmlBlueprintFunctionLibrary_eventAddFloat_Parms), Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddFloat_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddFloat_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddFloat_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddFloat_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddFloat()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddFloat_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddInt32_Statics
	{
		struct CohtmlBlueprintFunctionLibrary_eventAddInt32_Parms
		{
			UCohtmlJSEvent* JSEvent;
			int32 Arg;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Arg;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_JSEvent;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddInt32_Statics::NewProp_Arg = { "Arg", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventAddInt32_Parms, Arg), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddInt32_Statics::NewProp_JSEvent = { "JSEvent", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventAddInt32_Parms, JSEvent), Z_Construct_UClass_UCohtmlJSEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddInt32_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddInt32_Statics::NewProp_Arg,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddInt32_Statics::NewProp_JSEvent,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddInt32_Statics::Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "Category", "Prysm" },
		{ "Comment", "/** Adds an Integer parameter to the event */" },
		{ "ModuleRelativePath", "Classes/CohtmlBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Adds an Integer parameter to the event" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddInt32_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary, nullptr, "AddInt32", nullptr, nullptr, sizeof(CohtmlBlueprintFunctionLibrary_eventAddInt32_Parms), Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddInt32_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddInt32_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddInt32_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddInt32_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddInt32()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddInt32_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddObject_Statics
	{
		struct CohtmlBlueprintFunctionLibrary_eventAddObject_Parms
		{
			UCohtmlJSEvent* JSEvent;
			UObject* Arg;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Arg;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_JSEvent;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddObject_Statics::NewProp_Arg = { "Arg", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventAddObject_Parms, Arg), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddObject_Statics::NewProp_JSEvent = { "JSEvent", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventAddObject_Parms, JSEvent), Z_Construct_UClass_UCohtmlJSEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddObject_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddObject_Statics::NewProp_Arg,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddObject_Statics::NewProp_JSEvent,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddObject_Statics::Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "Category", "Prysm" },
		{ "Comment", "/** Adds an Object parameter to the event */" },
		{ "ModuleRelativePath", "Classes/CohtmlBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Adds an Object parameter to the event" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddObject_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary, nullptr, "AddObject", nullptr, nullptr, sizeof(CohtmlBlueprintFunctionLibrary_eventAddObject_Parms), Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddObject_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddObject_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddObject_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddObject_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddObject()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddObject_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddString_Statics
	{
		struct CohtmlBlueprintFunctionLibrary_eventAddString_Parms
		{
			UCohtmlJSEvent* JSEvent;
			FString Arg;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Arg_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Arg;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_JSEvent;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddString_Statics::NewProp_Arg_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddString_Statics::NewProp_Arg = { "Arg", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventAddString_Parms, Arg), METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddString_Statics::NewProp_Arg_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddString_Statics::NewProp_Arg_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddString_Statics::NewProp_JSEvent = { "JSEvent", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventAddString_Parms, JSEvent), Z_Construct_UClass_UCohtmlJSEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddString_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddString_Statics::NewProp_Arg,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddString_Statics::NewProp_JSEvent,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddString_Statics::Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "Category", "Prysm" },
		{ "Comment", "/** Adds a String parameter to the event */" },
		{ "ModuleRelativePath", "Classes/CohtmlBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Adds a String parameter to the event" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddString_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary, nullptr, "AddString", nullptr, nullptr, sizeof(CohtmlBlueprintFunctionLibrary_eventAddString_Parms), Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddString_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddString_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddString_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddString_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddString()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddString_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddStructArg_Statics
	{
		struct CohtmlBlueprintFunctionLibrary_eventAddStructArg_Parms
		{
			UCohtmlJSEvent* JSEvent;
			const UStructProperty* Arg;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Arg_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Arg;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_JSEvent;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddStructArg_Statics::NewProp_Arg_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddStructArg_Statics::NewProp_Arg = { "Arg", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventAddStructArg_Parms, Arg), Z_Construct_UClass_UStructProperty, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddStructArg_Statics::NewProp_Arg_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddStructArg_Statics::NewProp_Arg_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddStructArg_Statics::NewProp_JSEvent = { "JSEvent", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventAddStructArg_Parms, JSEvent), Z_Construct_UClass_UCohtmlJSEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddStructArg_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddStructArg_Statics::NewProp_Arg,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddStructArg_Statics::NewProp_JSEvent,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddStructArg_Statics::Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "Category", "Prysm" },
		{ "Comment", "/** Adds an instance of UStruct to the event */" },
		{ "CustomStructureParam", "Arg" },
		{ "CustomThunk", "true" },
		{ "ModuleRelativePath", "Classes/CohtmlBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Adds an instance of UStruct to the event" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddStructArg_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary, nullptr, "AddStructArg", nullptr, nullptr, sizeof(CohtmlBlueprintFunctionLibrary_eventAddStructArg_Parms), Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddStructArg_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddStructArg_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddStructArg_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddStructArg_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddStructArg()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddStructArg_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_CreateJSEvent_Statics
	{
		struct CohtmlBlueprintFunctionLibrary_eventCreateJSEvent_Parms
		{
			UObject* WorldContextObject;
			UCohtmlJSEvent* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_CreateJSEvent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventCreateJSEvent_Parms, ReturnValue), Z_Construct_UClass_UCohtmlJSEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_CreateJSEvent_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventCreateJSEvent_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_CreateJSEvent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_CreateJSEvent_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_CreateJSEvent_Statics::NewProp_WorldContextObject,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_CreateJSEvent_Statics::Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "Category", "Prysm" },
		{ "Comment", "/** Creates a UCohtmlJSEvent object */" },
		{ "DisplayName", "Trigger JavaScript Event" },
		{ "ModuleRelativePath", "Classes/CohtmlBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Creates a UCohtmlJSEvent object" },
		{ "WorldContext", "WorldContextObject" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_CreateJSEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary, nullptr, "CreateJSEvent", nullptr, nullptr, sizeof(CohtmlBlueprintFunctionLibrary_eventCreateJSEvent_Parms), Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_CreateJSEvent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_CreateJSEvent_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_CreateJSEvent_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_CreateJSEvent_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_CreateJSEvent()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_CreateJSEvent_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics
	{
		struct CohtmlBlueprintFunctionLibrary_eventTriggerJSEvent_Parms
		{
			UCohtmlBaseComponent* Component;
			FString EventName;
			UCohtmlJSEvent* JSEvent;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_JSEvent;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EventName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_EventName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Component_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Component;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics::NewProp_JSEvent = { "JSEvent", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventTriggerJSEvent_Parms, JSEvent), Z_Construct_UClass_UCohtmlJSEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics::NewProp_EventName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics::NewProp_EventName = { "EventName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventTriggerJSEvent_Parms, EventName), METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics::NewProp_EventName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics::NewProp_EventName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics::NewProp_Component_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics::NewProp_Component = { "Component", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBlueprintFunctionLibrary_eventTriggerJSEvent_Parms, Component), Z_Construct_UClass_UCohtmlBaseComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics::NewProp_Component_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics::NewProp_Component_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics::NewProp_JSEvent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics::NewProp_EventName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics::NewProp_Component,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics::Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "Category", "Prysm" },
		{ "Comment", "/** Invokes the specified event on the component with arguments coming from JSEvent */" },
		{ "ModuleRelativePath", "Classes/CohtmlBlueprintFunctionLibrary.h" },
		{ "ToolTip", "Invokes the specified event on the component with arguments coming from JSEvent" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary, nullptr, "TriggerJSEvent", nullptr, nullptr, sizeof(CohtmlBlueprintFunctionLibrary_eventTriggerJSEvent_Parms), Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary_NoRegister()
	{
		return UCohtmlBlueprintFunctionLibrary::StaticClass();
	}
	struct Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArray, "AddArray" }, // 174244098
		{ &Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddArrayOfStructs, "AddArrayOfStructs" }, // 4193883746
		{ &Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddBool, "AddBool" }, // 387340435
		{ &Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddByte, "AddByte" }, // 3825569202
		{ &Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddFloat, "AddFloat" }, // 171083907
		{ &Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddInt32, "AddInt32" }, // 249248364
		{ &Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddObject, "AddObject" }, // 1322589732
		{ &Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddString, "AddString" }, // 52407143
		{ &Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_AddStructArg, "AddStructArg" }, // 4274551875
		{ &Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_CreateJSEvent, "CreateJSEvent" }, // 2761909447
		{ &Z_Construct_UFunction_UCohtmlBlueprintFunctionLibrary_TriggerJSEvent, "TriggerJSEvent" }, // 1552289946
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary_Statics::Class_MetaDataParams[] = {
		{ "DisplayName", "Prysm Blueprint Function Library" },
		{ "IncludePath", "CohtmlBlueprintFunctionLibrary.h" },
		{ "ModuleRelativePath", "Classes/CohtmlBlueprintFunctionLibrary.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCohtmlBlueprintFunctionLibrary>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary_Statics::ClassParams = {
		&UCohtmlBlueprintFunctionLibrary::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCohtmlBlueprintFunctionLibrary, 3960317697);
	template<> COHTMLPLUGIN_API UClass* StaticClass<UCohtmlBlueprintFunctionLibrary>()
	{
		return UCohtmlBlueprintFunctionLibrary::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCohtmlBlueprintFunctionLibrary(Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary, &UCohtmlBlueprintFunctionLibrary::StaticClass, TEXT("/Script/CohtmlPlugin"), TEXT("UCohtmlBlueprintFunctionLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCohtmlBlueprintFunctionLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
