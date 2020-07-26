// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CohtmlPlugin/Classes/HummingbirdComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHummingbirdComponent() {}
// Cross Module References
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UHummingbirdComponent_NoRegister();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UHummingbirdComponent();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlComponent();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin();
// End Cross Module References
	void UHummingbirdComponent::StaticRegisterNativesUHummingbirdComponent()
	{
	}
	UClass* Z_Construct_UClass_UHummingbirdComponent_NoRegister()
	{
		return UHummingbirdComponent::StaticClass();
	}
	struct Z_Construct_UClass_UHummingbirdComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UHummingbirdComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UCohtmlComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHummingbirdComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "UI" },
		{ "HideCategories", "Object Object" },
		{ "IncludePath", "HummingbirdComponent.h" },
		{ "ModuleRelativePath", "Classes/HummingbirdComponent.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UHummingbirdComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHummingbirdComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UHummingbirdComponent_Statics::ClassParams = {
		&UHummingbirdComponent::StaticClass,
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
		0x00A810A4u,
		METADATA_PARAMS(Z_Construct_UClass_UHummingbirdComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UHummingbirdComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UHummingbirdComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UHummingbirdComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UHummingbirdComponent, 3505379643);
	template<> COHTMLPLUGIN_API UClass* StaticClass<UHummingbirdComponent>()
	{
		return UHummingbirdComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UHummingbirdComponent(Z_Construct_UClass_UHummingbirdComponent, &UHummingbirdComponent::StaticClass, TEXT("/Script/CohtmlPlugin"), TEXT("UHummingbirdComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UHummingbirdComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
