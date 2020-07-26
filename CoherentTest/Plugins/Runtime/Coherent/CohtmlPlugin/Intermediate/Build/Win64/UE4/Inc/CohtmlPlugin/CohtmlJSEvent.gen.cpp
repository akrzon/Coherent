// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CohtmlPlugin/Classes/CohtmlJSEvent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCohtmlJSEvent() {}
// Cross Module References
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlJSEvent_NoRegister();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlJSEvent();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlJSEvent_AddArray();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlJSEvent_AddBool();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlJSEvent_AddByte();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlJSEvent_AddFloat();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlJSEvent_AddInt32();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlJSEvent_AddName();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlJSEvent_AddObject();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlJSEvent_AddString();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlJSEvent_AddStructArg();
	COREUOBJECT_API UClass* Z_Construct_UClass_UStructProperty();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlJSEvent_AddText();
	COREUOBJECT_API UClass* Z_Construct_UClass_UStruct();
// End Cross Module References
	void UCohtmlJSEvent::StaticRegisterNativesUCohtmlJSEvent()
	{
		UClass* Class = UCohtmlJSEvent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AddArray", &UCohtmlJSEvent::execAddArray },
			{ "AddBool", &UCohtmlJSEvent::execAddBool },
			{ "AddByte", &UCohtmlJSEvent::execAddByte },
			{ "AddFloat", &UCohtmlJSEvent::execAddFloat },
			{ "AddInt32", &UCohtmlJSEvent::execAddInt32 },
			{ "AddName", &UCohtmlJSEvent::execAddName },
			{ "AddObject", &UCohtmlJSEvent::execAddObject },
			{ "AddString", &UCohtmlJSEvent::execAddString },
			{ "AddStructArg", &UCohtmlJSEvent::execAddStructArg },
			{ "AddText", &UCohtmlJSEvent::execAddText },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UCohtmlJSEvent_AddArray_Statics
	{
		struct CohtmlJSEvent_eventAddArray_Parms
		{
			TArray<int32> Array;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Array_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Array;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Array_Inner;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlJSEvent_AddArray_Statics::NewProp_Array_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UCohtmlJSEvent_AddArray_Statics::NewProp_Array = { "Array", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlJSEvent_eventAddArray_Parms, Array), METADATA_PARAMS(Z_Construct_UFunction_UCohtmlJSEvent_AddArray_Statics::NewProp_Array_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddArray_Statics::NewProp_Array_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UCohtmlJSEvent_AddArray_Statics::NewProp_Array_Inner = { "Array", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlJSEvent_AddArray_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlJSEvent_AddArray_Statics::NewProp_Array,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlJSEvent_AddArray_Statics::NewProp_Array_Inner,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlJSEvent_AddArray_Statics::Function_MetaDataParams[] = {
		{ "ArrayParm", "Array" },
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Adds an Array of a bindable type parameter to the event */" },
		{ "CustomThunk", "true" },
		{ "ModuleRelativePath", "Classes/CohtmlJSEvent.h" },
		{ "ToolTip", "Adds an Array of a bindable type parameter to the event" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlJSEvent_AddArray_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlJSEvent, nullptr, "AddArray", nullptr, nullptr, sizeof(CohtmlJSEvent_eventAddArray_Parms), Z_Construct_UFunction_UCohtmlJSEvent_AddArray_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddArray_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlJSEvent_AddArray_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddArray_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlJSEvent_AddArray()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlJSEvent_AddArray_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlJSEvent_AddBool_Statics
	{
		struct CohtmlJSEvent_eventAddBool_Parms
		{
			bool b;
		};
		static void NewProp_b_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_b;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UCohtmlJSEvent_AddBool_Statics::NewProp_b_SetBit(void* Obj)
	{
		((CohtmlJSEvent_eventAddBool_Parms*)Obj)->b = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCohtmlJSEvent_AddBool_Statics::NewProp_b = { "b", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CohtmlJSEvent_eventAddBool_Parms), &Z_Construct_UFunction_UCohtmlJSEvent_AddBool_Statics::NewProp_b_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlJSEvent_AddBool_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlJSEvent_AddBool_Statics::NewProp_b,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlJSEvent_AddBool_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Adds a Boolean parameter to the event */" },
		{ "ModuleRelativePath", "Classes/CohtmlJSEvent.h" },
		{ "ToolTip", "Adds a Boolean parameter to the event" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlJSEvent_AddBool_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlJSEvent, nullptr, "AddBool", nullptr, nullptr, sizeof(CohtmlJSEvent_eventAddBool_Parms), Z_Construct_UFunction_UCohtmlJSEvent_AddBool_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddBool_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlJSEvent_AddBool_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddBool_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlJSEvent_AddBool()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlJSEvent_AddBool_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlJSEvent_AddByte_Statics
	{
		struct CohtmlJSEvent_eventAddByte_Parms
		{
			uint8 byte;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_byte;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UCohtmlJSEvent_AddByte_Statics::NewProp_byte = { "byte", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlJSEvent_eventAddByte_Parms, byte), nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlJSEvent_AddByte_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlJSEvent_AddByte_Statics::NewProp_byte,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlJSEvent_AddByte_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Adds a Byte parameter to the event */" },
		{ "ModuleRelativePath", "Classes/CohtmlJSEvent.h" },
		{ "ToolTip", "Adds a Byte parameter to the event" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlJSEvent_AddByte_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlJSEvent, nullptr, "AddByte", nullptr, nullptr, sizeof(CohtmlJSEvent_eventAddByte_Parms), Z_Construct_UFunction_UCohtmlJSEvent_AddByte_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddByte_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlJSEvent_AddByte_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddByte_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlJSEvent_AddByte()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlJSEvent_AddByte_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlJSEvent_AddFloat_Statics
	{
		struct CohtmlJSEvent_eventAddFloat_Parms
		{
			float fl;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_fl;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UCohtmlJSEvent_AddFloat_Statics::NewProp_fl = { "fl", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlJSEvent_eventAddFloat_Parms, fl), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlJSEvent_AddFloat_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlJSEvent_AddFloat_Statics::NewProp_fl,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlJSEvent_AddFloat_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Adds a Float parameter to the event */" },
		{ "ModuleRelativePath", "Classes/CohtmlJSEvent.h" },
		{ "ToolTip", "Adds a Float parameter to the event" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlJSEvent_AddFloat_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlJSEvent, nullptr, "AddFloat", nullptr, nullptr, sizeof(CohtmlJSEvent_eventAddFloat_Parms), Z_Construct_UFunction_UCohtmlJSEvent_AddFloat_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddFloat_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlJSEvent_AddFloat_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddFloat_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlJSEvent_AddFloat()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlJSEvent_AddFloat_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlJSEvent_AddInt32_Statics
	{
		struct CohtmlJSEvent_eventAddInt32_Parms
		{
			int32 integer;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_integer;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UCohtmlJSEvent_AddInt32_Statics::NewProp_integer = { "integer", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlJSEvent_eventAddInt32_Parms, integer), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlJSEvent_AddInt32_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlJSEvent_AddInt32_Statics::NewProp_integer,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlJSEvent_AddInt32_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Adds an Integer parameter to the event */" },
		{ "ModuleRelativePath", "Classes/CohtmlJSEvent.h" },
		{ "ToolTip", "Adds an Integer parameter to the event" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlJSEvent_AddInt32_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlJSEvent, nullptr, "AddInt32", nullptr, nullptr, sizeof(CohtmlJSEvent_eventAddInt32_Parms), Z_Construct_UFunction_UCohtmlJSEvent_AddInt32_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddInt32_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlJSEvent_AddInt32_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddInt32_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlJSEvent_AddInt32()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlJSEvent_AddInt32_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlJSEvent_AddName_Statics
	{
		struct CohtmlJSEvent_eventAddName_Parms
		{
			FName name;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_name_MetaData[];
#endif
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_name;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlJSEvent_AddName_Statics::NewProp_name_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UCohtmlJSEvent_AddName_Statics::NewProp_name = { "name", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlJSEvent_eventAddName_Parms, name), METADATA_PARAMS(Z_Construct_UFunction_UCohtmlJSEvent_AddName_Statics::NewProp_name_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddName_Statics::NewProp_name_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlJSEvent_AddName_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlJSEvent_AddName_Statics::NewProp_name,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlJSEvent_AddName_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Adds a Name parameter to the event */" },
		{ "ModuleRelativePath", "Classes/CohtmlJSEvent.h" },
		{ "ToolTip", "Adds a Name parameter to the event" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlJSEvent_AddName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlJSEvent, nullptr, "AddName", nullptr, nullptr, sizeof(CohtmlJSEvent_eventAddName_Parms), Z_Construct_UFunction_UCohtmlJSEvent_AddName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddName_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlJSEvent_AddName_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddName_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlJSEvent_AddName()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlJSEvent_AddName_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlJSEvent_AddObject_Statics
	{
		struct CohtmlJSEvent_eventAddObject_Parms
		{
			UObject* object;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_object;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlJSEvent_AddObject_Statics::NewProp_object = { "object", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlJSEvent_eventAddObject_Parms, object), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlJSEvent_AddObject_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlJSEvent_AddObject_Statics::NewProp_object,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlJSEvent_AddObject_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Adds an Object parameter to the event */" },
		{ "ModuleRelativePath", "Classes/CohtmlJSEvent.h" },
		{ "ToolTip", "Adds an Object parameter to the event" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlJSEvent_AddObject_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlJSEvent, nullptr, "AddObject", nullptr, nullptr, sizeof(CohtmlJSEvent_eventAddObject_Parms), Z_Construct_UFunction_UCohtmlJSEvent_AddObject_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddObject_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlJSEvent_AddObject_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddObject_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlJSEvent_AddObject()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlJSEvent_AddObject_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlJSEvent_AddString_Statics
	{
		struct CohtmlJSEvent_eventAddString_Parms
		{
			FString str;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_str_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_str;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlJSEvent_AddString_Statics::NewProp_str_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCohtmlJSEvent_AddString_Statics::NewProp_str = { "str", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlJSEvent_eventAddString_Parms, str), METADATA_PARAMS(Z_Construct_UFunction_UCohtmlJSEvent_AddString_Statics::NewProp_str_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddString_Statics::NewProp_str_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlJSEvent_AddString_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlJSEvent_AddString_Statics::NewProp_str,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlJSEvent_AddString_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Adds a String parameter to the event */" },
		{ "ModuleRelativePath", "Classes/CohtmlJSEvent.h" },
		{ "ToolTip", "Adds a String parameter to the event" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlJSEvent_AddString_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlJSEvent, nullptr, "AddString", nullptr, nullptr, sizeof(CohtmlJSEvent_eventAddString_Parms), Z_Construct_UFunction_UCohtmlJSEvent_AddString_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddString_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlJSEvent_AddString_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddString_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlJSEvent_AddString()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlJSEvent_AddString_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlJSEvent_AddStructArg_Statics
	{
		struct CohtmlJSEvent_eventAddStructArg_Parms
		{
			const UStructProperty* Arg;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Arg_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Arg;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlJSEvent_AddStructArg_Statics::NewProp_Arg_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlJSEvent_AddStructArg_Statics::NewProp_Arg = { "Arg", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlJSEvent_eventAddStructArg_Parms, Arg), Z_Construct_UClass_UStructProperty, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlJSEvent_AddStructArg_Statics::NewProp_Arg_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddStructArg_Statics::NewProp_Arg_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlJSEvent_AddStructArg_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlJSEvent_AddStructArg_Statics::NewProp_Arg,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlJSEvent_AddStructArg_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Adds an instance of UStruct to the event */" },
		{ "CustomStructureParam", "Arg" },
		{ "CustomThunk", "true" },
		{ "ModuleRelativePath", "Classes/CohtmlJSEvent.h" },
		{ "ToolTip", "Adds an instance of UStruct to the event" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlJSEvent_AddStructArg_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlJSEvent, nullptr, "AddStructArg", nullptr, nullptr, sizeof(CohtmlJSEvent_eventAddStructArg_Parms), Z_Construct_UFunction_UCohtmlJSEvent_AddStructArg_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddStructArg_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlJSEvent_AddStructArg_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddStructArg_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlJSEvent_AddStructArg()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlJSEvent_AddStructArg_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlJSEvent_AddText_Statics
	{
		struct CohtmlJSEvent_eventAddText_Parms
		{
			FText text;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_text_MetaData[];
#endif
		static const UE4CodeGen_Private::FTextPropertyParams NewProp_text;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlJSEvent_AddText_Statics::NewProp_text_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FTextPropertyParams Z_Construct_UFunction_UCohtmlJSEvent_AddText_Statics::NewProp_text = { "text", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlJSEvent_eventAddText_Parms, text), METADATA_PARAMS(Z_Construct_UFunction_UCohtmlJSEvent_AddText_Statics::NewProp_text_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddText_Statics::NewProp_text_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlJSEvent_AddText_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlJSEvent_AddText_Statics::NewProp_text,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlJSEvent_AddText_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Adds a Text parameter to the event */" },
		{ "ModuleRelativePath", "Classes/CohtmlJSEvent.h" },
		{ "ToolTip", "Adds a Text parameter to the event" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlJSEvent_AddText_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlJSEvent, nullptr, "AddText", nullptr, nullptr, sizeof(CohtmlJSEvent_eventAddText_Parms), Z_Construct_UFunction_UCohtmlJSEvent_AddText_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddText_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlJSEvent_AddText_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlJSEvent_AddText_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlJSEvent_AddText()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlJSEvent_AddText_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UCohtmlJSEvent_NoRegister()
	{
		return UCohtmlJSEvent::StaticClass();
	}
	struct Z_Construct_UClass_UCohtmlJSEvent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StructTypes_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_StructTypes;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_StructTypes_Inner;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCohtmlJSEvent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UCohtmlJSEvent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UCohtmlJSEvent_AddArray, "AddArray" }, // 3121701567
		{ &Z_Construct_UFunction_UCohtmlJSEvent_AddBool, "AddBool" }, // 2376721477
		{ &Z_Construct_UFunction_UCohtmlJSEvent_AddByte, "AddByte" }, // 2074077042
		{ &Z_Construct_UFunction_UCohtmlJSEvent_AddFloat, "AddFloat" }, // 2072767830
		{ &Z_Construct_UFunction_UCohtmlJSEvent_AddInt32, "AddInt32" }, // 2150838610
		{ &Z_Construct_UFunction_UCohtmlJSEvent_AddName, "AddName" }, // 2153017958
		{ &Z_Construct_UFunction_UCohtmlJSEvent_AddObject, "AddObject" }, // 1784411236
		{ &Z_Construct_UFunction_UCohtmlJSEvent_AddString, "AddString" }, // 231670192
		{ &Z_Construct_UFunction_UCohtmlJSEvent_AddStructArg, "AddStructArg" }, // 330750604
		{ &Z_Construct_UFunction_UCohtmlJSEvent_AddText, "AddText" }, // 2654633438
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlJSEvent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n* The class represents an event triggered by the game that will be processed\n* in the JavaScript of the View. Use this class to pass parameters to JavaScript.\n*/" },
		{ "DisplayName", "Prysm JS Event" },
		{ "IncludePath", "CohtmlJSEvent.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Classes/CohtmlJSEvent.h" },
		{ "ToolTip", "The class represents an event triggered by the game that will be processed\nin the JavaScript of the View. Use this class to pass parameters to JavaScript." },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlJSEvent_Statics::NewProp_StructTypes_MetaData[] = {
		{ "ModuleRelativePath", "Classes/CohtmlJSEvent.h" },
		{ "NativeConstTemplateArg", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UCohtmlJSEvent_Statics::NewProp_StructTypes = { "StructTypes", nullptr, (EPropertyFlags)0x0010000000002000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlJSEvent, StructTypes), METADATA_PARAMS(Z_Construct_UClass_UCohtmlJSEvent_Statics::NewProp_StructTypes_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlJSEvent_Statics::NewProp_StructTypes_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCohtmlJSEvent_Statics::NewProp_StructTypes_Inner = { "StructTypes", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UStruct, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCohtmlJSEvent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlJSEvent_Statics::NewProp_StructTypes,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlJSEvent_Statics::NewProp_StructTypes_Inner,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCohtmlJSEvent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCohtmlJSEvent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCohtmlJSEvent_Statics::ClassParams = {
		&UCohtmlJSEvent::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UCohtmlJSEvent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlJSEvent_Statics::PropPointers),
		0,
		0x001002A0u,
		METADATA_PARAMS(Z_Construct_UClass_UCohtmlJSEvent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlJSEvent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCohtmlJSEvent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCohtmlJSEvent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCohtmlJSEvent, 1376074332);
	template<> COHTMLPLUGIN_API UClass* StaticClass<UCohtmlJSEvent>()
	{
		return UCohtmlJSEvent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCohtmlJSEvent(Z_Construct_UClass_UCohtmlJSEvent, &UCohtmlJSEvent::StaticClass, TEXT("/Script/CohtmlPlugin"), TEXT("UCohtmlJSEvent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCohtmlJSEvent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
