// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CohtmlPlugin/Classes/CohtmlAssetReferencer.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCohtmlAssetReferencer() {}
// Cross Module References
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlAssetReferencer_NoRegister();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlAssetReferencer();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin();
// End Cross Module References
	void UCohtmlAssetReferencer::StaticRegisterNativesUCohtmlAssetReferencer()
	{
	}
	UClass* Z_Construct_UClass_UCohtmlAssetReferencer_NoRegister()
	{
		return UCohtmlAssetReferencer::StaticClass();
	}
	struct Z_Construct_UClass_UCohtmlAssetReferencer_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCohtmlAssetReferencer_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlAssetReferencer_Statics::Class_MetaDataParams[] = {
		{ "Comment", "// Helper class that statically references all assets used by the plugin uses internally for packaging.\n// Must be an entire class because it makes use of ConstructorHelpers::FObjectFinder\n// There's no need to instantiate this class, referencing the materials in the constructor is enough\n" },
		{ "DisplayName", "Prysm Asset Referencer" },
		{ "IncludePath", "CohtmlAssetReferencer.h" },
		{ "ModuleRelativePath", "Classes/CohtmlAssetReferencer.h" },
		{ "ToolTip", "Helper class that statically references all assets used by the plugin uses internally for packaging.\nMust be an entire class because it makes use of ConstructorHelpers::FObjectFinder\nThere's no need to instantiate this class, referencing the materials in the constructor is enough" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCohtmlAssetReferencer_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCohtmlAssetReferencer>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCohtmlAssetReferencer_Statics::ClassParams = {
		&UCohtmlAssetReferencer::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UCohtmlAssetReferencer_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlAssetReferencer_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCohtmlAssetReferencer()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCohtmlAssetReferencer_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCohtmlAssetReferencer, 2303940638);
	template<> COHTMLPLUGIN_API UClass* StaticClass<UCohtmlAssetReferencer>()
	{
		return UCohtmlAssetReferencer::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCohtmlAssetReferencer(Z_Construct_UClass_UCohtmlAssetReferencer, &UCohtmlAssetReferencer::StaticClass, TEXT("/Script/CohtmlPlugin"), TEXT("UCohtmlAssetReferencer"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCohtmlAssetReferencer);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
