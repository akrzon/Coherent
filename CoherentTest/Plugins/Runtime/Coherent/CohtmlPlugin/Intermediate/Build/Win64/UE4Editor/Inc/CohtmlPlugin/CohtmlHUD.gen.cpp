// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CohtmlPlugin/Classes/CohtmlHUD.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCohtmlHUD() {}
// Cross Module References
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlHUD_NoRegister();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlHUD();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlBaseComponent();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin();
	ENGINE_API UClass* Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UMaterial_NoRegister();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FSoftObjectPath();
// End Cross Module References
	void UCohtmlHUD::StaticRegisterNativesUCohtmlHUD()
	{
	}
	UClass* Z_Construct_UClass_UCohtmlHUD_NoRegister()
	{
		return UCohtmlHUD::StaticClass();
	}
	struct Z_Construct_UClass_UCohtmlHUD_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HUDMaterialInstance_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_HUDMaterialInstance;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HUDMaterial_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_HUDMaterial;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HUDMaterialName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_HUDMaterialName;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCohtmlHUD_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UCohtmlBaseComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlHUD_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "DisplayName", "Prysm HUD" },
		{ "IncludePath", "CohtmlHUD.h" },
		{ "ModuleRelativePath", "Classes/CohtmlHUD.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlHUD_Statics::NewProp_HUDMaterialInstance_MetaData[] = {
		{ "ModuleRelativePath", "Classes/CohtmlHUD.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCohtmlHUD_Statics::NewProp_HUDMaterialInstance = { "HUDMaterialInstance", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlHUD, HUDMaterialInstance), Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UCohtmlHUD_Statics::NewProp_HUDMaterialInstance_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlHUD_Statics::NewProp_HUDMaterialInstance_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlHUD_Statics::NewProp_HUDMaterial_MetaData[] = {
		{ "ModuleRelativePath", "Classes/CohtmlHUD.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCohtmlHUD_Statics::NewProp_HUDMaterial = { "HUDMaterial", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlHUD, HUDMaterial), Z_Construct_UClass_UMaterial_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UCohtmlHUD_Statics::NewProp_HUDMaterial_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlHUD_Statics::NewProp_HUDMaterial_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlHUD_Statics::NewProp_HUDMaterialName_MetaData[] = {
		{ "ModuleRelativePath", "Classes/CohtmlHUD.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCohtmlHUD_Statics::NewProp_HUDMaterialName = { "HUDMaterialName", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlHUD, HUDMaterialName), Z_Construct_UScriptStruct_FSoftObjectPath, METADATA_PARAMS(Z_Construct_UClass_UCohtmlHUD_Statics::NewProp_HUDMaterialName_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlHUD_Statics::NewProp_HUDMaterialName_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCohtmlHUD_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlHUD_Statics::NewProp_HUDMaterialInstance,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlHUD_Statics::NewProp_HUDMaterial,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlHUD_Statics::NewProp_HUDMaterialName,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCohtmlHUD_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCohtmlHUD>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCohtmlHUD_Statics::ClassParams = {
		&UCohtmlHUD::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UCohtmlHUD_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlHUD_Statics::PropPointers),
		0,
		0x00A800A4u,
		METADATA_PARAMS(Z_Construct_UClass_UCohtmlHUD_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlHUD_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCohtmlHUD()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCohtmlHUD_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCohtmlHUD, 2819423677);
	template<> COHTMLPLUGIN_API UClass* StaticClass<UCohtmlHUD>()
	{
		return UCohtmlHUD::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCohtmlHUD(Z_Construct_UClass_UCohtmlHUD, &UCohtmlHUD::StaticClass, TEXT("/Script/CohtmlPlugin"), TEXT("UCohtmlHUD"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCohtmlHUD);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
