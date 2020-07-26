// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCohtmlPlugin_init() {}
	COHTMLPLUGIN_API UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlReadyForBindingsSignature__DelegateSignature();
	COHTMLPLUGIN_API UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlBindingsReleasedSignature__DelegateSignature();
	COHTMLPLUGIN_API UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlScriptingReady__DelegateSignature();
	COHTMLPLUGIN_API UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlOnLiveViewSizeRequest__DelegateSignature();
	COHTMLPLUGIN_API UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonDown__DelegateSignature();
	COHTMLPLUGIN_API UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonUp__DelegateSignature();
	COHTMLPLUGIN_API UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyDown__DelegateSignature();
	COHTMLPLUGIN_API UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyUp__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin()
	{
		static UPackage* ReturnPackage = nullptr;
		if (!ReturnPackage)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlReadyForBindingsSignature__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlBindingsReleasedSignature__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlScriptingReady__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlOnLiveViewSizeRequest__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonDown__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonUp__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyDown__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyUp__DelegateSignature,
			};
			static const UE4CodeGen_Private::FPackageParams PackageParams = {
				"/Script/CohtmlPlugin",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0xBDE43215,
				0xA6AF62E3,
				METADATA_PARAMS(nullptr, 0)
			};
			UE4CodeGen_Private::ConstructUPackage(ReturnPackage, PackageParams);
		}
		return ReturnPackage;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
