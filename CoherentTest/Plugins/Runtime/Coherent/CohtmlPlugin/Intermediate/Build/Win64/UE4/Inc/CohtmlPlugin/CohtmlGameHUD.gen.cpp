// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CohtmlPlugin/Classes/CohtmlGameHUD.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCohtmlGameHUD() {}
// Cross Module References
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_ACohtmlGameHUD_NoRegister();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_ACohtmlGameHUD();
	ENGINE_API UClass* Z_Construct_UClass_AHUD();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_ACohtmlGameHUD_SetupView();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlHUD_NoRegister();
// End Cross Module References
	void ACohtmlGameHUD::StaticRegisterNativesACohtmlGameHUD()
	{
		UClass* Class = ACohtmlGameHUD::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "SetupView", &ACohtmlGameHUD::execSetupView },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics
	{
		struct CohtmlGameHUD_eventSetupView_Parms
		{
			FString PageUrl;
			bool bEnableComplexCSSSupport;
			bool bDelayedUpdate;
		};
		static void NewProp_bDelayedUpdate_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bDelayedUpdate;
		static void NewProp_bEnableComplexCSSSupport_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bEnableComplexCSSSupport;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PageUrl_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_PageUrl;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::NewProp_bDelayedUpdate_SetBit(void* Obj)
	{
		((CohtmlGameHUD_eventSetupView_Parms*)Obj)->bDelayedUpdate = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::NewProp_bDelayedUpdate = { "bDelayedUpdate", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CohtmlGameHUD_eventSetupView_Parms), &Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::NewProp_bDelayedUpdate_SetBit, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::NewProp_bEnableComplexCSSSupport_SetBit(void* Obj)
	{
		((CohtmlGameHUD_eventSetupView_Parms*)Obj)->bEnableComplexCSSSupport = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::NewProp_bEnableComplexCSSSupport = { "bEnableComplexCSSSupport", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CohtmlGameHUD_eventSetupView_Parms), &Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::NewProp_bEnableComplexCSSSupport_SetBit, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::NewProp_PageUrl_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::NewProp_PageUrl = { "PageUrl", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlGameHUD_eventSetupView_Parms, PageUrl), METADATA_PARAMS(Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::NewProp_PageUrl_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::NewProp_PageUrl_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::NewProp_bDelayedUpdate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::NewProp_bEnableComplexCSSSupport,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::NewProp_PageUrl,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::Function_MetaDataParams[] = {
		{ "Category", "Prysm" },
		{ "CPP_Default_bDelayedUpdate", "false" },
		{ "CPP_Default_bEnableComplexCSSSupport", "true" },
		{ "DisplayName", "Setup View" },
		{ "ModuleRelativePath", "Classes/CohtmlGameHUD.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ACohtmlGameHUD, nullptr, "SetupView", nullptr, nullptr, sizeof(CohtmlGameHUD_eventSetupView_Parms), Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020403, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ACohtmlGameHUD_SetupView()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ACohtmlGameHUD_SetupView_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ACohtmlGameHUD_NoRegister()
	{
		return ACohtmlGameHUD::StaticClass();
	}
	struct Z_Construct_UClass_ACohtmlGameHUD_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CohtmlHUDInternal_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CohtmlHUDInternal;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CohtmlHUD_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CohtmlHUD;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ACohtmlGameHUD_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AHUD,
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ACohtmlGameHUD_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ACohtmlGameHUD_SetupView, "SetupView" }, // 85529911
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACohtmlGameHUD_Statics::Class_MetaDataParams[] = {
		{ "DisplayName", "Prysm GameHUD" },
		{ "HideCategories", "Rendering Actor Input Replication" },
		{ "IncludePath", "CohtmlGameHUD.h" },
		{ "ModuleRelativePath", "Classes/CohtmlGameHUD.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACohtmlGameHUD_Statics::NewProp_CohtmlHUDInternal_MetaData[] = {
		{ "Comment", "// After renaming the plugin BP's were broken, because their c-tor was\n// stomping the pointer of CohtmlHUD. The work around was to create another\n// pointer to CothmlHUD.\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Classes/CohtmlGameHUD.h" },
		{ "ToolTip", "After renaming the plugin BP's were broken, because their c-tor was\nstomping the pointer of CohtmlHUD. The work around was to create another\npointer to CothmlHUD." },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACohtmlGameHUD_Statics::NewProp_CohtmlHUDInternal = { "CohtmlHUDInternal", nullptr, (EPropertyFlags)0x0040000000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ACohtmlGameHUD, CohtmlHUDInternal), Z_Construct_UClass_UCohtmlHUD_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ACohtmlGameHUD_Statics::NewProp_CohtmlHUDInternal_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ACohtmlGameHUD_Statics::NewProp_CohtmlHUDInternal_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACohtmlGameHUD_Statics::NewProp_CohtmlHUD_MetaData[] = {
		{ "Category", "HUD" },
		{ "Comment", "// Instead of using this pointer directly, use GetCohtmlHUD() method.\n" },
		{ "DisplayName", "Prysm HUD" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Classes/CohtmlGameHUD.h" },
		{ "ToolTip", "Instead of using this pointer directly, use GetCohtmlHUD() method." },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACohtmlGameHUD_Statics::NewProp_CohtmlHUD = { "CohtmlHUD", nullptr, (EPropertyFlags)0x002008000008001c, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ACohtmlGameHUD, CohtmlHUD), Z_Construct_UClass_UCohtmlHUD_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ACohtmlGameHUD_Statics::NewProp_CohtmlHUD_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ACohtmlGameHUD_Statics::NewProp_CohtmlHUD_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ACohtmlGameHUD_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACohtmlGameHUD_Statics::NewProp_CohtmlHUDInternal,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACohtmlGameHUD_Statics::NewProp_CohtmlHUD,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ACohtmlGameHUD_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACohtmlGameHUD>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ACohtmlGameHUD_Statics::ClassParams = {
		&ACohtmlGameHUD::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ACohtmlGameHUD_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ACohtmlGameHUD_Statics::PropPointers),
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_ACohtmlGameHUD_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ACohtmlGameHUD_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ACohtmlGameHUD()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ACohtmlGameHUD_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ACohtmlGameHUD, 424866372);
	template<> COHTMLPLUGIN_API UClass* StaticClass<ACohtmlGameHUD>()
	{
		return ACohtmlGameHUD::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ACohtmlGameHUD(Z_Construct_UClass_ACohtmlGameHUD, &ACohtmlGameHUD::StaticClass, TEXT("/Script/CohtmlPlugin"), TEXT("ACohtmlGameHUD"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACohtmlGameHUD);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
