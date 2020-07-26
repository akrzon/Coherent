// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CohtmlPlugin/Classes/HummingbirdGameHUD.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHummingbirdGameHUD() {}
// Cross Module References
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_AHummingbirdGameHUD_NoRegister();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_AHummingbirdGameHUD();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_ACohtmlGameHUD();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin();
// End Cross Module References
	void AHummingbirdGameHUD::StaticRegisterNativesAHummingbirdGameHUD()
	{
	}
	UClass* Z_Construct_UClass_AHummingbirdGameHUD_NoRegister()
	{
		return AHummingbirdGameHUD::StaticClass();
	}
	struct Z_Construct_UClass_AHummingbirdGameHUD_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AHummingbirdGameHUD_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACohtmlGameHUD,
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AHummingbirdGameHUD_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Rendering Actor Input Replication" },
		{ "IncludePath", "HummingbirdGameHUD.h" },
		{ "IsBlueprintBase", "false" },
		{ "ModuleRelativePath", "Classes/HummingbirdGameHUD.h" },
		{ "NotBlueprintType", "true" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AHummingbirdGameHUD_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AHummingbirdGameHUD>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AHummingbirdGameHUD_Statics::ClassParams = {
		&AHummingbirdGameHUD::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_AHummingbirdGameHUD_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AHummingbirdGameHUD_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AHummingbirdGameHUD()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AHummingbirdGameHUD_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AHummingbirdGameHUD, 1089523793);
	template<> COHTMLPLUGIN_API UClass* StaticClass<AHummingbirdGameHUD>()
	{
		return AHummingbirdGameHUD::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AHummingbirdGameHUD(Z_Construct_UClass_AHummingbirdGameHUD, &AHummingbirdGameHUD::StaticClass, TEXT("/Script/CohtmlPlugin"), TEXT("AHummingbirdGameHUD"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AHummingbirdGameHUD);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
