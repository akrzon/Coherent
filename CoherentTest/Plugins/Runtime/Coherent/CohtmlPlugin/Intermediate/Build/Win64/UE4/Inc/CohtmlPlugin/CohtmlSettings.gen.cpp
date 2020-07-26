// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CohtmlPlugin/Classes/CohtmlSettings.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCohtmlSettings() {}
// Cross Module References
	COHTMLPLUGIN_API UEnum* Z_Construct_UEnum_CohtmlPlugin_ECohtmlImageFormat();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin();
	COHTMLPLUGIN_API UEnum* Z_Construct_UEnum_CohtmlPlugin_ECohtmlMSAA();
	COHTMLPLUGIN_API UEnum* Z_Construct_UEnum_CohtmlPlugin_ECohtmlSettingsSeverity();
	COHTMLPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FSingleFormatFallbacks();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlSettings_NoRegister();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlSettings();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
// End Cross Module References
	static UEnum* ECohtmlImageFormat_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_CohtmlPlugin_ECohtmlImageFormat, Z_Construct_UPackage__Script_CohtmlPlugin(), TEXT("ECohtmlImageFormat"));
		}
		return Singleton;
	}
	template<> COHTMLPLUGIN_API UEnum* StaticEnum<ECohtmlImageFormat>()
	{
		return ECohtmlImageFormat_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ECohtmlImageFormat(ECohtmlImageFormat_StaticEnum, TEXT("/Script/CohtmlPlugin"), TEXT("ECohtmlImageFormat"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_CohtmlPlugin_ECohtmlImageFormat_Hash() { return 3136895392U; }
	UEnum* Z_Construct_UEnum_CohtmlPlugin_ECohtmlImageFormat()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_CohtmlPlugin();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ECohtmlImageFormat"), 0, Get_Z_Construct_UEnum_CohtmlPlugin_ECohtmlImageFormat_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ECohtmlImageFormat::PNG", (int64)ECohtmlImageFormat::PNG },
				{ "ECohtmlImageFormat::TGA", (int64)ECohtmlImageFormat::TGA },
				{ "ECohtmlImageFormat::JPEG", (int64)ECohtmlImageFormat::JPEG },
				{ "ECohtmlImageFormat::PSD", (int64)ECohtmlImageFormat::PSD },
				{ "ECohtmlImageFormat::SVG", (int64)ECohtmlImageFormat::SVG },
				{ "ECohtmlImageFormat::DDS", (int64)ECohtmlImageFormat::DDS },
				{ "ECohtmlImageFormat::BMP", (int64)ECohtmlImageFormat::BMP },
				{ "ECohtmlImageFormat::ASTC", (int64)ECohtmlImageFormat::ASTC },
				{ "ECohtmlImageFormat::PKM", (int64)ECohtmlImageFormat::PKM },
				{ "ECohtmlImageFormat::KTX", (int64)ECohtmlImageFormat::KTX },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "ASTC.Name", "ECohtmlImageFormat::ASTC" },
				{ "BlueprintType", "true" },
				{ "BMP.Name", "ECohtmlImageFormat::BMP" },
				{ "DDS.Name", "ECohtmlImageFormat::DDS" },
				{ "DisplayName", "Prysm image formats" },
				{ "JPEG.Name", "ECohtmlImageFormat::JPEG" },
				{ "KTX.Name", "ECohtmlImageFormat::KTX" },
				{ "ModuleRelativePath", "Classes/CohtmlSettings.h" },
				{ "PKM.Name", "ECohtmlImageFormat::PKM" },
				{ "PNG.Name", "ECohtmlImageFormat::PNG" },
				{ "PSD.Name", "ECohtmlImageFormat::PSD" },
				{ "SVG.Name", "ECohtmlImageFormat::SVG" },
				{ "TGA.Name", "ECohtmlImageFormat::TGA" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_CohtmlPlugin,
				nullptr,
				"ECohtmlImageFormat",
				"ECohtmlImageFormat",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* ECohtmlMSAA_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_CohtmlPlugin_ECohtmlMSAA, Z_Construct_UPackage__Script_CohtmlPlugin(), TEXT("ECohtmlMSAA"));
		}
		return Singleton;
	}
	template<> COHTMLPLUGIN_API UEnum* StaticEnum<ECohtmlMSAA>()
	{
		return ECohtmlMSAA_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ECohtmlMSAA(ECohtmlMSAA_StaticEnum, TEXT("/Script/CohtmlPlugin"), TEXT("ECohtmlMSAA"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_CohtmlPlugin_ECohtmlMSAA_Hash() { return 1276995902U; }
	UEnum* Z_Construct_UEnum_CohtmlPlugin_ECohtmlMSAA()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_CohtmlPlugin();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ECohtmlMSAA"), 0, Get_Z_Construct_UEnum_CohtmlPlugin_ECohtmlMSAA_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ECohtmlMSAA::MSAA_1x", (int64)ECohtmlMSAA::MSAA_1x },
				{ "ECohtmlMSAA::MSAA_2x", (int64)ECohtmlMSAA::MSAA_2x },
				{ "ECohtmlMSAA::MSAA_4x", (int64)ECohtmlMSAA::MSAA_4x },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "DisplayName", "Prysm MSAA" },
				{ "ModuleRelativePath", "Classes/CohtmlSettings.h" },
				{ "MSAA_1x.DisplayName", "1x" },
				{ "MSAA_1x.Name", "ECohtmlMSAA::MSAA_1x" },
				{ "MSAA_2x.DisplayName", "2x" },
				{ "MSAA_2x.Name", "ECohtmlMSAA::MSAA_2x" },
				{ "MSAA_4x.DisplayName", "4x" },
				{ "MSAA_4x.Name", "ECohtmlMSAA::MSAA_4x" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_CohtmlPlugin,
				nullptr,
				"ECohtmlMSAA",
				"ECohtmlMSAA",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* ECohtmlSettingsSeverity_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_CohtmlPlugin_ECohtmlSettingsSeverity, Z_Construct_UPackage__Script_CohtmlPlugin(), TEXT("ECohtmlSettingsSeverity"));
		}
		return Singleton;
	}
	template<> COHTMLPLUGIN_API UEnum* StaticEnum<ECohtmlSettingsSeverity>()
	{
		return ECohtmlSettingsSeverity_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ECohtmlSettingsSeverity(ECohtmlSettingsSeverity_StaticEnum, TEXT("/Script/CohtmlPlugin"), TEXT("ECohtmlSettingsSeverity"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_CohtmlPlugin_ECohtmlSettingsSeverity_Hash() { return 3228998717U; }
	UEnum* Z_Construct_UEnum_CohtmlPlugin_ECohtmlSettingsSeverity()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_CohtmlPlugin();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ECohtmlSettingsSeverity"), 0, Get_Z_Construct_UEnum_CohtmlPlugin_ECohtmlSettingsSeverity_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ECohtmlSettingsSeverity::Trace", (int64)ECohtmlSettingsSeverity::Trace },
				{ "ECohtmlSettingsSeverity::Debug", (int64)ECohtmlSettingsSeverity::Debug },
				{ "ECohtmlSettingsSeverity::Info", (int64)ECohtmlSettingsSeverity::Info },
				{ "ECohtmlSettingsSeverity::Warning", (int64)ECohtmlSettingsSeverity::Warning },
				{ "ECohtmlSettingsSeverity::AssertFailure", (int64)ECohtmlSettingsSeverity::AssertFailure },
				{ "ECohtmlSettingsSeverity::Error", (int64)ECohtmlSettingsSeverity::Error },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "AssertFailure.Name", "ECohtmlSettingsSeverity::AssertFailure" },
				{ "Comment", "/**\n * Auxiliary enum for log severities that's visible in the Editor.\n * It should mirror the cohtml::Logging::Severity one.\n */" },
				{ "Debug.Name", "ECohtmlSettingsSeverity::Debug" },
				{ "DisplayName", "Prysm Settings Severity" },
				{ "Error.Name", "ECohtmlSettingsSeverity::Error" },
				{ "Info.Name", "ECohtmlSettingsSeverity::Info" },
				{ "ModuleRelativePath", "Classes/CohtmlSettings.h" },
				{ "ToolTip", "Auxiliary enum for log severities that's visible in the Editor.\nIt should mirror the cohtml::Logging::Severity one." },
				{ "Trace.Name", "ECohtmlSettingsSeverity::Trace" },
				{ "Warning.Name", "ECohtmlSettingsSeverity::Warning" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_CohtmlPlugin,
				nullptr,
				"ECohtmlSettingsSeverity",
				"ECohtmlSettingsSeverity",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
class UScriptStruct* FSingleFormatFallbacks::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern COHTMLPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FSingleFormatFallbacks_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FSingleFormatFallbacks, Z_Construct_UPackage__Script_CohtmlPlugin(), TEXT("SingleFormatFallbacks"), sizeof(FSingleFormatFallbacks), Get_Z_Construct_UScriptStruct_FSingleFormatFallbacks_Hash());
	}
	return Singleton;
}
template<> COHTMLPLUGIN_API UScriptStruct* StaticStruct<FSingleFormatFallbacks>()
{
	return FSingleFormatFallbacks::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FSingleFormatFallbacks(FSingleFormatFallbacks::StaticStruct, TEXT("/Script/CohtmlPlugin"), TEXT("SingleFormatFallbacks"), false, nullptr, nullptr);
static struct FScriptStruct_CohtmlPlugin_StaticRegisterNativesFSingleFormatFallbacks
{
	FScriptStruct_CohtmlPlugin_StaticRegisterNativesFSingleFormatFallbacks()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("SingleFormatFallbacks")),new UScriptStruct::TCppStructOps<FSingleFormatFallbacks>);
	}
} ScriptStruct_CohtmlPlugin_StaticRegisterNativesFSingleFormatFallbacks;
	struct Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PossibleFallbacks_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_PossibleFallbacks;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_PossibleFallbacks_Inner;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_PossibleFallbacks_Inner_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BaseFormat_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_BaseFormat;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_BaseFormat_Underlying;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Classes/CohtmlSettings.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSingleFormatFallbacks>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::NewProp_PossibleFallbacks_MetaData[] = {
		{ "Category", "Settings" },
		{ "Comment", "/** This array specifies the possible fallback formats of the base format\n\x09*   and the order in which they will be tried.\n\x09*/" },
		{ "DisplayName", "Permitted fallback formats" },
		{ "ModuleRelativePath", "Classes/CohtmlSettings.h" },
		{ "ToolTip", "This array specifies the possible fallback formats of the base format\n and the order in which they will be tried." },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::NewProp_PossibleFallbacks = { "PossibleFallbacks", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSingleFormatFallbacks, PossibleFallbacks), METADATA_PARAMS(Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::NewProp_PossibleFallbacks_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::NewProp_PossibleFallbacks_MetaData)) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::NewProp_PossibleFallbacks_Inner = { "PossibleFallbacks", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UEnum_CohtmlPlugin_ECohtmlImageFormat, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::NewProp_PossibleFallbacks_Inner_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::NewProp_BaseFormat_MetaData[] = {
		{ "Category", "Settings" },
		{ "Comment", "/** This specifies the base format for which we want to add fallbacks */" },
		{ "DisplayName", "Base format" },
		{ "ModuleRelativePath", "Classes/CohtmlSettings.h" },
		{ "ToolTip", "This specifies the base format for which we want to add fallbacks" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::NewProp_BaseFormat = { "BaseFormat", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSingleFormatFallbacks, BaseFormat), Z_Construct_UEnum_CohtmlPlugin_ECohtmlImageFormat, METADATA_PARAMS(Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::NewProp_BaseFormat_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::NewProp_BaseFormat_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::NewProp_BaseFormat_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::NewProp_PossibleFallbacks,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::NewProp_PossibleFallbacks_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::NewProp_PossibleFallbacks_Inner_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::NewProp_BaseFormat,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::NewProp_BaseFormat_Underlying,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
		nullptr,
		&NewStructOps,
		"SingleFormatFallbacks",
		sizeof(FSingleFormatFallbacks),
		alignof(FSingleFormatFallbacks),
		Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FSingleFormatFallbacks()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FSingleFormatFallbacks_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_CohtmlPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("SingleFormatFallbacks"), sizeof(FSingleFormatFallbacks), Get_Z_Construct_UScriptStruct_FSingleFormatFallbacks_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FSingleFormatFallbacks_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FSingleFormatFallbacks_Hash() { return 2914623821U; }
	void UCohtmlSettings::StaticRegisterNativesUCohtmlSettings()
	{
	}
	UClass* Z_Construct_UClass_UCohtmlSettings_NoRegister()
	{
		return UCohtmlSettings::StaticClass();
	}
	struct Z_Construct_UClass_UCohtmlSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FallbacksForAllFormats_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_FallbacksForAllFormats;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_FallbacksForAllFormats_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MSAA_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_MSAA;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_MSAA_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TickWhileGameIsPaused_MetaData[];
#endif
		static void NewProp_TickWhileGameIsPaused_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_TickWhileGameIsPaused;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bRespectLetterboxing_MetaData[];
#endif
		static void NewProp_bRespectLetterboxing_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bRespectLetterboxing;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bRespectTitleSafeZone_MetaData[];
#endif
		static void NewProp_bRespectTitleSafeZone_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bRespectTitleSafeZone;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LogSeverity_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_LogSeverity;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_LogSeverity_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ShowWarningsOnScreen_MetaData[];
#endif
		static void NewProp_ShowWarningsOnScreen_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ShowWarningsOnScreen;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ScrollDelta_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ScrollDelta;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InputTransparentCssClasses_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_InputTransparentCssClasses;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_InputTransparentCssClasses_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HandleInputOnHTMLBody_MetaData[];
#endif
		static void NewProp_HandleInputOnHTMLBody_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_HandleInputOnHTMLBody;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EnableLocalization_MetaData[];
#endif
		static void NewProp_EnableLocalization_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_EnableLocalization;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DevToolsPort_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_DevToolsPort;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EnableLiveReload_MetaData[];
#endif
		static void NewProp_EnableLiveReload_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_EnableLiveReload;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCohtmlSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlSettings_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Implements the settings for the Prysm plugin.\n */" },
		{ "DisplayName", "Prysm Settings" },
		{ "IncludePath", "CohtmlSettings.h" },
		{ "ModuleRelativePath", "Classes/CohtmlSettings.h" },
		{ "ToolTip", "Implements the settings for the Prysm plugin." },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_FallbacksForAllFormats_MetaData[] = {
		{ "Category", "Settings" },
		{ "Comment", "/// Defines an array where every item specifies a base image format and its suggested fallbacks.\n/// Any time Prysm encounters an image from the base format, it will *INSTEAD*\n/// request an image with the first available fallback format, doing so\n/// until it finds an image or until it exhausts the full list or formats.\n/// You will NOT receive a request for the original image (with the base format).\n/// The request will instead contain the URL of the first specified fallback.\n/// You can provide your custom fallback formats dynamically by binding the\n/// ICohtmlPlugin::OnGetFallbackFormats delegate. This is especially useful for\n/// per-platform project fallback control. If you want to inject your own fallback\n/// URLs dynamically you can bind the ICohtmlPlugin::OnURLRequest delegate.\n/// Examples of the overrides can be found in CoherentSample.cpp and the official documentation.\n" },
		{ "DisplayName", "Fallback formats" },
		{ "ModuleRelativePath", "Classes/CohtmlSettings.h" },
		{ "ToolTip", "Defines an array where every item specifies a base image format and its suggested fallbacks.\nAny time Prysm encounters an image from the base format, it will *INSTEAD*\nrequest an image with the first available fallback format, doing so\nuntil it finds an image or until it exhausts the full list or formats.\nYou will NOT receive a request for the original image (with the base format).\nThe request will instead contain the URL of the first specified fallback.\nYou can provide your custom fallback formats dynamically by binding the\nICohtmlPlugin::OnGetFallbackFormats delegate. This is especially useful for\nper-platform project fallback control. If you want to inject your own fallback\nURLs dynamically you can bind the ICohtmlPlugin::OnURLRequest delegate.\nExamples of the overrides can be found in CoherentSample.cpp and the official documentation." },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_FallbacksForAllFormats = { "FallbacksForAllFormats", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlSettings, FallbacksForAllFormats), METADATA_PARAMS(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_FallbacksForAllFormats_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_FallbacksForAllFormats_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_FallbacksForAllFormats_Inner = { "FallbacksForAllFormats", nullptr, (EPropertyFlags)0x0000000000004000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FSingleFormatFallbacks, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_MSAA_MetaData[] = {
		{ "Comment", "/// Sets the number of samples Prysm uses to apply MSAA\n/// to components and widgets.\n" },
		{ "ModuleRelativePath", "Classes/CohtmlSettings.h" },
		{ "ToolTip", "Sets the number of samples Prysm uses to apply MSAA\nto components and widgets." },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_MSAA = { "MSAA", nullptr, (EPropertyFlags)0x0010000000004000, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlSettings, MSAA), Z_Construct_UEnum_CohtmlPlugin_ECohtmlMSAA, METADATA_PARAMS(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_MSAA_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_MSAA_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_MSAA_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_TickWhileGameIsPaused_MetaData[] = {
		{ "Category", "Settings|Miscellaneous" },
		{ "Comment", "/// Set to true to keep the UI running even while the game is paused.\n" },
		{ "ModuleRelativePath", "Classes/CohtmlSettings.h" },
		{ "ToolTip", "Set to true to keep the UI running even while the game is paused." },
	};
#endif
	void Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_TickWhileGameIsPaused_SetBit(void* Obj)
	{
		((UCohtmlSettings*)Obj)->TickWhileGameIsPaused = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_TickWhileGameIsPaused = { "TickWhileGameIsPaused", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UCohtmlSettings), &Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_TickWhileGameIsPaused_SetBit, METADATA_PARAMS(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_TickWhileGameIsPaused_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_TickWhileGameIsPaused_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_bRespectLetterboxing_MetaData[] = {
		{ "Category", "Settings|HUD" },
		{ "Comment", "/// Whether to respect the letterboxing area when drawing the HUD\n/// using ACohtmlGameHUD.\n/// Setting it to false will cause your HUD to render even on the\n/// black bars caused by letterboxing.\n" },
		{ "ModuleRelativePath", "Classes/CohtmlSettings.h" },
		{ "ToolTip", "Whether to respect the letterboxing area when drawing the HUD\nusing ACohtmlGameHUD.\nSetting it to false will cause your HUD to render even on the\nblack bars caused by letterboxing." },
	};
#endif
	void Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_bRespectLetterboxing_SetBit(void* Obj)
	{
		((UCohtmlSettings*)Obj)->bRespectLetterboxing = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_bRespectLetterboxing = { "bRespectLetterboxing", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UCohtmlSettings), &Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_bRespectLetterboxing_SetBit, METADATA_PARAMS(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_bRespectLetterboxing_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_bRespectLetterboxing_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_bRespectTitleSafeZone_MetaData[] = {
		{ "Category", "Settings|HUD" },
		{ "Comment", "/// Whether to respect the title safe zone when drawing the HUD\n/// using ACohtmlGameHUD.\n/// Setting it to false will cause your HUD to take all the space\n/// on your screen bounded by the game's aspect ratio\n/// instead of only the zone deemed safe by the platform.\n" },
		{ "ModuleRelativePath", "Classes/CohtmlSettings.h" },
		{ "ToolTip", "Whether to respect the title safe zone when drawing the HUD\nusing ACohtmlGameHUD.\nSetting it to false will cause your HUD to take all the space\non your screen bounded by the game's aspect ratio\ninstead of only the zone deemed safe by the platform." },
	};
#endif
	void Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_bRespectTitleSafeZone_SetBit(void* Obj)
	{
		((UCohtmlSettings*)Obj)->bRespectTitleSafeZone = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_bRespectTitleSafeZone = { "bRespectTitleSafeZone", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UCohtmlSettings), &Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_bRespectTitleSafeZone_SetBit, METADATA_PARAMS(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_bRespectTitleSafeZone_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_bRespectTitleSafeZone_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_LogSeverity_MetaData[] = {
		{ "Category", "Settings|Logging" },
		{ "Comment", "/// Sets the log severity of Prysm.\n/// Changing this option requires restarting the UE4 editor / game.\n" },
		{ "ModuleRelativePath", "Classes/CohtmlSettings.h" },
		{ "ToolTip", "Sets the log severity of Prysm.\nChanging this option requires restarting the UE4 editor / game." },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_LogSeverity = { "LogSeverity", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlSettings, LogSeverity), Z_Construct_UEnum_CohtmlPlugin_ECohtmlSettingsSeverity, METADATA_PARAMS(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_LogSeverity_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_LogSeverity_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_LogSeverity_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_ShowWarningsOnScreen_MetaData[] = {
		{ "Category", "Settings|Logging" },
		{ "Comment", "/// Allows warnings in the Editor\n/// to be printed on-screen\n" },
		{ "ModuleRelativePath", "Classes/CohtmlSettings.h" },
		{ "ToolTip", "Allows warnings in the Editor\nto be printed on-screen" },
	};
#endif
	void Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_ShowWarningsOnScreen_SetBit(void* Obj)
	{
		((UCohtmlSettings*)Obj)->ShowWarningsOnScreen = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_ShowWarningsOnScreen = { "ShowWarningsOnScreen", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UCohtmlSettings), &Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_ShowWarningsOnScreen_SetBit, METADATA_PARAMS(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_ShowWarningsOnScreen_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_ShowWarningsOnScreen_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_ScrollDelta_MetaData[] = {
		{ "Category", "Settings" },
		{ "Comment", "/// Sets how many pixels one mousewheel tick is worth when scrolling.\n/// Defaults to 40.\n" },
		{ "DisplayName", "Wheel scroll scale" },
		{ "ModuleRelativePath", "Classes/CohtmlSettings.h" },
		{ "ToolTip", "Sets how many pixels one mousewheel tick is worth when scrolling.\nDefaults to 40." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_ScrollDelta = { "ScrollDelta", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlSettings, ScrollDelta), METADATA_PARAMS(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_ScrollDelta_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_ScrollDelta_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_InputTransparentCssClasses_MetaData[] = {
		{ "Category", "Settings|Input" },
		{ "Comment", "/// Any HTML Node or it's parent nodes that have one of these CSS classes are marked\n/// as transparent input for the UI, meaning that click/touch events on such a node\n/// will be left unhandled by the UI and if no other widget handles that event, it\n/// will be handled by the engine itself.\n" },
		{ "DisplayName", "Input Transparent CSS Classes" },
		{ "ModuleRelativePath", "Classes/CohtmlSettings.h" },
		{ "ToolTip", "Any HTML Node or it's parent nodes that have one of these CSS classes are marked\nas transparent input for the UI, meaning that click/touch events on such a node\nwill be left unhandled by the UI and if no other widget handles that event, it\nwill be handled by the engine itself." },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_InputTransparentCssClasses = { "InputTransparentCssClasses", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlSettings, InputTransparentCssClasses), METADATA_PARAMS(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_InputTransparentCssClasses_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_InputTransparentCssClasses_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_InputTransparentCssClasses_Inner = { "InputTransparentCssClasses", nullptr, (EPropertyFlags)0x0000000000004000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_HandleInputOnHTMLBody_MetaData[] = {
		{ "Category", "Settings|Input" },
		{ "Comment", "/// Whether to handle input events that have reached the HTML Body. If a click/touch\n/// input event on the HTML Body is left unhandled by the UI and no other widget handles\n/// that event, it will be handled by the engine itself.\n" },
		{ "DisplayName", "Handle Input On HTML Body" },
		{ "ModuleRelativePath", "Classes/CohtmlSettings.h" },
		{ "ToolTip", "Whether to handle input events that have reached the HTML Body. If a click/touch\ninput event on the HTML Body is left unhandled by the UI and no other widget handles\nthat event, it will be handled by the engine itself." },
	};
#endif
	void Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_HandleInputOnHTMLBody_SetBit(void* Obj)
	{
		((UCohtmlSettings*)Obj)->HandleInputOnHTMLBody = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_HandleInputOnHTMLBody = { "HandleInputOnHTMLBody", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UCohtmlSettings), &Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_HandleInputOnHTMLBody_SetBit, METADATA_PARAMS(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_HandleInputOnHTMLBody_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_HandleInputOnHTMLBody_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_EnableLocalization_MetaData[] = {
		{ "Category", "Settings" },
		{ "Comment", "/// Enables localization via the data-l10n-id attribute. Any HTML element\n/// with the attribute data-l10n-id=\"Namespace.Key\" will get its text content\n/// translated according to UE4's localization settings.\n" },
		{ "ModuleRelativePath", "Classes/CohtmlSettings.h" },
		{ "ToolTip", "Enables localization via the data-l10n-id attribute. Any HTML element\nwith the attribute data-l10n-id=\"Namespace.Key\" will get its text content\ntranslated according to UE4's localization settings." },
	};
#endif
	void Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_EnableLocalization_SetBit(void* Obj)
	{
		((UCohtmlSettings*)Obj)->EnableLocalization = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_EnableLocalization = { "EnableLocalization", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UCohtmlSettings), &Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_EnableLocalization_SetBit, METADATA_PARAMS(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_EnableLocalization_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_EnableLocalization_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_DevToolsPort_MetaData[] = {
		{ "Category", "Settings" },
		{ "Comment", "/// The port on which to run Prysm's dev tools. Use the dev tools to debug, profile and inspect your UI.\n/// Changing this option requires restarting the UE4 editor / game.\n" },
		{ "ModuleRelativePath", "Classes/CohtmlSettings.h" },
		{ "ToolTip", "The port on which to run Prysm's dev tools. Use the dev tools to debug, profile and inspect your UI.\nChanging this option requires restarting the UE4 editor / game." },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_DevToolsPort = { "DevToolsPort", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCohtmlSettings, DevToolsPort), METADATA_PARAMS(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_DevToolsPort_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_DevToolsPort_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_EnableLiveReload_MetaData[] = {
		{ "Category", "Settings" },
		{ "Comment", "/// Enables live reload for all Prysm components and widgets. When enabled\n/// the plugin will watch all files inside uiresources folder that are loaded by\n/// your UI via coui:// and reload them should any of them change. Works only in PIE.\n" },
		{ "ModuleRelativePath", "Classes/CohtmlSettings.h" },
		{ "ToolTip", "Enables live reload for all Prysm components and widgets. When enabled\nthe plugin will watch all files inside uiresources folder that are loaded by\nyour UI via coui: and reload them should any of them change. Works only in PIE." },
	};
#endif
	void Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_EnableLiveReload_SetBit(void* Obj)
	{
		((UCohtmlSettings*)Obj)->EnableLiveReload = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_EnableLiveReload = { "EnableLiveReload", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UCohtmlSettings), &Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_EnableLiveReload_SetBit, METADATA_PARAMS(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_EnableLiveReload_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_EnableLiveReload_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCohtmlSettings_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_FallbacksForAllFormats,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_FallbacksForAllFormats_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_MSAA,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_MSAA_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_TickWhileGameIsPaused,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_bRespectLetterboxing,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_bRespectTitleSafeZone,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_LogSeverity,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_LogSeverity_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_ShowWarningsOnScreen,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_ScrollDelta,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_InputTransparentCssClasses,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_InputTransparentCssClasses_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_HandleInputOnHTMLBody,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_EnableLocalization,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_DevToolsPort,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCohtmlSettings_Statics::NewProp_EnableLiveReload,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCohtmlSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCohtmlSettings>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCohtmlSettings_Statics::ClassParams = {
		&UCohtmlSettings::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UCohtmlSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlSettings_Statics::PropPointers),
		0,
		0x001000A6u,
		METADATA_PARAMS(Z_Construct_UClass_UCohtmlSettings_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCohtmlSettings_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCohtmlSettings()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCohtmlSettings_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCohtmlSettings, 296783428);
	template<> COHTMLPLUGIN_API UClass* StaticClass<UCohtmlSettings>()
	{
		return UCohtmlSettings::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCohtmlSettings(Z_Construct_UClass_UCohtmlSettings, &UCohtmlSettings::StaticClass, TEXT("/Script/CohtmlPlugin"), TEXT("UCohtmlSettings"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCohtmlSettings);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
