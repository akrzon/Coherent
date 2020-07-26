// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CohtmlPlugin/Classes/CohtmlAtlasMappingData.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCohtmlAtlasMappingData() {}
// Cross Module References
	COHTMLPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FTextureAtlasMetaData();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlTextureAtlasDetails_NoRegister();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlAtlasContainedTextures_NoRegister();
	COHTMLPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FTextureAtlasMappingInfo();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlAtlasContainedTextures();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlTextureAtlasDetails();
// End Cross Module References
class UScriptStruct* FTextureAtlasMetaData::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern COHTMLPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FTextureAtlasMetaData_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FTextureAtlasMetaData, Z_Construct_UPackage__Script_CohtmlPlugin(), TEXT("TextureAtlasMetaData"), sizeof(FTextureAtlasMetaData), Get_Z_Construct_UScriptStruct_FTextureAtlasMetaData_Hash());
	}
	return Singleton;
}
template<> COHTMLPLUGIN_API UScriptStruct* StaticStruct<FTextureAtlasMetaData>()
{
	return FTextureAtlasMetaData::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FTextureAtlasMetaData(FTextureAtlasMetaData::StaticStruct, TEXT("/Script/CohtmlPlugin"), TEXT("TextureAtlasMetaData"), false, nullptr, nullptr);
static struct FScriptStruct_CohtmlPlugin_StaticRegisterNativesFTextureAtlasMetaData
{
	FScriptStruct_CohtmlPlugin_StaticRegisterNativesFTextureAtlasMetaData()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("TextureAtlasMetaData")),new UScriptStruct::TCppStructOps<FTextureAtlasMetaData>);
	}
} ScriptStruct_CohtmlPlugin_StaticRegisterNativesFTextureAtlasMetaData;
	struct Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AtlasDetails_MetaData[];
#endif
		static const UE4CodeGen_Private::FMapPropertyParams NewProp_AtlasDetails;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AtlasDetails_Key_KeyProp;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_AtlasDetails_ValueProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AtlasContainedTextures_MetaData[];
#endif
		static const UE4CodeGen_Private::FMapPropertyParams NewProp_AtlasContainedTextures;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AtlasContainedTextures_Key_KeyProp;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_AtlasContainedTextures_ValueProp;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Classes/CohtmlAtlasMappingData.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTextureAtlasMetaData>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::NewProp_AtlasDetails_MetaData[] = {
		{ "Comment", "// A UCohtmlTextureAtlasDetails object is passed to PropertyEditor::CreateDetailsView\n// to create a widget containing the atlas information (size, pixel format, size thresholds).\n" },
		{ "ModuleRelativePath", "Classes/CohtmlAtlasMappingData.h" },
		{ "ToolTip", "A UCohtmlTextureAtlasDetails object is passed to PropertyEditor::CreateDetailsView\nto create a widget containing the atlas information (size, pixel format, size thresholds)." },
	};
#endif
	const UE4CodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::NewProp_AtlasDetails = { "AtlasDetails", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FTextureAtlasMetaData, AtlasDetails), METADATA_PARAMS(Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::NewProp_AtlasDetails_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::NewProp_AtlasDetails_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::NewProp_AtlasDetails_Key_KeyProp = { "AtlasDetails_Key", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::NewProp_AtlasDetails_ValueProp = { "AtlasDetails", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, Z_Construct_UClass_UCohtmlTextureAtlasDetails_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::NewProp_AtlasContainedTextures_MetaData[] = {
		{ "Comment", "// A UCohtmlAtlasContainedTextures object is passed to PropertyEditor::CreateDetailsView\n// to create a widget containing the textures contained in a given atlas.\n" },
		{ "ModuleRelativePath", "Classes/CohtmlAtlasMappingData.h" },
		{ "ToolTip", "A UCohtmlAtlasContainedTextures object is passed to PropertyEditor::CreateDetailsView\nto create a widget containing the textures contained in a given atlas." },
	};
#endif
	const UE4CodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::NewProp_AtlasContainedTextures = { "AtlasContainedTextures", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FTextureAtlasMetaData, AtlasContainedTextures), METADATA_PARAMS(Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::NewProp_AtlasContainedTextures_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::NewProp_AtlasContainedTextures_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::NewProp_AtlasContainedTextures_Key_KeyProp = { "AtlasContainedTextures_Key", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::NewProp_AtlasContainedTextures_ValueProp = { "AtlasContainedTextures", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, Z_Construct_UClass_UCohtmlAtlasContainedTextures_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::NewProp_AtlasDetails,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::NewProp_AtlasDetails_Key_KeyProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::NewProp_AtlasDetails_ValueProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::NewProp_AtlasContainedTextures,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::NewProp_AtlasContainedTextures_Key_KeyProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::NewProp_AtlasContainedTextures_ValueProp,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
		nullptr,
		&NewStructOps,
		"TextureAtlasMetaData",
		sizeof(FTextureAtlasMetaData),
		alignof(FTextureAtlasMetaData),
		Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FTextureAtlasMetaData()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FTextureAtlasMetaData_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_CohtmlPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("TextureAtlasMetaData"), sizeof(FTextureAtlasMetaData), Get_Z_Construct_UScriptStruct_FTextureAtlasMetaData_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FTextureAtlasMetaData_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FTextureAtlasMetaData_Hash() { return 137081004U; }
class UScriptStruct* FTextureAtlasMappingInfo::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern COHTMLPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FTextureAtlasMappingInfo, Z_Construct_UPackage__Script_CohtmlPlugin(), TEXT("TextureAtlasMappingInfo"), sizeof(FTextureAtlasMappingInfo), Get_Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Hash());
	}
	return Singleton;
}
template<> COHTMLPLUGIN_API UScriptStruct* StaticStruct<FTextureAtlasMappingInfo>()
{
	return FTextureAtlasMappingInfo::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FTextureAtlasMappingInfo(FTextureAtlasMappingInfo::StaticStruct, TEXT("/Script/CohtmlPlugin"), TEXT("TextureAtlasMappingInfo"), false, nullptr, nullptr);
static struct FScriptStruct_CohtmlPlugin_StaticRegisterNativesFTextureAtlasMappingInfo
{
	FScriptStruct_CohtmlPlugin_StaticRegisterNativesFTextureAtlasMappingInfo()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("TextureAtlasMappingInfo")),new UScriptStruct::TCppStructOps<FTextureAtlasMappingInfo>);
	}
} ScriptStruct_CohtmlPlugin_StaticRegisterNativesFTextureAtlasMappingInfo;
	struct Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OriginY_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_OriginY;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OriginX_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_OriginX;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Height_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Height;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Width_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Width;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AtlasPath_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AtlasPath;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Classes/CohtmlAtlasMappingData.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTextureAtlasMappingInfo>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_OriginY_MetaData[] = {
		{ "ModuleRelativePath", "Classes/CohtmlAtlasMappingData.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_OriginY = { "OriginY", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FTextureAtlasMappingInfo, OriginY), METADATA_PARAMS(Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_OriginY_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_OriginY_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_OriginX_MetaData[] = {
		{ "ModuleRelativePath", "Classes/CohtmlAtlasMappingData.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_OriginX = { "OriginX", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FTextureAtlasMappingInfo, OriginX), METADATA_PARAMS(Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_OriginX_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_OriginX_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_Height_MetaData[] = {
		{ "ModuleRelativePath", "Classes/CohtmlAtlasMappingData.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_Height = { "Height", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FTextureAtlasMappingInfo, Height), METADATA_PARAMS(Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_Height_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_Height_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_Width_MetaData[] = {
		{ "ModuleRelativePath", "Classes/CohtmlAtlasMappingData.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_Width = { "Width", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FTextureAtlasMappingInfo, Width), METADATA_PARAMS(Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_Width_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_Width_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_AtlasPath_MetaData[] = {
		{ "ModuleRelativePath", "Classes/CohtmlAtlasMappingData.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_AtlasPath = { "AtlasPath", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FTextureAtlasMappingInfo, AtlasPath), METADATA_PARAMS(Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_AtlasPath_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_AtlasPath_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_OriginY,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_OriginX,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_Height,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_Width,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::NewProp_AtlasPath,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
		nullptr,
		&NewStructOps,
		"TextureAtlasMappingInfo",
		sizeof(FTextureAtlasMappingInfo),
		alignof(FTextureAtlasMappingInfo),
		Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FTextureAtlasMappingInfo()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_CohtmlPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("TextureAtlasMappingInfo"), sizeof(FTextureAtlasMappingInfo), Get_Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FTextureAtlasMappingInfo_Hash() { return 2647975244U; }
	void UCohtmlAtlasContainedTextures::StaticRegisterNativesUCohtmlAtlasContainedTextures()
	{
	}
	UClass* Z_Construct_UClass_UCohtmlAtlasContainedTextures_NoRegister()
	{
		return UCohtmlAtlasContainedTextures::StaticClass();
	}
	struct Z_Construct_UClass_UCohtmlAtlasContainedTextures_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Textures_MetaData[];
#endif
		static const UE4CodeGen_Private::FSetPropertyParams NewProp_Textures;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Textures_ElementProp;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCohtmlAtlasContainedTextures_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlAtlasContainedTextures_Statics::Class_MetaDataParams[] = {
		{ "DisplayName", "Prysm Atlas Contained Textures" },
		{ "IncludePath", "CohtmlAtlasMappingData.h" },
		{ "ModuleRelativePath", "Classes/CohtmlAtlasMappingData.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlAtlasContainedTextures_Statics::NewProp_Textures_MetaData[] = {
		{ "Category", "Textures" },
		{ "ModuleRelativePath", "Classes/CohtmlAtlasMappingData.h" },
	};
#endif
	const UE4CodeGen_Private::FSetPropertyParams Z_Construct_UClass_UCohtmlAtlasContainedTextures_Statics::NewProp_Textures = { "Textures", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlAtlasContainedTextures, Textures), METADATA_PARAMS(Z_Construct_UClass_UCohtmlAtlasContainedTextures_Statics::NewProp_Textures_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlAtlasContainedTextures_Statics::NewProp_Textures_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCohtmlAtlasContainedTextures_Statics::NewProp_Textures_ElementProp = { "Textures", nullptr, (EPropertyFlags)0x0000000000000001, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCohtmlAtlasContainedTextures_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlAtlasContainedTextures_Statics::NewProp_Textures,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlAtlasContainedTextures_Statics::NewProp_Textures_ElementProp,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCohtmlAtlasContainedTextures_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCohtmlAtlasContainedTextures>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCohtmlAtlasContainedTextures_Statics::ClassParams = {
		&UCohtmlAtlasContainedTextures::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UCohtmlAtlasContainedTextures_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlAtlasContainedTextures_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UCohtmlAtlasContainedTextures_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlAtlasContainedTextures_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCohtmlAtlasContainedTextures()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCohtmlAtlasContainedTextures_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCohtmlAtlasContainedTextures, 1337499551);
	template<> COHTMLPLUGIN_API UClass* StaticClass<UCohtmlAtlasContainedTextures>()
	{
		return UCohtmlAtlasContainedTextures::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCohtmlAtlasContainedTextures(Z_Construct_UClass_UCohtmlAtlasContainedTextures, &UCohtmlAtlasContainedTextures::StaticClass, TEXT("/Script/CohtmlPlugin"), TEXT("UCohtmlAtlasContainedTextures"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCohtmlAtlasContainedTextures);
	void UCohtmlTextureAtlasDetails::StaticRegisterNativesUCohtmlTextureAtlasDetails()
	{
	}
	UClass* Z_Construct_UClass_UCohtmlTextureAtlasDetails_NoRegister()
	{
		return UCohtmlTextureAtlasDetails::StaticClass();
	}
	struct Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaxTextureHeight_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_MaxTextureHeight;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaxTextureWidth_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_MaxTextureWidth;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaxAtlasHeight_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_MaxAtlasHeight;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaxAtlasWidth_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_MaxAtlasWidth;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PixelFormat_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_PixelFormat;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Height_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Height;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Width_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Width;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AtlasPath_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AtlasPath;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::Class_MetaDataParams[] = {
		{ "DisplayName", "Prysm Texture Atlas Details" },
		{ "IncludePath", "CohtmlAtlasMappingData.h" },
		{ "ModuleRelativePath", "Classes/CohtmlAtlasMappingData.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_MaxTextureHeight_MetaData[] = {
		{ "Category", "AtlasThresholds" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Classes/CohtmlAtlasMappingData.h" },
		{ "ToolTip", "The maximum allowed height for a texture contained in the atlas" },
		{ "UIMax", "4096" },
		{ "UIMin", "0" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_MaxTextureHeight = { "MaxTextureHeight", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlTextureAtlasDetails, MaxTextureHeight), METADATA_PARAMS(Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_MaxTextureHeight_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_MaxTextureHeight_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_MaxTextureWidth_MetaData[] = {
		{ "Category", "AtlasThresholds" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Classes/CohtmlAtlasMappingData.h" },
		{ "ToolTip", "The maximum allowed width for a texture contained in the atlas" },
		{ "UIMax", "4096" },
		{ "UIMin", "0" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_MaxTextureWidth = { "MaxTextureWidth", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlTextureAtlasDetails, MaxTextureWidth), METADATA_PARAMS(Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_MaxTextureWidth_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_MaxTextureWidth_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_MaxAtlasHeight_MetaData[] = {
		{ "Category", "AtlasThresholds" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Classes/CohtmlAtlasMappingData.h" },
		{ "ToolTip", "The maximum allowed height of the texture atlas" },
		{ "UIMax", "4096" },
		{ "UIMin", "0" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_MaxAtlasHeight = { "MaxAtlasHeight", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlTextureAtlasDetails, MaxAtlasHeight), METADATA_PARAMS(Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_MaxAtlasHeight_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_MaxAtlasHeight_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_MaxAtlasWidth_MetaData[] = {
		{ "Category", "AtlasThresholds" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Classes/CohtmlAtlasMappingData.h" },
		{ "ToolTip", "The maximum allowed width of the texture atlas" },
		{ "UIMax", "4096" },
		{ "UIMin", "0" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_MaxAtlasWidth = { "MaxAtlasWidth", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlTextureAtlasDetails, MaxAtlasWidth), METADATA_PARAMS(Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_MaxAtlasWidth_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_MaxAtlasWidth_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_PixelFormat_MetaData[] = {
		{ "Category", "AtlasInfo" },
		{ "ModuleRelativePath", "Classes/CohtmlAtlasMappingData.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_PixelFormat = { "PixelFormat", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlTextureAtlasDetails, PixelFormat), METADATA_PARAMS(Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_PixelFormat_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_PixelFormat_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_Height_MetaData[] = {
		{ "Category", "AtlasInfo" },
		{ "ModuleRelativePath", "Classes/CohtmlAtlasMappingData.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_Height = { "Height", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlTextureAtlasDetails, Height), METADATA_PARAMS(Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_Height_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_Height_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_Width_MetaData[] = {
		{ "Category", "AtlasInfo" },
		{ "ModuleRelativePath", "Classes/CohtmlAtlasMappingData.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_Width = { "Width", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlTextureAtlasDetails, Width), METADATA_PARAMS(Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_Width_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_Width_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_AtlasPath_MetaData[] = {
		{ "Category", "AtlasInfo" },
		{ "ModuleRelativePath", "Classes/CohtmlAtlasMappingData.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_AtlasPath = { "AtlasPath", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlTextureAtlasDetails, AtlasPath), METADATA_PARAMS(Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_AtlasPath_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_AtlasPath_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_MaxTextureHeight,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_MaxTextureWidth,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_MaxAtlasHeight,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_MaxAtlasWidth,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_PixelFormat,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_Height,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_Width,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::NewProp_AtlasPath,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCohtmlTextureAtlasDetails>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::ClassParams = {
		&UCohtmlTextureAtlasDetails::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCohtmlTextureAtlasDetails()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCohtmlTextureAtlasDetails_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCohtmlTextureAtlasDetails, 515091283);
	template<> COHTMLPLUGIN_API UClass* StaticClass<UCohtmlTextureAtlasDetails>()
	{
		return UCohtmlTextureAtlasDetails::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCohtmlTextureAtlasDetails(Z_Construct_UClass_UCohtmlTextureAtlasDetails, &UCohtmlTextureAtlasDetails::StaticClass, TEXT("/Script/CohtmlPlugin"), TEXT("UCohtmlTextureAtlasDetails"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCohtmlTextureAtlasDetails);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
