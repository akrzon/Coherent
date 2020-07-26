// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CohtmlPlugin/Classes/CohtmlViewInfo.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCohtmlViewInfo() {}
// Cross Module References
	COHTMLPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FCohtmlViewSettings();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin();
// End Cross Module References
class UScriptStruct* FCohtmlViewSettings::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern COHTMLPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FCohtmlViewSettings_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FCohtmlViewSettings, Z_Construct_UPackage__Script_CohtmlPlugin(), TEXT("CohtmlViewSettings"), sizeof(FCohtmlViewSettings), Get_Z_Construct_UScriptStruct_FCohtmlViewSettings_Hash());
	}
	return Singleton;
}
template<> COHTMLPLUGIN_API UScriptStruct* StaticStruct<FCohtmlViewSettings>()
{
	return FCohtmlViewSettings::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FCohtmlViewSettings(FCohtmlViewSettings::StaticStruct, TEXT("/Script/CohtmlPlugin"), TEXT("CohtmlViewSettings"), false, nullptr, nullptr);
static struct FScriptStruct_CohtmlPlugin_StaticRegisterNativesFCohtmlViewSettings
{
	FScriptStruct_CohtmlPlugin_StaticRegisterNativesFCohtmlViewSettings()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("CohtmlViewSettings")),new UScriptStruct::TCppStructOps<FCohtmlViewSettings>);
	}
} ScriptStruct_CohtmlPlugin_StaticRegisterNativesFCohtmlViewSettings;
	struct Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AnimationFrameDefer_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_AnimationFrameDefer;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IsTransparent_MetaData[];
#endif
		static void NewProp_IsTransparent_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_IsTransparent;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Height_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Height;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Width_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Width;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Classes/CohtmlViewInfo.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FCohtmlViewSettings>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_AnimationFrameDefer_MetaData[] = {
		{ "Category", "Prysm" },
		{ "Comment", "/// Sets the minimal frame time between invocations of requested animation\n/// frames in seconds. Decreasing the number will trigger animations more \n/// often but will consume more CPU. A good figure is around half the \n/// frame-rate of the application.\n" },
		{ "ModuleRelativePath", "Classes/CohtmlViewInfo.h" },
		{ "ToolTip", "Sets the minimal frame time between invocations of requested animation\nframes in seconds. Decreasing the number will trigger animations more\noften but will consume more CPU. A good figure is around half the\nframe-rate of the application." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_AnimationFrameDefer = { "AnimationFrameDefer", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCohtmlViewSettings, AnimationFrameDefer), METADATA_PARAMS(Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_AnimationFrameDefer_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_AnimationFrameDefer_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_IsTransparent_MetaData[] = {
		{ "Category", "Prysm" },
		{ "Comment", "/**\n\x09* Defines if a view is transparent or not. A transparent view can be have transparent parts that will\n\x09* be correctly blended with the client's surfaces. Non-transparent views are always implicitly composited\n\x09* as if on a white background. Don't use transparent views unless you have transparent parts in the page\n\x09* because non-transparent view are slightly faster.\n\x09* @note Do not blend non-transparent views.\n\x09*/" },
		{ "ModuleRelativePath", "Classes/CohtmlViewInfo.h" },
		{ "ToolTip", "Defines if a view is transparent or not. A transparent view can be have transparent parts that will\nbe correctly blended with the client's surfaces. Non-transparent views are always implicitly composited\nas if on a white background. Don't use transparent views unless you have transparent parts in the page\nbecause non-transparent view are slightly faster.\n@note Do not blend non-transparent views." },
	};
#endif
	void Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_IsTransparent_SetBit(void* Obj)
	{
		((FCohtmlViewSettings*)Obj)->IsTransparent = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_IsTransparent = { "IsTransparent", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FCohtmlViewSettings), &Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_IsTransparent_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_IsTransparent_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_IsTransparent_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_Height_MetaData[] = {
		{ "Category", "Prysm" },
		{ "Comment", "/** The Height of a View in pixels */" },
		{ "ModuleRelativePath", "Classes/CohtmlViewInfo.h" },
		{ "ToolTip", "The Height of a View in pixels" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_Height = { "Height", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCohtmlViewSettings, Height), METADATA_PARAMS(Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_Height_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_Height_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_Width_MetaData[] = {
		{ "Category", "Prysm" },
		{ "Comment", "/** The Width of a View in pixels */" },
		{ "ModuleRelativePath", "Classes/CohtmlViewInfo.h" },
		{ "ToolTip", "The Width of a View in pixels" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_Width = { "Width", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCohtmlViewSettings, Width), METADATA_PARAMS(Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_Width_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_Width_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_AnimationFrameDefer,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_IsTransparent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_Height,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::NewProp_Width,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
		nullptr,
		&NewStructOps,
		"CohtmlViewSettings",
		sizeof(FCohtmlViewSettings),
		alignof(FCohtmlViewSettings),
		Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FCohtmlViewSettings()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FCohtmlViewSettings_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_CohtmlPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("CohtmlViewSettings"), sizeof(FCohtmlViewSettings), Get_Z_Construct_UScriptStruct_FCohtmlViewSettings_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FCohtmlViewSettings_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FCohtmlViewSettings_Hash() { return 47572889U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
