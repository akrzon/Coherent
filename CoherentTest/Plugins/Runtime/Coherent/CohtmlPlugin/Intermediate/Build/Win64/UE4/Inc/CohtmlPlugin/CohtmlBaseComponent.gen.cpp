// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CohtmlPlugin/Classes/CohtmlBaseComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCohtmlBaseComponent() {}
// Cross Module References
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlBaseComponent_NoRegister();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlBaseComponent();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_BeginDebugFrameSave();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromObject();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct();
	COREUOBJECT_API UClass* Z_Construct_UClass_UStructProperty();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_CreateJSEvent();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlJSEvent_NoRegister();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_DebugSaveNextFrame();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_EnableDelayedUpdate();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_EndDebugFrameSave();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_HasRequestedView();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyForBindings();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyToCreateView();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_Load();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_Reload();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_Resize();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_SetSoundAttenuation();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FSoundAttenuationSettings();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_ShowPaintRects();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_SynchronizeModels();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_TriggerJSEvent();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromObject();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromStruct();
	ENGINE_API UEnum* Z_Construct_UEnum_Engine_TextureFilter();
	ENGINE_API UClass* Z_Construct_UClass_UTextureRenderTarget2D_NoRegister();
	COHTMLPLUGIN_API UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlScriptingReady__DelegateSignature();
	COHTMLPLUGIN_API UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlBindingsReleasedSignature__DelegateSignature();
	COHTMLPLUGIN_API UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlReadyForBindingsSignature__DelegateSignature();
// End Cross Module References
	void UCohtmlBaseComponent::StaticRegisterNativesUCohtmlBaseComponent()
	{
		UClass* Class = UCohtmlBaseComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "BeginDebugFrameSave", &UCohtmlBaseComponent::execBeginDebugFrameSave },
			{ "CreateDataModelFromObject", &UCohtmlBaseComponent::execCreateDataModelFromObject },
			{ "CreateDataModelFromStruct", &UCohtmlBaseComponent::execCreateDataModelFromStruct },
			{ "CreateJSEvent", &UCohtmlBaseComponent::execCreateJSEvent },
			{ "DebugSaveNextFrame", &UCohtmlBaseComponent::execDebugSaveNextFrame },
			{ "EnableDelayedUpdate", &UCohtmlBaseComponent::execEnableDelayedUpdate },
			{ "EndDebugFrameSave", &UCohtmlBaseComponent::execEndDebugFrameSave },
			{ "HasRequestedView", &UCohtmlBaseComponent::execHasRequestedView },
			{ "IsReadyForBindings", &UCohtmlBaseComponent::execIsReadyForBindings },
			{ "IsReadyToCreateView", &UCohtmlBaseComponent::execIsReadyToCreateView },
			{ "Load", &UCohtmlBaseComponent::execLoad },
			{ "Reload", &UCohtmlBaseComponent::execReload },
			{ "Resize", &UCohtmlBaseComponent::execResize },
			{ "SetSoundAttenuation", &UCohtmlBaseComponent::execSetSoundAttenuation },
			{ "ShowPaintRects", &UCohtmlBaseComponent::execShowPaintRects },
			{ "SynchronizeModels", &UCohtmlBaseComponent::execSynchronizeModels },
			{ "TriggerJSEvent", &UCohtmlBaseComponent::execTriggerJSEvent },
			{ "UpdateWholeDataModelFromObject", &UCohtmlBaseComponent::execUpdateWholeDataModelFromObject },
			{ "UpdateWholeDataModelFromStruct", &UCohtmlBaseComponent::execUpdateWholeDataModelFromStruct },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UCohtmlBaseComponent_BeginDebugFrameSave_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_BeginDebugFrameSave_Statics::Function_MetaDataParams[] = {
		{ "Category", "View" },
		{ "Comment", "/** Starts saving render frames to disk */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Starts saving render frames to disk" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBaseComponent_BeginDebugFrameSave_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBaseComponent, nullptr, "BeginDebugFrameSave", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_BeginDebugFrameSave_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_BeginDebugFrameSave_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_BeginDebugFrameSave()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBaseComponent_BeginDebugFrameSave_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromObject_Statics
	{
		struct CohtmlBaseComponent_eventCreateDataModelFromObject_Parms
		{
			FString Name;
			UObject* Model;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Model;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Name;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromObject_Statics::NewProp_Model = { "Model", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBaseComponent_eventCreateDataModelFromObject_Parms, Model), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromObject_Statics::NewProp_Name_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromObject_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBaseComponent_eventCreateDataModelFromObject_Parms, Name), METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromObject_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromObject_Statics::NewProp_Name_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromObject_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromObject_Statics::NewProp_Model,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromObject_Statics::NewProp_Name,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromObject_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Creates a global variable (data model) in JavaScript from an UObject */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Creates a global variable (data model) in JavaScript from an UObject" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromObject_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBaseComponent, nullptr, "CreateDataModelFromObject", nullptr, nullptr, sizeof(CohtmlBaseComponent_eventCreateDataModelFromObject_Parms), Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromObject_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromObject_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromObject_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromObject_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromObject()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromObject_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct_Statics
	{
		struct CohtmlBaseComponent_eventCreateDataModelFromStruct_Parms
		{
			FString Name;
			const UStructProperty* Arg;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Arg_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Arg;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Name;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct_Statics::NewProp_Arg_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct_Statics::NewProp_Arg = { "Arg", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBaseComponent_eventCreateDataModelFromStruct_Parms, Arg), Z_Construct_UClass_UStructProperty, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct_Statics::NewProp_Arg_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct_Statics::NewProp_Arg_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct_Statics::NewProp_Name_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBaseComponent_eventCreateDataModelFromStruct_Parms, Name), METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct_Statics::NewProp_Name_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct_Statics::NewProp_Arg,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct_Statics::NewProp_Name,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Creates a global variable (data model) in JavaScript from a UStruct */" },
		{ "CustomStructureParam", "Arg" },
		{ "CustomThunk", "true" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Creates a global variable (data model) in JavaScript from a UStruct" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBaseComponent, nullptr, "CreateDataModelFromStruct", nullptr, nullptr, sizeof(CohtmlBaseComponent_eventCreateDataModelFromStruct_Parms), Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBaseComponent_CreateJSEvent_Statics
	{
		struct CohtmlBaseComponent_eventCreateJSEvent_Parms
		{
			UCohtmlJSEvent* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBaseComponent_CreateJSEvent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBaseComponent_eventCreateJSEvent_Parms, ReturnValue), Z_Construct_UClass_UCohtmlJSEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBaseComponent_CreateJSEvent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBaseComponent_CreateJSEvent_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_CreateJSEvent_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Creates an event that will be executed in JavaScript */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Creates an event that will be executed in JavaScript" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBaseComponent_CreateJSEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBaseComponent, nullptr, "CreateJSEvent", nullptr, nullptr, sizeof(CohtmlBaseComponent_eventCreateJSEvent_Parms), Z_Construct_UFunction_UCohtmlBaseComponent_CreateJSEvent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_CreateJSEvent_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_CreateJSEvent_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_CreateJSEvent_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_CreateJSEvent()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBaseComponent_CreateJSEvent_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBaseComponent_DebugSaveNextFrame_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_DebugSaveNextFrame_Statics::Function_MetaDataParams[] = {
		{ "Category", "View" },
		{ "Comment", "/** Saves next render frame to disk */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Saves next render frame to disk" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBaseComponent_DebugSaveNextFrame_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBaseComponent, nullptr, "DebugSaveNextFrame", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_DebugSaveNextFrame_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_DebugSaveNextFrame_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_DebugSaveNextFrame()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBaseComponent_DebugSaveNextFrame_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBaseComponent_EnableDelayedUpdate_Statics
	{
		struct CohtmlBaseComponent_eventEnableDelayedUpdate_Parms
		{
			bool bEnabled;
		};
		static void NewProp_bEnabled_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bEnabled;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UCohtmlBaseComponent_EnableDelayedUpdate_Statics::NewProp_bEnabled_SetBit(void* Obj)
	{
		((CohtmlBaseComponent_eventEnableDelayedUpdate_Parms*)Obj)->bEnabled = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCohtmlBaseComponent_EnableDelayedUpdate_Statics::NewProp_bEnabled = { "bEnabled", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CohtmlBaseComponent_eventEnableDelayedUpdate_Parms), &Z_Construct_UFunction_UCohtmlBaseComponent_EnableDelayedUpdate_Statics::NewProp_bEnabled_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBaseComponent_EnableDelayedUpdate_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBaseComponent_EnableDelayedUpdate_Statics::NewProp_bEnabled,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_EnableDelayedUpdate_Statics::Function_MetaDataParams[] = {
		{ "Category", "View" },
		{ "Comment", "/** Delays UI updates until after cameras are updated. Read the section in the FAQ page of the documentation before using */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Delays UI updates until after cameras are updated. Read the section in the FAQ page of the documentation before using" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBaseComponent_EnableDelayedUpdate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBaseComponent, nullptr, "EnableDelayedUpdate", nullptr, nullptr, sizeof(CohtmlBaseComponent_eventEnableDelayedUpdate_Parms), Z_Construct_UFunction_UCohtmlBaseComponent_EnableDelayedUpdate_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_EnableDelayedUpdate_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_EnableDelayedUpdate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_EnableDelayedUpdate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_EnableDelayedUpdate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBaseComponent_EnableDelayedUpdate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBaseComponent_EndDebugFrameSave_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_EndDebugFrameSave_Statics::Function_MetaDataParams[] = {
		{ "Category", "View" },
		{ "Comment", "/** Stops saving render frames to disk */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Stops saving render frames to disk" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBaseComponent_EndDebugFrameSave_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBaseComponent, nullptr, "EndDebugFrameSave", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_EndDebugFrameSave_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_EndDebugFrameSave_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_EndDebugFrameSave()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBaseComponent_EndDebugFrameSave_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBaseComponent_HasRequestedView_Statics
	{
		struct CohtmlBaseComponent_eventHasRequestedView_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UCohtmlBaseComponent_HasRequestedView_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((CohtmlBaseComponent_eventHasRequestedView_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCohtmlBaseComponent_HasRequestedView_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CohtmlBaseComponent_eventHasRequestedView_Parms), &Z_Construct_UFunction_UCohtmlBaseComponent_HasRequestedView_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBaseComponent_HasRequestedView_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBaseComponent_HasRequestedView_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_HasRequestedView_Statics::Function_MetaDataParams[] = {
		{ "Category", "View" },
		{ "Comment", "/** Tells if a View has been scheduled for creation */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Tells if a View has been scheduled for creation" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBaseComponent_HasRequestedView_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBaseComponent, nullptr, "HasRequestedView", nullptr, nullptr, sizeof(CohtmlBaseComponent_eventHasRequestedView_Parms), Z_Construct_UFunction_UCohtmlBaseComponent_HasRequestedView_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_HasRequestedView_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_HasRequestedView_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_HasRequestedView_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_HasRequestedView()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBaseComponent_HasRequestedView_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyForBindings_Statics
	{
		struct CohtmlBaseComponent_eventIsReadyForBindings_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyForBindings_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((CohtmlBaseComponent_eventIsReadyForBindings_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyForBindings_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CohtmlBaseComponent_eventIsReadyForBindings_Parms), &Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyForBindings_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyForBindings_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyForBindings_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyForBindings_Statics::Function_MetaDataParams[] = {
		{ "Category", "View" },
		{ "Comment", "/** Tells if the View is ready to be created */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Tells if the View is ready to be created" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyForBindings_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBaseComponent, nullptr, "IsReadyForBindings", nullptr, nullptr, sizeof(CohtmlBaseComponent_eventIsReadyForBindings_Parms), Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyForBindings_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyForBindings_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyForBindings_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyForBindings_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyForBindings()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyForBindings_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyToCreateView_Statics
	{
		struct CohtmlBaseComponent_eventIsReadyToCreateView_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyToCreateView_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((CohtmlBaseComponent_eventIsReadyToCreateView_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyToCreateView_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CohtmlBaseComponent_eventIsReadyToCreateView_Parms), &Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyToCreateView_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyToCreateView_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyToCreateView_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyToCreateView_Statics::Function_MetaDataParams[] = {
		{ "Category", "View" },
		{ "Comment", "/** Tells if the View is ready to be created */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Tells if the View is ready to be created" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyToCreateView_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBaseComponent, nullptr, "IsReadyToCreateView", nullptr, nullptr, sizeof(CohtmlBaseComponent_eventIsReadyToCreateView_Parms), Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyToCreateView_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyToCreateView_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyToCreateView_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyToCreateView_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyToCreateView()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyToCreateView_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBaseComponent_Load_Statics
	{
		struct CohtmlBaseComponent_eventLoad_Parms
		{
			FString path;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_path_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_path;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_Load_Statics::NewProp_path_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCohtmlBaseComponent_Load_Statics::NewProp_path = { "path", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBaseComponent_eventLoad_Parms, path), METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_Load_Statics::NewProp_path_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_Load_Statics::NewProp_path_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBaseComponent_Load_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBaseComponent_Load_Statics::NewProp_path,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_Load_Statics::Function_MetaDataParams[] = {
		{ "Category", "View" },
		{ "Comment", "/** Requests a new URL to be loaded in the View */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Requests a new URL to be loaded in the View" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBaseComponent_Load_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBaseComponent, nullptr, "Load", nullptr, nullptr, sizeof(CohtmlBaseComponent_eventLoad_Parms), Z_Construct_UFunction_UCohtmlBaseComponent_Load_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_Load_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_Load_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_Load_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_Load()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBaseComponent_Load_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBaseComponent_Reload_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_Reload_Statics::Function_MetaDataParams[] = {
		{ "Category", "View" },
		{ "Comment", "/** Requests the View to reload the current URL */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Requests the View to reload the current URL" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBaseComponent_Reload_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBaseComponent, nullptr, "Reload", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_Reload_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_Reload_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_Reload()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBaseComponent_Reload_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBaseComponent_Resize_Statics
	{
		struct CohtmlBaseComponent_eventResize_Parms
		{
			int32 width;
			int32 height;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_height;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_width;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UCohtmlBaseComponent_Resize_Statics::NewProp_height = { "height", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBaseComponent_eventResize_Parms, height), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UCohtmlBaseComponent_Resize_Statics::NewProp_width = { "width", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBaseComponent_eventResize_Parms, width), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBaseComponent_Resize_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBaseComponent_Resize_Statics::NewProp_height,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBaseComponent_Resize_Statics::NewProp_width,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_Resize_Statics::Function_MetaDataParams[] = {
		{ "Category", "View" },
		{ "Comment", "/*uint32*/" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "uint32" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBaseComponent_Resize_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBaseComponent, nullptr, "Resize", nullptr, nullptr, sizeof(CohtmlBaseComponent_eventResize_Parms), Z_Construct_UFunction_UCohtmlBaseComponent_Resize_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_Resize_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_Resize_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_Resize_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_Resize()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBaseComponent_Resize_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBaseComponent_SetSoundAttenuation_Statics
	{
		struct CohtmlBaseComponent_eventSetSoundAttenuation_Parms
		{
			FSoundAttenuationSettings Settings;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Settings_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Settings;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_SetSoundAttenuation_Statics::NewProp_Settings_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UCohtmlBaseComponent_SetSoundAttenuation_Statics::NewProp_Settings = { "Settings", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBaseComponent_eventSetSoundAttenuation_Parms, Settings), Z_Construct_UScriptStruct_FSoundAttenuationSettings, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_SetSoundAttenuation_Statics::NewProp_Settings_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_SetSoundAttenuation_Statics::NewProp_Settings_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBaseComponent_SetSoundAttenuation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBaseComponent_SetSoundAttenuation_Statics::NewProp_Settings,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_SetSoundAttenuation_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio" },
		{ "Comment", "/** Sets the AttenuationSettings for the Sound Components\n\x09Note: Sound is 2D by default. It can be changed to 3D if appropriate AttenuationSettings is set.\n\x09""for more details look at Unreal's documentation for AttenuationSettings */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Sets the AttenuationSettings for the Sound Components\n      Note: Sound is 2D by default. It can be changed to 3D if appropriate AttenuationSettings is set.\n      for more details look at Unreal's documentation for AttenuationSettings" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBaseComponent_SetSoundAttenuation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBaseComponent, nullptr, "SetSoundAttenuation", nullptr, nullptr, sizeof(CohtmlBaseComponent_eventSetSoundAttenuation_Parms), Z_Construct_UFunction_UCohtmlBaseComponent_SetSoundAttenuation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_SetSoundAttenuation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_SetSoundAttenuation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_SetSoundAttenuation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_SetSoundAttenuation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBaseComponent_SetSoundAttenuation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBaseComponent_ShowPaintRects_Statics
	{
		struct CohtmlBaseComponent_eventShowPaintRects_Parms
		{
			bool show;
		};
		static void NewProp_show_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_show;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UCohtmlBaseComponent_ShowPaintRects_Statics::NewProp_show_SetBit(void* Obj)
	{
		((CohtmlBaseComponent_eventShowPaintRects_Parms*)Obj)->show = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCohtmlBaseComponent_ShowPaintRects_Statics::NewProp_show = { "show", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CohtmlBaseComponent_eventShowPaintRects_Parms), &Z_Construct_UFunction_UCohtmlBaseComponent_ShowPaintRects_Statics::NewProp_show_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBaseComponent_ShowPaintRects_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBaseComponent_ShowPaintRects_Statics::NewProp_show,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_ShowPaintRects_Statics::Function_MetaDataParams[] = {
		{ "Category", "View" },
		{ "Comment", "/** Tells the view to show/hide debug paint rectangles */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Tells the view to show/hide debug paint rectangles" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBaseComponent_ShowPaintRects_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBaseComponent, nullptr, "ShowPaintRects", nullptr, nullptr, sizeof(CohtmlBaseComponent_eventShowPaintRects_Parms), Z_Construct_UFunction_UCohtmlBaseComponent_ShowPaintRects_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_ShowPaintRects_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_ShowPaintRects_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_ShowPaintRects_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_ShowPaintRects()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBaseComponent_ShowPaintRects_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBaseComponent_SynchronizeModels_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_SynchronizeModels_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Synchronize all models marked for update. */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Synchronize all models marked for update." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBaseComponent_SynchronizeModels_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBaseComponent, nullptr, "SynchronizeModels", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x44020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_SynchronizeModels_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_SynchronizeModels_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_SynchronizeModels()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBaseComponent_SynchronizeModels_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBaseComponent_TriggerJSEvent_Statics
	{
		struct CohtmlBaseComponent_eventTriggerJSEvent_Parms
		{
			FString name;
			UCohtmlJSEvent* eventData;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_eventData;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_name_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_name;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBaseComponent_TriggerJSEvent_Statics::NewProp_eventData = { "eventData", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBaseComponent_eventTriggerJSEvent_Parms, eventData), Z_Construct_UClass_UCohtmlJSEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_TriggerJSEvent_Statics::NewProp_name_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCohtmlBaseComponent_TriggerJSEvent_Statics::NewProp_name = { "name", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBaseComponent_eventTriggerJSEvent_Parms, name), METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_TriggerJSEvent_Statics::NewProp_name_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_TriggerJSEvent_Statics::NewProp_name_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBaseComponent_TriggerJSEvent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBaseComponent_TriggerJSEvent_Statics::NewProp_eventData,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBaseComponent_TriggerJSEvent_Statics::NewProp_name,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_TriggerJSEvent_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Triggers an event in JavaScript */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Triggers an event in JavaScript" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBaseComponent_TriggerJSEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBaseComponent, nullptr, "TriggerJSEvent", nullptr, nullptr, sizeof(CohtmlBaseComponent_eventTriggerJSEvent_Parms), Z_Construct_UFunction_UCohtmlBaseComponent_TriggerJSEvent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_TriggerJSEvent_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x44020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_TriggerJSEvent_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_TriggerJSEvent_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_TriggerJSEvent()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBaseComponent_TriggerJSEvent_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromObject_Statics
	{
		struct CohtmlBaseComponent_eventUpdateWholeDataModelFromObject_Parms
		{
			UObject* Model;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Model;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromObject_Statics::NewProp_Model = { "Model", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBaseComponent_eventUpdateWholeDataModelFromObject_Parms, Model), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromObject_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromObject_Statics::NewProp_Model,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromObject_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Marks an Object model for update. The UI using this data model will be updated during the next\n\x09""call to SynchronizeModels. For optimum performance, call SynchronizeModels as rarely as possible.\n\x09(e.g. once per frame)*/" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Marks an Object model for update. The UI using this data model will be updated during the next\n      call to SynchronizeModels. For optimum performance, call SynchronizeModels as rarely as possible.\n      (e.g. once per frame)" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromObject_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBaseComponent, nullptr, "UpdateWholeDataModelFromObject", nullptr, nullptr, sizeof(CohtmlBaseComponent_eventUpdateWholeDataModelFromObject_Parms), Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromObject_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromObject_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x44020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromObject_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromObject_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromObject()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromObject_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromStruct_Statics
	{
		struct CohtmlBaseComponent_eventUpdateWholeDataModelFromStruct_Parms
		{
			const UStructProperty* Struct;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Struct_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Struct;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromStruct_Statics::NewProp_Struct_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromStruct_Statics::NewProp_Struct = { "Struct", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlBaseComponent_eventUpdateWholeDataModelFromStruct_Parms, Struct), Z_Construct_UClass_UStructProperty, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromStruct_Statics::NewProp_Struct_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromStruct_Statics::NewProp_Struct_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromStruct_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromStruct_Statics::NewProp_Struct,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromStruct_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Marks a Struct model for update. The UI using this data model will be updated during the next\n\x09""call to SynchronizeModels. For optimum performance, call SynchronizeModels as rarely as possible.\n\x09(e.g. once per frame)*/" },
		{ "CustomStructureParam", "Struct" },
		{ "CustomThunk", "true" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Marks a Struct model for update. The UI using this data model will be updated during the next\n      call to SynchronizeModels. For optimum performance, call SynchronizeModels as rarely as possible.\n      (e.g. once per frame)" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromStruct_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlBaseComponent, nullptr, "UpdateWholeDataModelFromStruct", nullptr, nullptr, sizeof(CohtmlBaseComponent_eventUpdateWholeDataModelFromStruct_Parms), Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromStruct_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromStruct_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x44020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromStruct_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromStruct_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromStruct()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromStruct_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UCohtmlBaseComponent_NoRegister()
	{
		return UCohtmlBaseComponent::StaticClass();
	}
	struct Z_Construct_UClass_UCohtmlBaseComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bDelayedUpdate_MetaData[];
#endif
		static void NewProp_bDelayedUpdate_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bDelayedUpdate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bReceiveInput_MetaData[];
#endif
		static void NewProp_bReceiveInput_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bReceiveInput;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Filter_MetaData[];
#endif
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Filter;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Texture_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Texture;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bEnableComplexCSSSupport_MetaData[];
#endif
		static void NewProp_bEnableComplexCSSSupport_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bEnableComplexCSSSupport;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ScriptingReady_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_ScriptingReady;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BindingsReleased_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_BindingsReleased;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ReadyForBindings_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_ReadyForBindings;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCohtmlBaseComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UCohtmlBaseComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UCohtmlBaseComponent_BeginDebugFrameSave, "BeginDebugFrameSave" }, // 4121015988
		{ &Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromObject, "CreateDataModelFromObject" }, // 2877066128
		{ &Z_Construct_UFunction_UCohtmlBaseComponent_CreateDataModelFromStruct, "CreateDataModelFromStruct" }, // 122171847
		{ &Z_Construct_UFunction_UCohtmlBaseComponent_CreateJSEvent, "CreateJSEvent" }, // 1745312805
		{ &Z_Construct_UFunction_UCohtmlBaseComponent_DebugSaveNextFrame, "DebugSaveNextFrame" }, // 3579298884
		{ &Z_Construct_UFunction_UCohtmlBaseComponent_EnableDelayedUpdate, "EnableDelayedUpdate" }, // 1510314672
		{ &Z_Construct_UFunction_UCohtmlBaseComponent_EndDebugFrameSave, "EndDebugFrameSave" }, // 1225434672
		{ &Z_Construct_UFunction_UCohtmlBaseComponent_HasRequestedView, "HasRequestedView" }, // 2301739451
		{ &Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyForBindings, "IsReadyForBindings" }, // 145394743
		{ &Z_Construct_UFunction_UCohtmlBaseComponent_IsReadyToCreateView, "IsReadyToCreateView" }, // 705072458
		{ &Z_Construct_UFunction_UCohtmlBaseComponent_Load, "Load" }, // 251107491
		{ &Z_Construct_UFunction_UCohtmlBaseComponent_Reload, "Reload" }, // 3708422827
		{ &Z_Construct_UFunction_UCohtmlBaseComponent_Resize, "Resize" }, // 1811707455
		{ &Z_Construct_UFunction_UCohtmlBaseComponent_SetSoundAttenuation, "SetSoundAttenuation" }, // 3384592514
		{ &Z_Construct_UFunction_UCohtmlBaseComponent_ShowPaintRects, "ShowPaintRects" }, // 1626234263
		{ &Z_Construct_UFunction_UCohtmlBaseComponent_SynchronizeModels, "SynchronizeModels" }, // 3745340390
		{ &Z_Construct_UFunction_UCohtmlBaseComponent_TriggerJSEvent, "TriggerJSEvent" }, // 2862017674
		{ &Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromObject, "UpdateWholeDataModelFromObject" }, // 2086814567
		{ &Z_Construct_UFunction_UCohtmlBaseComponent_UpdateWholeDataModelFromStruct, "UpdateWholeDataModelFromStruct" }, // 3528331205
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlBaseComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "DisplayName", "Prysm Base Component" },
		{ "IncludePath", "CohtmlBaseComponent.h" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bDelayedUpdate_MetaData[] = {
		{ "Category", "View" },
		{ "Comment", "/** Changes this component's tick group to TG_PostUpdateWork and sends bindings before drawing.\n\x09""For more information refer to the FAQ section of the documentation. */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Changes this component's tick group to TG_PostUpdateWork and sends bindings before drawing.\n      For more information refer to the FAQ section of the documentation." },
	};
#endif
	void Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bDelayedUpdate_SetBit(void* Obj)
	{
		((UCohtmlBaseComponent*)Obj)->bDelayedUpdate = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bDelayedUpdate = { "bDelayedUpdate", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UCohtmlBaseComponent), &Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bDelayedUpdate_SetBit, METADATA_PARAMS(Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bDelayedUpdate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bDelayedUpdate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bReceiveInput_MetaData[] = {
		{ "Category", "View" },
		{ "Comment", "/** Indicates whether input is forwarded to this view */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Indicates whether input is forwarded to this view" },
	};
#endif
	void Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bReceiveInput_SetBit(void* Obj)
	{
		((UCohtmlBaseComponent*)Obj)->bReceiveInput = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bReceiveInput = { "bReceiveInput", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UCohtmlBaseComponent), &Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bReceiveInput_SetBit, METADATA_PARAMS(Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bReceiveInput_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bReceiveInput_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_Filter_MetaData[] = {
		{ "Category", "View" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_Filter = { "Filter", nullptr, (EPropertyFlags)0x0010040000000005, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlBaseComponent, Filter), Z_Construct_UEnum_Engine_TextureFilter, METADATA_PARAMS(Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_Filter_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_Filter_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_Texture_MetaData[] = {
		{ "Category", "View" },
		{ "Comment", "/** Gives access to the UI Texture */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Gives access to the UI Texture" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_Texture = { "Texture", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlBaseComponent, Texture), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_Texture_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_Texture_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bEnableComplexCSSSupport_MetaData[] = {
		{ "Category", "View" },
		{ "Comment", "/** Whether to enable support for complex CSS selectors (e.g. div > p, div ~ p)*/" },
		{ "DisplayName", "Enable Complex CSS Selector Support" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Whether to enable support for complex CSS selectors (e.g. div > p, div ~ p)" },
	};
#endif
	void Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bEnableComplexCSSSupport_SetBit(void* Obj)
	{
		((UCohtmlBaseComponent*)Obj)->bEnableComplexCSSSupport = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bEnableComplexCSSSupport = { "bEnableComplexCSSSupport", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UCohtmlBaseComponent), &Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bEnableComplexCSSSupport_SetBit, METADATA_PARAMS(Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bEnableComplexCSSSupport_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bEnableComplexCSSSupport_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_ScriptingReady_MetaData[] = {
		{ "Comment", "/** Called when the View is ready to accept events */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "Called when the View is ready to accept events" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_ScriptingReady = { "ScriptingReady", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlBaseComponent, ScriptingReady), Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlScriptingReady__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_ScriptingReady_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_ScriptingReady_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_BindingsReleased_MetaData[] = {
		{ "Comment", "/** When fired, the View has released its bindings. */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "When fired, the View has released its bindings." },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_BindingsReleased = { "BindingsReleased", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlBaseComponent, BindingsReleased), Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlBindingsReleasedSignature__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_BindingsReleased_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_BindingsReleased_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_ReadyForBindings_MetaData[] = {
		{ "Comment", "/** When fired, the View is ready for binding events. Any event bound prior to this will be ignored */" },
		{ "ModuleRelativePath", "Classes/CohtmlBaseComponent.h" },
		{ "ToolTip", "When fired, the View is ready for binding events. Any event bound prior to this will be ignored" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_ReadyForBindings = { "ReadyForBindings", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlBaseComponent, ReadyForBindings), Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlReadyForBindingsSignature__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_ReadyForBindings_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_ReadyForBindings_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCohtmlBaseComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bDelayedUpdate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bReceiveInput,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_Filter,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_Texture,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_bEnableComplexCSSSupport,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_ScriptingReady,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_BindingsReleased,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlBaseComponent_Statics::NewProp_ReadyForBindings,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCohtmlBaseComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCohtmlBaseComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCohtmlBaseComponent_Statics::ClassParams = {
		&UCohtmlBaseComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UCohtmlBaseComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlBaseComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UCohtmlBaseComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlBaseComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCohtmlBaseComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCohtmlBaseComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCohtmlBaseComponent, 3371686688);
	template<> COHTMLPLUGIN_API UClass* StaticClass<UCohtmlBaseComponent>()
	{
		return UCohtmlBaseComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCohtmlBaseComponent(Z_Construct_UClass_UCohtmlBaseComponent, &UCohtmlBaseComponent::StaticClass, TEXT("/Script/CohtmlPlugin"), TEXT("UCohtmlBaseComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCohtmlBaseComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
