// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CohtmlPlugin/Classes/HummingbirdBaseComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHummingbirdBaseComponent() {}
// Cross Module References
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UHummingbirdBaseComponent_NoRegister();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UHummingbirdBaseComponent();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlBaseComponent();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin();
// End Cross Module References
	void UHummingbirdBaseComponent::StaticRegisterNativesUHummingbirdBaseComponent()
	{
	}
	UClass* Z_Construct_UClass_UHummingbirdBaseComponent_NoRegister()
	{
		return UHummingbirdBaseComponent::StaticClass();
	}
	struct Z_Construct_UClass_UHummingbirdBaseComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UHummingbirdBaseComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UCohtmlBaseComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHummingbirdBaseComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "HummingbirdBaseComponent.h" },
		{ "ModuleRelativePath", "Classes/HummingbirdBaseComponent.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UHummingbirdBaseComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHummingbirdBaseComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UHummingbirdBaseComponent_Statics::ClassParams = {
		&UHummingbirdBaseComponent::StaticClass,
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
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UHummingbirdBaseComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UHummingbirdBaseComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UHummingbirdBaseComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UHummingbirdBaseComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UHummingbirdBaseComponent, 1903469686);
	template<> COHTMLPLUGIN_API UClass* StaticClass<UHummingbirdBaseComponent>()
	{
		return UHummingbirdBaseComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UHummingbirdBaseComponent(Z_Construct_UClass_UHummingbirdBaseComponent, &UHummingbirdBaseComponent::StaticClass, TEXT("/Script/CohtmlPlugin"), TEXT("UHummingbirdBaseComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UHummingbirdBaseComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
