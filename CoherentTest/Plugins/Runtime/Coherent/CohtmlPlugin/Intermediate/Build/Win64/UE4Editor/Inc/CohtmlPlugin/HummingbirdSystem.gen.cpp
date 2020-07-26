// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CohtmlPlugin/Classes/HummingbirdSystem.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHummingbirdSystem() {}
// Cross Module References
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_AHummingbirdSystem_NoRegister();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_AHummingbirdSystem();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_ACohtmlSystem();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin();
// End Cross Module References
	void AHummingbirdSystem::StaticRegisterNativesAHummingbirdSystem()
	{
	}
	UClass* Z_Construct_UClass_AHummingbirdSystem_NoRegister()
	{
		return AHummingbirdSystem::StaticClass();
	}
	struct Z_Construct_UClass_AHummingbirdSystem_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AHummingbirdSystem_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACohtmlSystem,
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AHummingbirdSystem_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "HummingbirdSystem.h" },
		{ "ModuleRelativePath", "Classes/HummingbirdSystem.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AHummingbirdSystem_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AHummingbirdSystem>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AHummingbirdSystem_Statics::ClassParams = {
		&AHummingbirdSystem::StaticClass,
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
		0x008800A4u,
		METADATA_PARAMS(Z_Construct_UClass_AHummingbirdSystem_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AHummingbirdSystem_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AHummingbirdSystem()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AHummingbirdSystem_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AHummingbirdSystem, 206953400);
	template<> COHTMLPLUGIN_API UClass* StaticClass<AHummingbirdSystem>()
	{
		return AHummingbirdSystem::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AHummingbirdSystem(Z_Construct_UClass_AHummingbirdSystem, &AHummingbirdSystem::StaticClass, TEXT("/Script/CohtmlPlugin"), TEXT("AHummingbirdSystem"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AHummingbirdSystem);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
