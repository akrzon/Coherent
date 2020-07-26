// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CohtmlPlugin/Classes/SCohtmlInputForward.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSCohtmlInputForward() {}
// Cross Module References
	COHTMLPLUGIN_API UEnum* Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputPropagationBehaviour();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin();
	COHTMLPLUGIN_API UEnum* Z_Construct_UEnum_CohtmlPlugin_ECohtmlGamepadBehaviourOnFocusLost();
	COHTMLPLUGIN_API UEnum* Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputWidgetLineTraceMode();
	COHTMLPLUGIN_API UEnum* Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputWidgetRaycastQuality();
// End Cross Module References
	static UEnum* ECohtmlInputPropagationBehaviour_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputPropagationBehaviour, Z_Construct_UPackage__Script_CohtmlPlugin(), TEXT("ECohtmlInputPropagationBehaviour"));
		}
		return Singleton;
	}
	template<> COHTMLPLUGIN_API UEnum* StaticEnum<ECohtmlInputPropagationBehaviour::Type>()
	{
		return ECohtmlInputPropagationBehaviour_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ECohtmlInputPropagationBehaviour(ECohtmlInputPropagationBehaviour_StaticEnum, TEXT("/Script/CohtmlPlugin"), TEXT("ECohtmlInputPropagationBehaviour"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputPropagationBehaviour_Hash() { return 2714903499U; }
	UEnum* Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputPropagationBehaviour()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_CohtmlPlugin();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ECohtmlInputPropagationBehaviour"), 0, Get_Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputPropagationBehaviour_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ECohtmlInputPropagationBehaviour::None", (int64)ECohtmlInputPropagationBehaviour::None },
				{ "ECohtmlInputPropagationBehaviour::Keyboard", (int64)ECohtmlInputPropagationBehaviour::Keyboard },
				{ "ECohtmlInputPropagationBehaviour::Joystick", (int64)ECohtmlInputPropagationBehaviour::Joystick },
				{ "ECohtmlInputPropagationBehaviour::KeyboardAndJoystick", (int64)ECohtmlInputPropagationBehaviour::KeyboardAndJoystick },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "DisplayName", "Prysm Input Propagation Behaviour" },
				{ "Joystick.Name", "ECohtmlInputPropagationBehaviour::Joystick" },
				{ "Keyboard.Name", "ECohtmlInputPropagationBehaviour::Keyboard" },
				{ "KeyboardAndJoystick.Name", "ECohtmlInputPropagationBehaviour::KeyboardAndJoystick" },
				{ "ModuleRelativePath", "Classes/SCohtmlInputForward.h" },
				{ "None.Name", "ECohtmlInputPropagationBehaviour::None" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_CohtmlPlugin,
				nullptr,
				"ECohtmlInputPropagationBehaviour",
				"ECohtmlInputPropagationBehaviour::Type",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::Namespaced,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* ECohtmlGamepadBehaviourOnFocusLost_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_CohtmlPlugin_ECohtmlGamepadBehaviourOnFocusLost, Z_Construct_UPackage__Script_CohtmlPlugin(), TEXT("ECohtmlGamepadBehaviourOnFocusLost"));
		}
		return Singleton;
	}
	template<> COHTMLPLUGIN_API UEnum* StaticEnum<ECohtmlGamepadBehaviourOnFocusLost>()
	{
		return ECohtmlGamepadBehaviourOnFocusLost_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ECohtmlGamepadBehaviourOnFocusLost(ECohtmlGamepadBehaviourOnFocusLost_StaticEnum, TEXT("/Script/CohtmlPlugin"), TEXT("ECohtmlGamepadBehaviourOnFocusLost"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_CohtmlPlugin_ECohtmlGamepadBehaviourOnFocusLost_Hash() { return 1864850046U; }
	UEnum* Z_Construct_UEnum_CohtmlPlugin_ECohtmlGamepadBehaviourOnFocusLost()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_CohtmlPlugin();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ECohtmlGamepadBehaviourOnFocusLost"), 0, Get_Z_Construct_UEnum_CohtmlPlugin_ECohtmlGamepadBehaviourOnFocusLost_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "CohtmlResetState", (int64)CohtmlResetState },
				{ "CohtmlUseCurrentState", (int64)CohtmlUseCurrentState },
				{ "CohtmlUseStateBeforeReset", (int64)CohtmlUseStateBeforeReset },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "CohtmlResetState.Comment", "/// Set the current state to zero this is default behaviour.\n" },
				{ "CohtmlResetState.Name", "CohtmlResetState" },
				{ "CohtmlResetState.ToolTip", "Set the current state to zero this is default behaviour." },
				{ "CohtmlUseCurrentState.Comment", "/// Behaviour will be the same as before losing a focus\n" },
				{ "CohtmlUseCurrentState.Name", "CohtmlUseCurrentState" },
				{ "CohtmlUseCurrentState.ToolTip", "Behaviour will be the same as before losing a focus" },
				{ "CohtmlUseStateBeforeReset.Comment", "/// Will save the last known state, set the current state to zero and\n/// once focus is regained by UI that saved state will be reapplied\n" },
				{ "CohtmlUseStateBeforeReset.Name", "CohtmlUseStateBeforeReset" },
				{ "CohtmlUseStateBeforeReset.ToolTip", "Will save the last known state, set the current state to zero and\nonce focus is regained by UI that saved state will be reapplied" },
				{ "DisplayName", "Prysm Gamepad Behaviour On Focus Lost" },
				{ "ModuleRelativePath", "Classes/SCohtmlInputForward.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_CohtmlPlugin,
				nullptr,
				"ECohtmlGamepadBehaviourOnFocusLost",
				"ECohtmlGamepadBehaviourOnFocusLost",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::Regular,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* ECohtmlInputWidgetLineTraceMode_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputWidgetLineTraceMode, Z_Construct_UPackage__Script_CohtmlPlugin(), TEXT("ECohtmlInputWidgetLineTraceMode"));
		}
		return Singleton;
	}
	template<> COHTMLPLUGIN_API UEnum* StaticEnum<ECohtmlInputWidgetLineTraceMode>()
	{
		return ECohtmlInputWidgetLineTraceMode_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ECohtmlInputWidgetLineTraceMode(ECohtmlInputWidgetLineTraceMode_StaticEnum, TEXT("/Script/CohtmlPlugin"), TEXT("ECohtmlInputWidgetLineTraceMode"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputWidgetLineTraceMode_Hash() { return 1182693057U; }
	UEnum* Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputWidgetLineTraceMode()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_CohtmlPlugin();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ECohtmlInputWidgetLineTraceMode"), 0, Get_Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputWidgetLineTraceMode_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "CohtmlInputLineTrace_Single", (int64)CohtmlInputLineTrace_Single },
				{ "CohtmlInputLineTrace_Multi", (int64)CohtmlInputLineTrace_Multi },
				{ "CohtmlInputLineTrace_MAX", (int64)CohtmlInputLineTrace_MAX },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "CohtmlInputLineTrace_MAX.Name", "CohtmlInputLineTrace_MAX" },
				{ "CohtmlInputLineTrace_Multi.DisplayName", "Multiple objects trace" },
				{ "CohtmlInputLineTrace_Multi.Name", "CohtmlInputLineTrace_Multi" },
				{ "CohtmlInputLineTrace_Single.DisplayName", "Single object trace" },
				{ "CohtmlInputLineTrace_Single.Name", "CohtmlInputLineTrace_Single" },
				{ "DisplayName", "Prysm Input Widget Line Trace Mode" },
				{ "ModuleRelativePath", "Classes/SCohtmlInputForward.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_CohtmlPlugin,
				nullptr,
				"ECohtmlInputWidgetLineTraceMode",
				"ECohtmlInputWidgetLineTraceMode",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::Regular,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* ECohtmlInputWidgetRaycastQuality_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputWidgetRaycastQuality, Z_Construct_UPackage__Script_CohtmlPlugin(), TEXT("ECohtmlInputWidgetRaycastQuality"));
		}
		return Singleton;
	}
	template<> COHTMLPLUGIN_API UEnum* StaticEnum<ECohtmlInputWidgetRaycastQuality>()
	{
		return ECohtmlInputWidgetRaycastQuality_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ECohtmlInputWidgetRaycastQuality(ECohtmlInputWidgetRaycastQuality_StaticEnum, TEXT("/Script/CohtmlPlugin"), TEXT("ECohtmlInputWidgetRaycastQuality"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputWidgetRaycastQuality_Hash() { return 679129494U; }
	UEnum* Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputWidgetRaycastQuality()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_CohtmlPlugin();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ECohtmlInputWidgetRaycastQuality"), 0, Get_Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputWidgetRaycastQuality_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "CohtmlRaycastQuality_Fast", (int64)CohtmlRaycastQuality_Fast },
				{ "CohtmlRaycastQuality_Balanced", (int64)CohtmlRaycastQuality_Balanced },
				{ "CohtmlRaycastQuality_Accurate", (int64)CohtmlRaycastQuality_Accurate },
				{ "CohtmlRaycastQuality_MAX", (int64)CohtmlRaycastQuality_MAX },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "CohtmlRaycastQuality_Accurate.DisplayName", "Accurate" },
				{ "CohtmlRaycastQuality_Accurate.Name", "CohtmlRaycastQuality_Accurate" },
				{ "CohtmlRaycastQuality_Balanced.DisplayName", "Balanced" },
				{ "CohtmlRaycastQuality_Balanced.Name", "CohtmlRaycastQuality_Balanced" },
				{ "CohtmlRaycastQuality_Fast.DisplayName", "Fast" },
				{ "CohtmlRaycastQuality_Fast.Name", "CohtmlRaycastQuality_Fast" },
				{ "CohtmlRaycastQuality_MAX.Name", "CohtmlRaycastQuality_MAX" },
				{ "DisplayName", "Prysm Input Widget Raycast Quality" },
				{ "ModuleRelativePath", "Classes/SCohtmlInputForward.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_CohtmlPlugin,
				nullptr,
				"ECohtmlInputWidgetRaycastQuality",
				"ECohtmlInputWidgetRaycastQuality",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::Regular,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
