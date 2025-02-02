// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CoherentRenderingPlugin/Classes/CoherentRenderingSettings.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCoherentRenderingSettings() {}
// Cross Module References
	COHERENTRENDERINGPLUGIN_API UEnum* Z_Construct_UEnum_CoherentRenderingPlugin_ECoherentRenderingSettingsSeverity();
	UPackage* Z_Construct_UPackage__Script_CoherentRenderingPlugin();
	COHERENTRENDERINGPLUGIN_API UClass* Z_Construct_UClass_UCoherentRenderingSettings_NoRegister();
	COHERENTRENDERINGPLUGIN_API UClass* Z_Construct_UClass_UCoherentRenderingSettings();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
// End Cross Module References
	static UEnum* ECoherentRenderingSettingsSeverity_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_CoherentRenderingPlugin_ECoherentRenderingSettingsSeverity, Z_Construct_UPackage__Script_CoherentRenderingPlugin(), TEXT("ECoherentRenderingSettingsSeverity"));
		}
		return Singleton;
	}
	template<> COHERENTRENDERINGPLUGIN_API UEnum* StaticEnum<ECoherentRenderingSettingsSeverity>()
	{
		return ECoherentRenderingSettingsSeverity_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ECoherentRenderingSettingsSeverity(ECoherentRenderingSettingsSeverity_StaticEnum, TEXT("/Script/CoherentRenderingPlugin"), TEXT("ECoherentRenderingSettingsSeverity"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_CoherentRenderingPlugin_ECoherentRenderingSettingsSeverity_Hash() { return 2761533666U; }
	UEnum* Z_Construct_UEnum_CoherentRenderingPlugin_ECoherentRenderingSettingsSeverity()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_CoherentRenderingPlugin();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ECoherentRenderingSettingsSeverity"), 0, Get_Z_Construct_UEnum_CoherentRenderingPlugin_ECoherentRenderingSettingsSeverity_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ECoherentRenderingSettingsSeverity::Trace", (int64)ECoherentRenderingSettingsSeverity::Trace },
				{ "ECoherentRenderingSettingsSeverity::Debug", (int64)ECoherentRenderingSettingsSeverity::Debug },
				{ "ECoherentRenderingSettingsSeverity::Info", (int64)ECoherentRenderingSettingsSeverity::Info },
				{ "ECoherentRenderingSettingsSeverity::Warning", (int64)ECoherentRenderingSettingsSeverity::Warning },
				{ "ECoherentRenderingSettingsSeverity::AssertFailure", (int64)ECoherentRenderingSettingsSeverity::AssertFailure },
				{ "ECoherentRenderingSettingsSeverity::Error", (int64)ECoherentRenderingSettingsSeverity::Error },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "AssertFailure.Name", "ECoherentRenderingSettingsSeverity::AssertFailure" },
				{ "Comment", "/**\n * Auxiliary enum for log severities that's visible in the Editor.\n * It should mirror the renoir::Severity one.\n */" },
				{ "Debug.Name", "ECoherentRenderingSettingsSeverity::Debug" },
				{ "Error.Name", "ECoherentRenderingSettingsSeverity::Error" },
				{ "Info.Name", "ECoherentRenderingSettingsSeverity::Info" },
				{ "ModuleRelativePath", "Classes/CoherentRenderingSettings.h" },
				{ "ToolTip", "Auxiliary enum for log severities that's visible in the Editor.\nIt should mirror the renoir::Severity one." },
				{ "Trace.Name", "ECoherentRenderingSettingsSeverity::Trace" },
				{ "Warning.Name", "ECoherentRenderingSettingsSeverity::Warning" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_CoherentRenderingPlugin,
				nullptr,
				"ECoherentRenderingSettingsSeverity",
				"ECoherentRenderingSettingsSeverity",
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
	void UCoherentRenderingSettings::StaticRegisterNativesUCoherentRenderingSettings()
	{
	}
	UClass* Z_Construct_UClass_UCoherentRenderingSettings_NoRegister()
	{
		return UCoherentRenderingSettings::StaticClass();
	}
	struct Z_Construct_UClass_UCoherentRenderingSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RenderingLogSeverity_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_RenderingLogSeverity;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_RenderingLogSeverity_Underlying;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCoherentRenderingSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_CoherentRenderingPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCoherentRenderingSettings_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Implements the settings for the Coherent Rendering plugin.\n */" },
		{ "IncludePath", "CoherentRenderingSettings.h" },
		{ "ModuleRelativePath", "Classes/CoherentRenderingSettings.h" },
		{ "ToolTip", "Implements the settings for the Coherent Rendering plugin." },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCoherentRenderingSettings_Statics::NewProp_RenderingLogSeverity_MetaData[] = {
		{ "Category", "Settings" },
		{ "Comment", "/// Sets the log severity of the Coherent Rendering Plugin.\n/// Requires restart of the editor to take effect.\n" },
		{ "ModuleRelativePath", "Classes/CoherentRenderingSettings.h" },
		{ "ToolTip", "Sets the log severity of the Coherent Rendering Plugin.\nRequires restart of the editor to take effect." },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UCoherentRenderingSettings_Statics::NewProp_RenderingLogSeverity = { "RenderingLogSeverity", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCoherentRenderingSettings, RenderingLogSeverity), Z_Construct_UEnum_CoherentRenderingPlugin_ECoherentRenderingSettingsSeverity, METADATA_PARAMS(Z_Construct_UClass_UCoherentRenderingSettings_Statics::NewProp_RenderingLogSeverity_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCoherentRenderingSettings_Statics::NewProp_RenderingLogSeverity_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UCoherentRenderingSettings_Statics::NewProp_RenderingLogSeverity_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCoherentRenderingSettings_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCoherentRenderingSettings_Statics::NewProp_RenderingLogSeverity,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCoherentRenderingSettings_Statics::NewProp_RenderingLogSeverity_Underlying,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCoherentRenderingSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCoherentRenderingSettings>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCoherentRenderingSettings_Statics::ClassParams = {
		&UCoherentRenderingSettings::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UCoherentRenderingSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UCoherentRenderingSettings_Statics::PropPointers),
		0,
		0x001000A6u,
		METADATA_PARAMS(Z_Construct_UClass_UCoherentRenderingSettings_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCoherentRenderingSettings_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCoherentRenderingSettings()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCoherentRenderingSettings_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCoherentRenderingSettings, 630560757);
	template<> COHERENTRENDERINGPLUGIN_API UClass* StaticClass<UCoherentRenderingSettings>()
	{
		return UCoherentRenderingSettings::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCoherentRenderingSettings(Z_Construct_UClass_UCoherentRenderingSettings, &UCoherentRenderingSettings::StaticClass, TEXT("/Script/CoherentRenderingPlugin"), TEXT("UCoherentRenderingSettings"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCoherentRenderingSettings);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
