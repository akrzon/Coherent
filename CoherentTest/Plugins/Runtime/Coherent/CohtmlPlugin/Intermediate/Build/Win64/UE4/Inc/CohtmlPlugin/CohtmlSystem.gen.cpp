// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CohtmlPlugin/Classes/CohtmlSystem.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCohtmlSystem() {}
// Cross Module References
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_ACohtmlSystem_NoRegister();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_ACohtmlSystem();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin();
// End Cross Module References
	void ACohtmlSystem::StaticRegisterNativesACohtmlSystem()
	{
	}
	UClass* Z_Construct_UClass_ACohtmlSystem_NoRegister()
	{
		return ACohtmlSystem::StaticClass();
	}
	struct Z_Construct_UClass_ACohtmlSystem_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ACohtmlSystem_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACohtmlSystem_Statics::Class_MetaDataParams[] = {
		{ "DisplayName", "Prysm System" },
		{ "IncludePath", "CohtmlSystem.h" },
		{ "ModuleRelativePath", "Classes/CohtmlSystem.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ACohtmlSystem_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACohtmlSystem>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ACohtmlSystem_Statics::ClassParams = {
		&ACohtmlSystem::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_ACohtmlSystem_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ACohtmlSystem_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ACohtmlSystem()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ACohtmlSystem_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ACohtmlSystem, 557142776);
	template<> COHTMLPLUGIN_API UClass* StaticClass<ACohtmlSystem>()
	{
		return ACohtmlSystem::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ACohtmlSystem(Z_Construct_UClass_ACohtmlSystem, &ACohtmlSystem::StaticClass, TEXT("/Script/CohtmlPlugin"), TEXT("ACohtmlSystem"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACohtmlSystem);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
