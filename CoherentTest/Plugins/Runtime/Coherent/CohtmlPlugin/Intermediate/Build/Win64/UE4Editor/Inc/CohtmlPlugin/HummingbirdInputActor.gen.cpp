// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CohtmlPlugin/Classes/HummingbirdInputActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHummingbirdInputActor() {}
// Cross Module References
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_AHummingbirdInputActor_NoRegister();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_AHummingbirdInputActor();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_ACohtmlInputActor();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin();
// End Cross Module References
	void AHummingbirdInputActor::StaticRegisterNativesAHummingbirdInputActor()
	{
	}
	UClass* Z_Construct_UClass_AHummingbirdInputActor_NoRegister()
	{
		return AHummingbirdInputActor::StaticClass();
	}
	struct Z_Construct_UClass_AHummingbirdInputActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AHummingbirdInputActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACohtmlInputActor,
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AHummingbirdInputActor_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "HummingbirdInputActor.h" },
		{ "ModuleRelativePath", "Classes/HummingbirdInputActor.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AHummingbirdInputActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AHummingbirdInputActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AHummingbirdInputActor_Statics::ClassParams = {
		&AHummingbirdInputActor::StaticClass,
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
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AHummingbirdInputActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AHummingbirdInputActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AHummingbirdInputActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AHummingbirdInputActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AHummingbirdInputActor, 1712530263);
	template<> COHTMLPLUGIN_API UClass* StaticClass<AHummingbirdInputActor>()
	{
		return AHummingbirdInputActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AHummingbirdInputActor(Z_Construct_UClass_AHummingbirdInputActor, &AHummingbirdInputActor::StaticClass, TEXT("/Script/CohtmlPlugin"), TEXT("AHummingbirdInputActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AHummingbirdInputActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
