// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CohtmlPlugin/Classes/CohtmlComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCohtmlComponent() {}
// Cross Module References
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlComponent_NoRegister();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlComponent();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlBaseComponent();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin();
// End Cross Module References
	void UCohtmlComponent::StaticRegisterNativesUCohtmlComponent()
	{
	}
	UClass* Z_Construct_UClass_UCohtmlComponent_NoRegister()
	{
		return UCohtmlComponent::StaticClass();
	}
	struct Z_Construct_UClass_UCohtmlComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ManualTexture_MetaData[];
#endif
		static void NewProp_ManualTexture_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ManualTexture;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Height_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Height;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Width_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Width;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_URL_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_URL;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCohtmlComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UCohtmlBaseComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "UI" },
		{ "DisplayName", "Prysm Component" },
		{ "HideCategories", "Object" },
		{ "IncludePath", "CohtmlComponent.h" },
		{ "ModuleRelativePath", "Classes/CohtmlComponent.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_ManualTexture_MetaData[] = {
		{ "Category", "View" },
		{ "ModuleRelativePath", "Classes/CohtmlComponent.h" },
	};
#endif
	void Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_ManualTexture_SetBit(void* Obj)
	{
		((UCohtmlComponent*)Obj)->ManualTexture = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_ManualTexture = { "ManualTexture", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UCohtmlComponent), &Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_ManualTexture_SetBit, METADATA_PARAMS(Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_ManualTexture_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_ManualTexture_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_Height_MetaData[] = {
		{ "Category", "View" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Classes/CohtmlComponent.h" },
		{ "UIMax", "4096" },
		{ "UIMin", "0" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_Height = { "Height", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlComponent, Height), METADATA_PARAMS(Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_Height_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_Height_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_Width_MetaData[] = {
		{ "Category", "View" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Classes/CohtmlComponent.h" },
		{ "UIMax", "4096" },
		{ "UIMin", "0" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_Width = { "Width", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlComponent, Width), METADATA_PARAMS(Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_Width_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_Width_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_URL_MetaData[] = {
		{ "Category", "View" },
		{ "Comment", "/** The URL to load when the View is created */" },
		{ "ModuleRelativePath", "Classes/CohtmlComponent.h" },
		{ "ToolTip", "The URL to load when the View is created" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_URL = { "URL", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlComponent, URL), METADATA_PARAMS(Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_URL_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_URL_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCohtmlComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_ManualTexture,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_Height,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_Width,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlComponent_Statics::NewProp_URL,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCohtmlComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCohtmlComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCohtmlComponent_Statics::ClassParams = {
		&UCohtmlComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UCohtmlComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlComponent_Statics::PropPointers),
		0,
		0x00A810A4u,
		METADATA_PARAMS(Z_Construct_UClass_UCohtmlComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCohtmlComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCohtmlComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCohtmlComponent, 152961923);
	template<> COHTMLPLUGIN_API UClass* StaticClass<UCohtmlComponent>()
	{
		return UCohtmlComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCohtmlComponent(Z_Construct_UClass_UCohtmlComponent, &UCohtmlComponent::StaticClass, TEXT("/Script/CohtmlPlugin"), TEXT("UCohtmlComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCohtmlComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
