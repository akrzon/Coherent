// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CohtmlPlugin/Classes/CohtmlWidget.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCohtmlWidget() {}
// Cross Module References
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlWidget_NoRegister();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlWidget();
	UMG_API UClass* Z_Construct_UClass_UWidget();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromObject();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct();
	COREUOBJECT_API UClass* Z_Construct_UClass_UStructProperty();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlWidget_CreateJSEvent();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlJSEvent_NoRegister();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlWidget_GetInputPropagationBehaviour();
	COHTMLPLUGIN_API UEnum* Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputPropagationBehaviour();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlWidget_GetRenderTexture();
	ENGINE_API UClass* Z_Construct_UClass_UTextureRenderTarget2D_NoRegister();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlWidget_HasRequestedView();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlWidget_IsReadyForBindings();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlWidget_IsReadyToCreateView();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlWidget_Load();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlWidget_Reload();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlWidget_SetInputPropagationBehaviour();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlWidget_SetSoundAttenuation();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FSoundAttenuationSettings();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlWidget_ShowPaintRects();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlWidget_SynchronizeModels();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlWidget_TriggerJSEvent();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromObject();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromStruct();
	ENGINE_API UEnum* Z_Construct_UEnum_Engine_TextureFilter();
	COHTMLPLUGIN_API UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlScriptingReady__DelegateSignature();
	COHTMLPLUGIN_API UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlBindingsReleasedSignature__DelegateSignature();
	COHTMLPLUGIN_API UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlReadyForBindingsSignature__DelegateSignature();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
// End Cross Module References
	void UCohtmlWidget::StaticRegisterNativesUCohtmlWidget()
	{
		UClass* Class = UCohtmlWidget::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CreateDataModelFromObject", &UCohtmlWidget::execCreateDataModelFromObject },
			{ "CreateDataModelFromStruct", &UCohtmlWidget::execCreateDataModelFromStruct },
			{ "CreateJSEvent", &UCohtmlWidget::execCreateJSEvent },
			{ "GetInputPropagationBehaviour", &UCohtmlWidget::execGetInputPropagationBehaviour },
			{ "GetRenderTexture", &UCohtmlWidget::execGetRenderTexture },
			{ "HasRequestedView", &UCohtmlWidget::execHasRequestedView },
			{ "IsReadyForBindings", &UCohtmlWidget::execIsReadyForBindings },
			{ "IsReadyToCreateView", &UCohtmlWidget::execIsReadyToCreateView },
			{ "Load", &UCohtmlWidget::execLoad },
			{ "Reload", &UCohtmlWidget::execReload },
			{ "SetInputPropagationBehaviour", &UCohtmlWidget::execSetInputPropagationBehaviour },
			{ "SetSoundAttenuation", &UCohtmlWidget::execSetSoundAttenuation },
			{ "ShowPaintRects", &UCohtmlWidget::execShowPaintRects },
			{ "SynchronizeModels", &UCohtmlWidget::execSynchronizeModels },
			{ "TriggerJSEvent", &UCohtmlWidget::execTriggerJSEvent },
			{ "UpdateWholeDataModelFromObject", &UCohtmlWidget::execUpdateWholeDataModelFromObject },
			{ "UpdateWholeDataModelFromStruct", &UCohtmlWidget::execUpdateWholeDataModelFromStruct },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromObject_Statics
	{
		struct CohtmlWidget_eventCreateDataModelFromObject_Parms
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
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromObject_Statics::NewProp_Model = { "Model", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlWidget_eventCreateDataModelFromObject_Parms, Model), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromObject_Statics::NewProp_Name_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromObject_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlWidget_eventCreateDataModelFromObject_Parms, Name), METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromObject_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromObject_Statics::NewProp_Name_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromObject_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromObject_Statics::NewProp_Model,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromObject_Statics::NewProp_Name,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromObject_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Creates a global variable (data model) in JavaScript from an UObject */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Creates a global variable (data model) in JavaScript from an UObject" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromObject_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlWidget, nullptr, "CreateDataModelFromObject", nullptr, nullptr, sizeof(CohtmlWidget_eventCreateDataModelFromObject_Parms), Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromObject_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromObject_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromObject_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromObject_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromObject()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromObject_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct_Statics
	{
		struct CohtmlWidget_eventCreateDataModelFromStruct_Parms
		{
			FString Name;
			const UStructProperty* Struct;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Struct_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Struct;
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct_Statics::NewProp_Struct_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct_Statics::NewProp_Struct = { "Struct", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlWidget_eventCreateDataModelFromStruct_Parms, Struct), Z_Construct_UClass_UStructProperty, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct_Statics::NewProp_Struct_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct_Statics::NewProp_Struct_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct_Statics::NewProp_Name_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlWidget_eventCreateDataModelFromStruct_Parms, Name), METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct_Statics::NewProp_Name_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct_Statics::NewProp_Struct,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct_Statics::NewProp_Name,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Creates a global variable (data model) in JavaScript from a UStruct */" },
		{ "CustomStructureParam", "Struct" },
		{ "CustomThunk", "true" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Creates a global variable (data model) in JavaScript from a UStruct" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlWidget, nullptr, "CreateDataModelFromStruct", nullptr, nullptr, sizeof(CohtmlWidget_eventCreateDataModelFromStruct_Parms), Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlWidget_CreateJSEvent_Statics
	{
		struct CohtmlWidget_eventCreateJSEvent_Parms
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
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlWidget_CreateJSEvent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlWidget_eventCreateJSEvent_Parms, ReturnValue), Z_Construct_UClass_UCohtmlJSEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlWidget_CreateJSEvent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlWidget_CreateJSEvent_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_CreateJSEvent_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Creates an event that will be executed in JavaScript */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Creates an event that will be executed in JavaScript" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlWidget_CreateJSEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlWidget, nullptr, "CreateJSEvent", nullptr, nullptr, sizeof(CohtmlWidget_eventCreateJSEvent_Parms), Z_Construct_UFunction_UCohtmlWidget_CreateJSEvent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_CreateJSEvent_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_CreateJSEvent_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_CreateJSEvent_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlWidget_CreateJSEvent()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlWidget_CreateJSEvent_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlWidget_GetInputPropagationBehaviour_Statics
	{
		struct CohtmlWidget_eventGetInputPropagationBehaviour_Parms
		{
			TEnumAsByte<ECohtmlInputPropagationBehaviour::Type> ReturnValue;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UCohtmlWidget_GetInputPropagationBehaviour_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlWidget_eventGetInputPropagationBehaviour_Parms, ReturnValue), Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputPropagationBehaviour, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlWidget_GetInputPropagationBehaviour_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlWidget_GetInputPropagationBehaviour_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_GetInputPropagationBehaviour_Statics::Function_MetaDataParams[] = {
		{ "Category", "View" },
		{ "Comment", "/** Gets the type of input that the widget will propagate to the game */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Gets the type of input that the widget will propagate to the game" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlWidget_GetInputPropagationBehaviour_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlWidget, nullptr, "GetInputPropagationBehaviour", nullptr, nullptr, sizeof(CohtmlWidget_eventGetInputPropagationBehaviour_Parms), Z_Construct_UFunction_UCohtmlWidget_GetInputPropagationBehaviour_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_GetInputPropagationBehaviour_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_GetInputPropagationBehaviour_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_GetInputPropagationBehaviour_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlWidget_GetInputPropagationBehaviour()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlWidget_GetInputPropagationBehaviour_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlWidget_GetRenderTexture_Statics
	{
		struct CohtmlWidget_eventGetRenderTexture_Parms
		{
			UTextureRenderTarget2D* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlWidget_GetRenderTexture_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlWidget_eventGetRenderTexture_Parms, ReturnValue), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlWidget_GetRenderTexture_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlWidget_GetRenderTexture_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_GetRenderTexture_Statics::Function_MetaDataParams[] = {
		{ "Category", "View" },
		{ "Comment", "/** Gives access to the UI Texture */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Gives access to the UI Texture" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlWidget_GetRenderTexture_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlWidget, nullptr, "GetRenderTexture", nullptr, nullptr, sizeof(CohtmlWidget_eventGetRenderTexture_Parms), Z_Construct_UFunction_UCohtmlWidget_GetRenderTexture_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_GetRenderTexture_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_GetRenderTexture_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_GetRenderTexture_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlWidget_GetRenderTexture()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlWidget_GetRenderTexture_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlWidget_HasRequestedView_Statics
	{
		struct CohtmlWidget_eventHasRequestedView_Parms
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
	void Z_Construct_UFunction_UCohtmlWidget_HasRequestedView_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((CohtmlWidget_eventHasRequestedView_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCohtmlWidget_HasRequestedView_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CohtmlWidget_eventHasRequestedView_Parms), &Z_Construct_UFunction_UCohtmlWidget_HasRequestedView_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlWidget_HasRequestedView_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlWidget_HasRequestedView_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_HasRequestedView_Statics::Function_MetaDataParams[] = {
		{ "Category", "View" },
		{ "Comment", "/** Tells if a View has been scheduled for creation */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Tells if a View has been scheduled for creation" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlWidget_HasRequestedView_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlWidget, nullptr, "HasRequestedView", nullptr, nullptr, sizeof(CohtmlWidget_eventHasRequestedView_Parms), Z_Construct_UFunction_UCohtmlWidget_HasRequestedView_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_HasRequestedView_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_HasRequestedView_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_HasRequestedView_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlWidget_HasRequestedView()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlWidget_HasRequestedView_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlWidget_IsReadyForBindings_Statics
	{
		struct CohtmlWidget_eventIsReadyForBindings_Parms
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
	void Z_Construct_UFunction_UCohtmlWidget_IsReadyForBindings_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((CohtmlWidget_eventIsReadyForBindings_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCohtmlWidget_IsReadyForBindings_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CohtmlWidget_eventIsReadyForBindings_Parms), &Z_Construct_UFunction_UCohtmlWidget_IsReadyForBindings_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlWidget_IsReadyForBindings_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlWidget_IsReadyForBindings_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_IsReadyForBindings_Statics::Function_MetaDataParams[] = {
		{ "Category", "View" },
		{ "Comment", "/** Tells if the View is ready to be created */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Tells if the View is ready to be created" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlWidget_IsReadyForBindings_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlWidget, nullptr, "IsReadyForBindings", nullptr, nullptr, sizeof(CohtmlWidget_eventIsReadyForBindings_Parms), Z_Construct_UFunction_UCohtmlWidget_IsReadyForBindings_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_IsReadyForBindings_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_IsReadyForBindings_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_IsReadyForBindings_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlWidget_IsReadyForBindings()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlWidget_IsReadyForBindings_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlWidget_IsReadyToCreateView_Statics
	{
		struct CohtmlWidget_eventIsReadyToCreateView_Parms
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
	void Z_Construct_UFunction_UCohtmlWidget_IsReadyToCreateView_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((CohtmlWidget_eventIsReadyToCreateView_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCohtmlWidget_IsReadyToCreateView_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CohtmlWidget_eventIsReadyToCreateView_Parms), &Z_Construct_UFunction_UCohtmlWidget_IsReadyToCreateView_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlWidget_IsReadyToCreateView_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlWidget_IsReadyToCreateView_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_IsReadyToCreateView_Statics::Function_MetaDataParams[] = {
		{ "Category", "View" },
		{ "Comment", "/** Tells if the View is ready to be created */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Tells if the View is ready to be created" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlWidget_IsReadyToCreateView_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlWidget, nullptr, "IsReadyToCreateView", nullptr, nullptr, sizeof(CohtmlWidget_eventIsReadyToCreateView_Parms), Z_Construct_UFunction_UCohtmlWidget_IsReadyToCreateView_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_IsReadyToCreateView_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_IsReadyToCreateView_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_IsReadyToCreateView_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlWidget_IsReadyToCreateView()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlWidget_IsReadyToCreateView_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlWidget_Load_Statics
	{
		struct CohtmlWidget_eventLoad_Parms
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_Load_Statics::NewProp_path_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCohtmlWidget_Load_Statics::NewProp_path = { "path", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlWidget_eventLoad_Parms, path), METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_Load_Statics::NewProp_path_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_Load_Statics::NewProp_path_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlWidget_Load_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlWidget_Load_Statics::NewProp_path,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_Load_Statics::Function_MetaDataParams[] = {
		{ "Category", "View" },
		{ "Comment", "/** Requests a new URL to be loaded in the View */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Requests a new URL to be loaded in the View" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlWidget_Load_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlWidget, nullptr, "Load", nullptr, nullptr, sizeof(CohtmlWidget_eventLoad_Parms), Z_Construct_UFunction_UCohtmlWidget_Load_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_Load_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_Load_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_Load_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlWidget_Load()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlWidget_Load_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlWidget_Reload_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_Reload_Statics::Function_MetaDataParams[] = {
		{ "Category", "View" },
		{ "Comment", "/** Requests the View to reload the current URL */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Requests the View to reload the current URL" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlWidget_Reload_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlWidget, nullptr, "Reload", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_Reload_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_Reload_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlWidget_Reload()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlWidget_Reload_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlWidget_SetInputPropagationBehaviour_Statics
	{
		struct CohtmlWidget_eventSetInputPropagationBehaviour_Parms
		{
			TEnumAsByte<ECohtmlInputPropagationBehaviour::Type> Propagation;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Propagation;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UCohtmlWidget_SetInputPropagationBehaviour_Statics::NewProp_Propagation = { "Propagation", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlWidget_eventSetInputPropagationBehaviour_Parms, Propagation), Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputPropagationBehaviour, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlWidget_SetInputPropagationBehaviour_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlWidget_SetInputPropagationBehaviour_Statics::NewProp_Propagation,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_SetInputPropagationBehaviour_Statics::Function_MetaDataParams[] = {
		{ "Category", "View" },
		{ "Comment", "/** Sets the type of input that the widget will propagate to the game */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Sets the type of input that the widget will propagate to the game" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlWidget_SetInputPropagationBehaviour_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlWidget, nullptr, "SetInputPropagationBehaviour", nullptr, nullptr, sizeof(CohtmlWidget_eventSetInputPropagationBehaviour_Parms), Z_Construct_UFunction_UCohtmlWidget_SetInputPropagationBehaviour_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_SetInputPropagationBehaviour_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_SetInputPropagationBehaviour_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_SetInputPropagationBehaviour_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlWidget_SetInputPropagationBehaviour()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlWidget_SetInputPropagationBehaviour_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlWidget_SetSoundAttenuation_Statics
	{
		struct CohtmlWidget_eventSetSoundAttenuation_Parms
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_SetSoundAttenuation_Statics::NewProp_Settings_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UCohtmlWidget_SetSoundAttenuation_Statics::NewProp_Settings = { "Settings", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlWidget_eventSetSoundAttenuation_Parms, Settings), Z_Construct_UScriptStruct_FSoundAttenuationSettings, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_SetSoundAttenuation_Statics::NewProp_Settings_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_SetSoundAttenuation_Statics::NewProp_Settings_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlWidget_SetSoundAttenuation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlWidget_SetSoundAttenuation_Statics::NewProp_Settings,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_SetSoundAttenuation_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio" },
		{ "Comment", "/** Sets the AttenuationSettings for the Sound Components\n\x09Note: Sound is 2D by default. It can be changed to 3D if appropriate AttenuationSettings is set.\n\x09""for more details look at Unreal's documentation for AttenuationSettings */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Sets the AttenuationSettings for the Sound Components\n      Note: Sound is 2D by default. It can be changed to 3D if appropriate AttenuationSettings is set.\n      for more details look at Unreal's documentation for AttenuationSettings" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlWidget_SetSoundAttenuation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlWidget, nullptr, "SetSoundAttenuation", nullptr, nullptr, sizeof(CohtmlWidget_eventSetSoundAttenuation_Parms), Z_Construct_UFunction_UCohtmlWidget_SetSoundAttenuation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_SetSoundAttenuation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_SetSoundAttenuation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_SetSoundAttenuation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlWidget_SetSoundAttenuation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlWidget_SetSoundAttenuation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlWidget_ShowPaintRects_Statics
	{
		struct CohtmlWidget_eventShowPaintRects_Parms
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
	void Z_Construct_UFunction_UCohtmlWidget_ShowPaintRects_Statics::NewProp_show_SetBit(void* Obj)
	{
		((CohtmlWidget_eventShowPaintRects_Parms*)Obj)->show = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCohtmlWidget_ShowPaintRects_Statics::NewProp_show = { "show", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CohtmlWidget_eventShowPaintRects_Parms), &Z_Construct_UFunction_UCohtmlWidget_ShowPaintRects_Statics::NewProp_show_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlWidget_ShowPaintRects_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlWidget_ShowPaintRects_Statics::NewProp_show,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_ShowPaintRects_Statics::Function_MetaDataParams[] = {
		{ "Category", "View" },
		{ "Comment", "/** Tells the view to show/hide debug paint rectangles */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Tells the view to show/hide debug paint rectangles" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlWidget_ShowPaintRects_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlWidget, nullptr, "ShowPaintRects", nullptr, nullptr, sizeof(CohtmlWidget_eventShowPaintRects_Parms), Z_Construct_UFunction_UCohtmlWidget_ShowPaintRects_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_ShowPaintRects_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_ShowPaintRects_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_ShowPaintRects_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlWidget_ShowPaintRects()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlWidget_ShowPaintRects_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlWidget_SynchronizeModels_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_SynchronizeModels_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Synchronize all models marked for update. */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Synchronize all models marked for update." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlWidget_SynchronizeModels_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlWidget, nullptr, "SynchronizeModels", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x44020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_SynchronizeModels_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_SynchronizeModels_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlWidget_SynchronizeModels()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlWidget_SynchronizeModels_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlWidget_TriggerJSEvent_Statics
	{
		struct CohtmlWidget_eventTriggerJSEvent_Parms
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
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlWidget_TriggerJSEvent_Statics::NewProp_eventData = { "eventData", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlWidget_eventTriggerJSEvent_Parms, eventData), Z_Construct_UClass_UCohtmlJSEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_TriggerJSEvent_Statics::NewProp_name_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCohtmlWidget_TriggerJSEvent_Statics::NewProp_name = { "name", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlWidget_eventTriggerJSEvent_Parms, name), METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_TriggerJSEvent_Statics::NewProp_name_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_TriggerJSEvent_Statics::NewProp_name_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlWidget_TriggerJSEvent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlWidget_TriggerJSEvent_Statics::NewProp_eventData,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlWidget_TriggerJSEvent_Statics::NewProp_name,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_TriggerJSEvent_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Triggers an event in JavaScript */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Triggers an event in JavaScript" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlWidget_TriggerJSEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlWidget, nullptr, "TriggerJSEvent", nullptr, nullptr, sizeof(CohtmlWidget_eventTriggerJSEvent_Parms), Z_Construct_UFunction_UCohtmlWidget_TriggerJSEvent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_TriggerJSEvent_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x44020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_TriggerJSEvent_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_TriggerJSEvent_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlWidget_TriggerJSEvent()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlWidget_TriggerJSEvent_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromObject_Statics
	{
		struct CohtmlWidget_eventUpdateWholeDataModelFromObject_Parms
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
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromObject_Statics::NewProp_Model = { "Model", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlWidget_eventUpdateWholeDataModelFromObject_Parms, Model), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromObject_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromObject_Statics::NewProp_Model,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromObject_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Marks an Object model for update. The UI using this data model will be updated during the next\n\x09""call to SynchronizeModels. For optimum performance, call SynchronizeModels as rarely as possible.\n\x09(e.g. once per frame)*/" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Marks an Object model for update. The UI using this data model will be updated during the next\n      call to SynchronizeModels. For optimum performance, call SynchronizeModels as rarely as possible.\n      (e.g. once per frame)" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromObject_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlWidget, nullptr, "UpdateWholeDataModelFromObject", nullptr, nullptr, sizeof(CohtmlWidget_eventUpdateWholeDataModelFromObject_Parms), Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromObject_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromObject_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x44020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromObject_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromObject_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromObject()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromObject_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromStruct_Statics
	{
		struct CohtmlWidget_eventUpdateWholeDataModelFromStruct_Parms
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromStruct_Statics::NewProp_Struct_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromStruct_Statics::NewProp_Struct = { "Struct", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlWidget_eventUpdateWholeDataModelFromStruct_Parms, Struct), Z_Construct_UClass_UStructProperty, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromStruct_Statics::NewProp_Struct_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromStruct_Statics::NewProp_Struct_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromStruct_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromStruct_Statics::NewProp_Struct,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromStruct_Statics::Function_MetaDataParams[] = {
		{ "Category", "ViewScripting" },
		{ "Comment", "/** Marks a Struct model for update. The UI using this data model will be updated during the next\n\x09""call to SynchronizeModels. For optimum performance, call SynchronizeModels as rarely as possible.\n\x09(e.g. once per frame)*/" },
		{ "CustomStructureParam", "Struct" },
		{ "CustomThunk", "true" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Marks a Struct model for update. The UI using this data model will be updated during the next\n      call to SynchronizeModels. For optimum performance, call SynchronizeModels as rarely as possible.\n      (e.g. once per frame)" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromStruct_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCohtmlWidget, nullptr, "UpdateWholeDataModelFromStruct", nullptr, nullptr, sizeof(CohtmlWidget_eventUpdateWholeDataModelFromStruct_Parms), Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromStruct_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromStruct_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x44020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromStruct_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromStruct_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromStruct()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromStruct_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UCohtmlWidget_NoRegister()
	{
		return UCohtmlWidget::StaticClass();
	}
	struct Z_Construct_UClass_UCohtmlWidget_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_URL_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_URL;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bGammaCorrectedMaterial_MetaData[];
#endif
		static void NewProp_bGammaCorrectedMaterial_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bGammaCorrectedMaterial;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InputPropagationBehaviour_MetaData[];
#endif
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_InputPropagationBehaviour;
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
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Owner_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Owner;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCohtmlWidget_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UCohtmlWidget_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromObject, "CreateDataModelFromObject" }, // 3239775274
		{ &Z_Construct_UFunction_UCohtmlWidget_CreateDataModelFromStruct, "CreateDataModelFromStruct" }, // 3244679477
		{ &Z_Construct_UFunction_UCohtmlWidget_CreateJSEvent, "CreateJSEvent" }, // 1250376526
		{ &Z_Construct_UFunction_UCohtmlWidget_GetInputPropagationBehaviour, "GetInputPropagationBehaviour" }, // 3137382042
		{ &Z_Construct_UFunction_UCohtmlWidget_GetRenderTexture, "GetRenderTexture" }, // 1661032623
		{ &Z_Construct_UFunction_UCohtmlWidget_HasRequestedView, "HasRequestedView" }, // 2906947040
		{ &Z_Construct_UFunction_UCohtmlWidget_IsReadyForBindings, "IsReadyForBindings" }, // 1594831418
		{ &Z_Construct_UFunction_UCohtmlWidget_IsReadyToCreateView, "IsReadyToCreateView" }, // 2723945837
		{ &Z_Construct_UFunction_UCohtmlWidget_Load, "Load" }, // 2976337111
		{ &Z_Construct_UFunction_UCohtmlWidget_Reload, "Reload" }, // 2220253886
		{ &Z_Construct_UFunction_UCohtmlWidget_SetInputPropagationBehaviour, "SetInputPropagationBehaviour" }, // 4040776441
		{ &Z_Construct_UFunction_UCohtmlWidget_SetSoundAttenuation, "SetSoundAttenuation" }, // 1102396912
		{ &Z_Construct_UFunction_UCohtmlWidget_ShowPaintRects, "ShowPaintRects" }, // 3486748415
		{ &Z_Construct_UFunction_UCohtmlWidget_SynchronizeModels, "SynchronizeModels" }, // 1994010663
		{ &Z_Construct_UFunction_UCohtmlWidget_TriggerJSEvent, "TriggerJSEvent" }, // 179411586
		{ &Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromObject, "UpdateWholeDataModelFromObject" }, // 2151907067
		{ &Z_Construct_UFunction_UCohtmlWidget_UpdateWholeDataModelFromStruct, "UpdateWholeDataModelFromStruct" }, // 4153191645
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlWidget_Statics::Class_MetaDataParams[] = {
		{ "Category", "Prysm" },
		{ "Comment", "/** A HTML5 control powered by Prysm. */" },
		{ "DisplayName", "Prysm Widget" },
		{ "IncludePath", "CohtmlWidget.h" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "A HTML5 control powered by Prysm." },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_URL_MetaData[] = {
		{ "Category", "View" },
		{ "Comment", "/** The URL to load when the View is created */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "The URL to load when the View is created" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_URL = { "URL", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlWidget, URL), METADATA_PARAMS(Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_URL_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_URL_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bGammaCorrectedMaterial_MetaData[] = {
		{ "Category", "View" },
		{ "Comment", "/** Whether this widget's material should be gamma corrected or not.\n\x09Set to true if the widget is used for HUD.\n\x09Set to false if it is used for in-game surface. */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Whether this widget's material should be gamma corrected or not.\n      Set to true if the widget is used for HUD.\n      Set to false if it is used for in-game surface." },
	};
#endif
	void Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bGammaCorrectedMaterial_SetBit(void* Obj)
	{
		((UCohtmlWidget*)Obj)->bGammaCorrectedMaterial = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bGammaCorrectedMaterial = { "bGammaCorrectedMaterial", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UCohtmlWidget), &Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bGammaCorrectedMaterial_SetBit, METADATA_PARAMS(Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bGammaCorrectedMaterial_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bGammaCorrectedMaterial_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_InputPropagationBehaviour_MetaData[] = {
		{ "Category", "View" },
		{ "Comment", "/** Indicates the type of input this view forwards to the game */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Indicates the type of input this view forwards to the game" },
	};
#endif
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_InputPropagationBehaviour = { "InputPropagationBehaviour", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlWidget, InputPropagationBehaviour), Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputPropagationBehaviour, METADATA_PARAMS(Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_InputPropagationBehaviour_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_InputPropagationBehaviour_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bReceiveInput_MetaData[] = {
		{ "Category", "View" },
		{ "Comment", "/** Indicates whether input is forwarded to this view */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Indicates whether input is forwarded to this view" },
	};
#endif
	void Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bReceiveInput_SetBit(void* Obj)
	{
		((UCohtmlWidget*)Obj)->bReceiveInput = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bReceiveInput = { "bReceiveInput", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UCohtmlWidget), &Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bReceiveInput_SetBit, METADATA_PARAMS(Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bReceiveInput_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bReceiveInput_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_Filter_MetaData[] = {
		{ "Category", "View" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
	};
#endif
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_Filter = { "Filter", nullptr, (EPropertyFlags)0x0010040000000005, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlWidget, Filter), Z_Construct_UEnum_Engine_TextureFilter, METADATA_PARAMS(Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_Filter_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_Filter_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bEnableComplexCSSSupport_MetaData[] = {
		{ "Category", "View" },
		{ "Comment", "/** Whether to enable support for complex CSS selectors (e.g. div > p, div ~ p)*/" },
		{ "DisplayName", "Enable Complex CSS Selector Support" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Whether to enable support for complex CSS selectors (e.g. div > p, div ~ p)" },
	};
#endif
	void Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bEnableComplexCSSSupport_SetBit(void* Obj)
	{
		((UCohtmlWidget*)Obj)->bEnableComplexCSSSupport = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bEnableComplexCSSSupport = { "bEnableComplexCSSSupport", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UCohtmlWidget), &Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bEnableComplexCSSSupport_SetBit, METADATA_PARAMS(Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bEnableComplexCSSSupport_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bEnableComplexCSSSupport_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_ScriptingReady_MetaData[] = {
		{ "Comment", "/** Called when the View is ready to accept events */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Called when the View is ready to accept events" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_ScriptingReady = { "ScriptingReady", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlWidget, ScriptingReady), Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlScriptingReady__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_ScriptingReady_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_ScriptingReady_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_BindingsReleased_MetaData[] = {
		{ "Comment", "/** When fired, the View has released its bindings. */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "When fired, the View has released its bindings." },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_BindingsReleased = { "BindingsReleased", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlWidget, BindingsReleased), Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlBindingsReleasedSignature__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_BindingsReleased_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_BindingsReleased_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_ReadyForBindings_MetaData[] = {
		{ "Comment", "/** When fired, the View is ready for binding events. Any event bound prior to this will be ignored */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "When fired, the View is ready for binding events. Any event bound prior to this will be ignored" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_ReadyForBindings = { "ReadyForBindings", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlWidget, ReadyForBindings), Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlReadyForBindingsSignature__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_ReadyForBindings_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_ReadyForBindings_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_Owner_MetaData[] = {
		{ "Category", "View" },
		{ "Comment", "/** Gets or sets the Actor containing any LiveViewComponents. */" },
		{ "ModuleRelativePath", "Classes/CohtmlWidget.h" },
		{ "ToolTip", "Gets or sets the Actor containing any LiveViewComponents." },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_Owner = { "Owner", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlWidget, Owner), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_Owner_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_Owner_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCohtmlWidget_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_URL,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bGammaCorrectedMaterial,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_InputPropagationBehaviour,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bReceiveInput,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_Filter,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_bEnableComplexCSSSupport,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_ScriptingReady,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_BindingsReleased,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_ReadyForBindings,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlWidget_Statics::NewProp_Owner,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCohtmlWidget_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCohtmlWidget>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCohtmlWidget_Statics::ClassParams = {
		&UCohtmlWidget::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UCohtmlWidget_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlWidget_Statics::PropPointers),
		0,
		0x00B000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UCohtmlWidget_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlWidget_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCohtmlWidget()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCohtmlWidget_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCohtmlWidget, 3215952930);
	template<> COHTMLPLUGIN_API UClass* StaticClass<UCohtmlWidget>()
	{
		return UCohtmlWidget::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCohtmlWidget(Z_Construct_UClass_UCohtmlWidget, &UCohtmlWidget::StaticClass, TEXT("/Script/CohtmlPlugin"), TEXT("UCohtmlWidget"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCohtmlWidget);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
