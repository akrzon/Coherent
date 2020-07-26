// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CoherentRenderingPlugin/Public/CohTexture.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCohTexture() {}
// Cross Module References
	COHERENTRENDERINGPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FCohTextureUserWrapData();
	UPackage* Z_Construct_UPackage__Script_CoherentRenderingPlugin();
	ENGINE_API UClass* Z_Construct_UClass_UTexture_NoRegister();
// End Cross Module References
class UScriptStruct* FCohTextureUserWrapData::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern COHERENTRENDERINGPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FCohTextureUserWrapData_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FCohTextureUserWrapData, Z_Construct_UPackage__Script_CoherentRenderingPlugin(), TEXT("CohTextureUserWrapData"), sizeof(FCohTextureUserWrapData), Get_Z_Construct_UScriptStruct_FCohTextureUserWrapData_Hash());
	}
	return Singleton;
}
template<> COHERENTRENDERINGPLUGIN_API UScriptStruct* StaticStruct<FCohTextureUserWrapData>()
{
	return FCohTextureUserWrapData::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FCohTextureUserWrapData(FCohTextureUserWrapData::StaticStruct, TEXT("/Script/CoherentRenderingPlugin"), TEXT("CohTextureUserWrapData"), false, nullptr, nullptr);
static struct FScriptStruct_CoherentRenderingPlugin_StaticRegisterNativesFCohTextureUserWrapData
{
	FScriptStruct_CoherentRenderingPlugin_StaticRegisterNativesFCohTextureUserWrapData()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("CohTextureUserWrapData")),new UScriptStruct::TCppStructOps<FCohTextureUserWrapData>);
	}
} ScriptStruct_CoherentRenderingPlugin_StaticRegisterNativesFCohTextureUserWrapData;
	struct Z_Construct_UScriptStruct_FCohTextureUserWrapData_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Texture_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Texture;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCohTextureUserWrapData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "BlueprintType", "true" },
		{ "Comment", "// Uncomment this to start logging texture descriptions\n//#define COHERENT_LOG_TEXTURE_DESC\n" },
		{ "ModuleRelativePath", "Public/CohTexture.h" },
		{ "ToolTip", "Uncomment this to start logging texture descriptions\n#define COHERENT_LOG_TEXTURE_DESC" },
	};
#endif
	void* Z_Construct_UScriptStruct_FCohTextureUserWrapData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FCohTextureUserWrapData>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCohTextureUserWrapData_Statics::NewProp_Texture_MetaData[] = {
		{ "ModuleRelativePath", "Public/CohTexture.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FCohTextureUserWrapData_Statics::NewProp_Texture = { "Texture", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCohTextureUserWrapData, Texture), Z_Construct_UClass_UTexture_NoRegister, METADATA_PARAMS(Z_Construct_UScriptStruct_FCohTextureUserWrapData_Statics::NewProp_Texture_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCohTextureUserWrapData_Statics::NewProp_Texture_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FCohTextureUserWrapData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCohTextureUserWrapData_Statics::NewProp_Texture,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FCohTextureUserWrapData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_CoherentRenderingPlugin,
		nullptr,
		&NewStructOps,
		"CohTextureUserWrapData",
		sizeof(FCohTextureUserWrapData),
		alignof(FCohTextureUserWrapData),
		Z_Construct_UScriptStruct_FCohTextureUserWrapData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCohTextureUserWrapData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FCohTextureUserWrapData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCohTextureUserWrapData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FCohTextureUserWrapData()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FCohTextureUserWrapData_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_CoherentRenderingPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("CohTextureUserWrapData"), sizeof(FCohTextureUserWrapData), Get_Z_Construct_UScriptStruct_FCohTextureUserWrapData_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FCohTextureUserWrapData_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FCohTextureUserWrapData_Hash() { return 4240260040U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
