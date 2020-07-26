// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CohtmlPlugin/Classes/HummingbirdHUD.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHummingbirdHUD() {}
// Cross Module References
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UHummingbirdHUD_NoRegister();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UHummingbirdHUD();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlHUD();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin();
// End Cross Module References
	void UHummingbirdHUD::StaticRegisterNativesUHummingbirdHUD()
	{
	}
	UClass* Z_Construct_UClass_UHummingbirdHUD_NoRegister()
	{
		return UHummingbirdHUD::StaticClass();
	}
	struct Z_Construct_UClass_UHummingbirdHUD_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UHummingbirdHUD_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UCohtmlHUD,
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHummingbirdHUD_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "HummingbirdHUD.h" },
		{ "ModuleRelativePath", "Classes/HummingbirdHUD.h" },
		{ "NotBlueprintType", "true" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UHummingbirdHUD_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHummingbirdHUD>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UHummingbirdHUD_Statics::ClassParams = {
		&UHummingbirdHUD::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x00A800A4u,
		METADATA_PARAMS(Z_Construct_UClass_UHummingbirdHUD_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UHummingbirdHUD_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UHummingbirdHUD()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UHummingbirdHUD_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UHummingbirdHUD, 3220052497);
	template<> COHTMLPLUGIN_API UClass* StaticClass<UHummingbirdHUD>()
	{
		return UHummingbirdHUD::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UHummingbirdHUD(Z_Construct_UClass_UHummingbirdHUD, &UHummingbirdHUD::StaticClass, TEXT("/Script/CohtmlPlugin"), TEXT("UHummingbirdHUD"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UHummingbirdHUD);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
