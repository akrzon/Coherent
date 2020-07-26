// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CohtmlPlugin/Classes/CohtmlInputActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCohtmlInputActor() {}
// Cross Module References
	COHTMLPLUGIN_API UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyUp__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_CohtmlPlugin();
	COHTMLPLUGIN_API UEnum* Z_Construct_UEnum_CohtmlPlugin_ECohtmlKeys();
	COHTMLPLUGIN_API UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyDown__DelegateSignature();
	COHTMLPLUGIN_API UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonUp__DelegateSignature();
	COHTMLPLUGIN_API UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonDown__DelegateSignature();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_ACohtmlInputActor_NoRegister();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_ACohtmlInputActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_ACohtmlInputActor_AlwaysAcceptMouseInput();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_ACohtmlInputActor_GetInputPropagationBehaviour();
	COHTMLPLUGIN_API UEnum* Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputPropagationBehaviour();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_ACohtmlInputActor_Initialize();
	COHTMLPLUGIN_API UEnum* Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputWidgetRaycastQuality();
	ENGINE_API UEnum* Z_Construct_UEnum_Engine_TextureAddress();
	ENGINE_API UEnum* Z_Construct_UEnum_Engine_ECollisionChannel();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_ACohtmlInputActor_IsCohtmlFocused();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlInputFocus();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlViewFocus();
	COHTMLPLUGIN_API UClass* Z_Construct_UClass_UCohtmlBaseComponent_NoRegister();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_ACohtmlInputActor_SetInputPropagationBehaviour();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_ACohtmlInputActor_SetLineTraceMode();
	COHTMLPLUGIN_API UEnum* Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputWidgetLineTraceMode();
	COHTMLPLUGIN_API UFunction* Z_Construct_UFunction_ACohtmlInputActor_ToggleCohtmlInputFocus();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyUp__DelegateSignature_Statics
	{
		struct _Script_CohtmlPlugin_eventCohtmlInputActorKeyUp_Parms
		{
			TEnumAsByte<ECohtmlKeys::Type> Key;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Key;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyUp__DelegateSignature_Statics::NewProp_Key = { "Key", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_CohtmlPlugin_eventCohtmlInputActorKeyUp_Parms, Key), Z_Construct_UEnum_CohtmlPlugin_ECohtmlKeys, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyUp__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyUp__DelegateSignature_Statics::NewProp_Key,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyUp__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Classes/CohtmlInputActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyUp__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_CohtmlPlugin, nullptr, "CohtmlInputActorKeyUp__DelegateSignature", nullptr, nullptr, sizeof(_Script_CohtmlPlugin_eventCohtmlInputActorKeyUp_Parms), Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyUp__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyUp__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyUp__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyUp__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyUp__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyUp__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyDown__DelegateSignature_Statics
	{
		struct _Script_CohtmlPlugin_eventCohtmlInputActorKeyDown_Parms
		{
			TEnumAsByte<ECohtmlKeys::Type> Key;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Key;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyDown__DelegateSignature_Statics::NewProp_Key = { "Key", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_CohtmlPlugin_eventCohtmlInputActorKeyDown_Parms, Key), Z_Construct_UEnum_CohtmlPlugin_ECohtmlKeys, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyDown__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyDown__DelegateSignature_Statics::NewProp_Key,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyDown__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Classes/CohtmlInputActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyDown__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_CohtmlPlugin, nullptr, "CohtmlInputActorKeyDown__DelegateSignature", nullptr, nullptr, sizeof(_Script_CohtmlPlugin_eventCohtmlInputActorKeyDown_Parms), Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyDown__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyDown__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyDown__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyDown__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyDown__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyDown__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonUp__DelegateSignature_Statics
	{
		struct _Script_CohtmlPlugin_eventCohtmlInputActorMouseButtonUp_Parms
		{
			TEnumAsByte<ECohtmlKeys::Type> Button;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Button;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonUp__DelegateSignature_Statics::NewProp_Button = { "Button", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_CohtmlPlugin_eventCohtmlInputActorMouseButtonUp_Parms, Button), Z_Construct_UEnum_CohtmlPlugin_ECohtmlKeys, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonUp__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonUp__DelegateSignature_Statics::NewProp_Button,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonUp__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Classes/CohtmlInputActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonUp__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_CohtmlPlugin, nullptr, "CohtmlInputActorMouseButtonUp__DelegateSignature", nullptr, nullptr, sizeof(_Script_CohtmlPlugin_eventCohtmlInputActorMouseButtonUp_Parms), Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonUp__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonUp__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonUp__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonUp__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonUp__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonUp__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonDown__DelegateSignature_Statics
	{
		struct _Script_CohtmlPlugin_eventCohtmlInputActorMouseButtonDown_Parms
		{
			TEnumAsByte<ECohtmlKeys::Type> Button;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Button;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonDown__DelegateSignature_Statics::NewProp_Button = { "Button", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_CohtmlPlugin_eventCohtmlInputActorMouseButtonDown_Parms, Button), Z_Construct_UEnum_CohtmlPlugin_ECohtmlKeys, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonDown__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonDown__DelegateSignature_Statics::NewProp_Button,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonDown__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Classes/CohtmlInputActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonDown__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_CohtmlPlugin, nullptr, "CohtmlInputActorMouseButtonDown__DelegateSignature", nullptr, nullptr, sizeof(_Script_CohtmlPlugin_eventCohtmlInputActorMouseButtonDown_Parms), Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonDown__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonDown__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonDown__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonDown__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonDown__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonDown__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	static UEnum* ECohtmlKeys_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_CohtmlPlugin_ECohtmlKeys, Z_Construct_UPackage__Script_CohtmlPlugin(), TEXT("ECohtmlKeys"));
		}
		return Singleton;
	}
	template<> COHTMLPLUGIN_API UEnum* StaticEnum<ECohtmlKeys::Type>()
	{
		return ECohtmlKeys_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ECohtmlKeys(ECohtmlKeys_StaticEnum, TEXT("/Script/CohtmlPlugin"), TEXT("ECohtmlKeys"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_CohtmlPlugin_ECohtmlKeys_Hash() { return 931919925U; }
	UEnum* Z_Construct_UEnum_CohtmlPlugin_ECohtmlKeys()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_CohtmlPlugin();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ECohtmlKeys"), 0, Get_Z_Construct_UEnum_CohtmlPlugin_ECohtmlKeys_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ECohtmlKeys::LeftMouseButton", (int64)ECohtmlKeys::LeftMouseButton },
				{ "ECohtmlKeys::RightMouseButton", (int64)ECohtmlKeys::RightMouseButton },
				{ "ECohtmlKeys::MiddleMouseButton", (int64)ECohtmlKeys::MiddleMouseButton },
				{ "ECohtmlKeys::ThumbMouseButton", (int64)ECohtmlKeys::ThumbMouseButton },
				{ "ECohtmlKeys::ThumbMouseButton2", (int64)ECohtmlKeys::ThumbMouseButton2 },
				{ "ECohtmlKeys::BackSpace", (int64)ECohtmlKeys::BackSpace },
				{ "ECohtmlKeys::Tab", (int64)ECohtmlKeys::Tab },
				{ "ECohtmlKeys::Enter", (int64)ECohtmlKeys::Enter },
				{ "ECohtmlKeys::Pause", (int64)ECohtmlKeys::Pause },
				{ "ECohtmlKeys::CapsLock", (int64)ECohtmlKeys::CapsLock },
				{ "ECohtmlKeys::Escape", (int64)ECohtmlKeys::Escape },
				{ "ECohtmlKeys::SpaceBar", (int64)ECohtmlKeys::SpaceBar },
				{ "ECohtmlKeys::PageUp", (int64)ECohtmlKeys::PageUp },
				{ "ECohtmlKeys::PageDown", (int64)ECohtmlKeys::PageDown },
				{ "ECohtmlKeys::End", (int64)ECohtmlKeys::End },
				{ "ECohtmlKeys::Home", (int64)ECohtmlKeys::Home },
				{ "ECohtmlKeys::Left", (int64)ECohtmlKeys::Left },
				{ "ECohtmlKeys::Up", (int64)ECohtmlKeys::Up },
				{ "ECohtmlKeys::Right", (int64)ECohtmlKeys::Right },
				{ "ECohtmlKeys::Down", (int64)ECohtmlKeys::Down },
				{ "ECohtmlKeys::Insert", (int64)ECohtmlKeys::Insert },
				{ "ECohtmlKeys::Delete", (int64)ECohtmlKeys::Delete },
				{ "ECohtmlKeys::Zero", (int64)ECohtmlKeys::Zero },
				{ "ECohtmlKeys::One", (int64)ECohtmlKeys::One },
				{ "ECohtmlKeys::Two", (int64)ECohtmlKeys::Two },
				{ "ECohtmlKeys::Three", (int64)ECohtmlKeys::Three },
				{ "ECohtmlKeys::Four", (int64)ECohtmlKeys::Four },
				{ "ECohtmlKeys::Five", (int64)ECohtmlKeys::Five },
				{ "ECohtmlKeys::Six", (int64)ECohtmlKeys::Six },
				{ "ECohtmlKeys::Seven", (int64)ECohtmlKeys::Seven },
				{ "ECohtmlKeys::Eight", (int64)ECohtmlKeys::Eight },
				{ "ECohtmlKeys::Nine", (int64)ECohtmlKeys::Nine },
				{ "ECohtmlKeys::A", (int64)ECohtmlKeys::A },
				{ "ECohtmlKeys::B", (int64)ECohtmlKeys::B },
				{ "ECohtmlKeys::C", (int64)ECohtmlKeys::C },
				{ "ECohtmlKeys::D", (int64)ECohtmlKeys::D },
				{ "ECohtmlKeys::E", (int64)ECohtmlKeys::E },
				{ "ECohtmlKeys::F", (int64)ECohtmlKeys::F },
				{ "ECohtmlKeys::G", (int64)ECohtmlKeys::G },
				{ "ECohtmlKeys::H", (int64)ECohtmlKeys::H },
				{ "ECohtmlKeys::I", (int64)ECohtmlKeys::I },
				{ "ECohtmlKeys::J", (int64)ECohtmlKeys::J },
				{ "ECohtmlKeys::K", (int64)ECohtmlKeys::K },
				{ "ECohtmlKeys::L", (int64)ECohtmlKeys::L },
				{ "ECohtmlKeys::M", (int64)ECohtmlKeys::M },
				{ "ECohtmlKeys::N", (int64)ECohtmlKeys::N },
				{ "ECohtmlKeys::O", (int64)ECohtmlKeys::O },
				{ "ECohtmlKeys::P", (int64)ECohtmlKeys::P },
				{ "ECohtmlKeys::Q", (int64)ECohtmlKeys::Q },
				{ "ECohtmlKeys::R", (int64)ECohtmlKeys::R },
				{ "ECohtmlKeys::S", (int64)ECohtmlKeys::S },
				{ "ECohtmlKeys::T", (int64)ECohtmlKeys::T },
				{ "ECohtmlKeys::U", (int64)ECohtmlKeys::U },
				{ "ECohtmlKeys::V", (int64)ECohtmlKeys::V },
				{ "ECohtmlKeys::W", (int64)ECohtmlKeys::W },
				{ "ECohtmlKeys::X", (int64)ECohtmlKeys::X },
				{ "ECohtmlKeys::Y", (int64)ECohtmlKeys::Y },
				{ "ECohtmlKeys::Z", (int64)ECohtmlKeys::Z },
				{ "ECohtmlKeys::NumPadZero", (int64)ECohtmlKeys::NumPadZero },
				{ "ECohtmlKeys::NumPadOne", (int64)ECohtmlKeys::NumPadOne },
				{ "ECohtmlKeys::NumPadTwo", (int64)ECohtmlKeys::NumPadTwo },
				{ "ECohtmlKeys::NumPadThree", (int64)ECohtmlKeys::NumPadThree },
				{ "ECohtmlKeys::NumPadFour", (int64)ECohtmlKeys::NumPadFour },
				{ "ECohtmlKeys::NumPadFive", (int64)ECohtmlKeys::NumPadFive },
				{ "ECohtmlKeys::NumPadSix", (int64)ECohtmlKeys::NumPadSix },
				{ "ECohtmlKeys::NumPadSeven", (int64)ECohtmlKeys::NumPadSeven },
				{ "ECohtmlKeys::NumPadEight", (int64)ECohtmlKeys::NumPadEight },
				{ "ECohtmlKeys::NumPadNine", (int64)ECohtmlKeys::NumPadNine },
				{ "ECohtmlKeys::Multiply", (int64)ECohtmlKeys::Multiply },
				{ "ECohtmlKeys::Add", (int64)ECohtmlKeys::Add },
				{ "ECohtmlKeys::Subtract", (int64)ECohtmlKeys::Subtract },
				{ "ECohtmlKeys::Decimal", (int64)ECohtmlKeys::Decimal },
				{ "ECohtmlKeys::Divide", (int64)ECohtmlKeys::Divide },
				{ "ECohtmlKeys::F1", (int64)ECohtmlKeys::F1 },
				{ "ECohtmlKeys::F2", (int64)ECohtmlKeys::F2 },
				{ "ECohtmlKeys::F3", (int64)ECohtmlKeys::F3 },
				{ "ECohtmlKeys::F4", (int64)ECohtmlKeys::F4 },
				{ "ECohtmlKeys::F5", (int64)ECohtmlKeys::F5 },
				{ "ECohtmlKeys::F6", (int64)ECohtmlKeys::F6 },
				{ "ECohtmlKeys::F7", (int64)ECohtmlKeys::F7 },
				{ "ECohtmlKeys::F8", (int64)ECohtmlKeys::F8 },
				{ "ECohtmlKeys::F9", (int64)ECohtmlKeys::F9 },
				{ "ECohtmlKeys::F10", (int64)ECohtmlKeys::F10 },
				{ "ECohtmlKeys::F11", (int64)ECohtmlKeys::F11 },
				{ "ECohtmlKeys::F12", (int64)ECohtmlKeys::F12 },
				{ "ECohtmlKeys::NumLock", (int64)ECohtmlKeys::NumLock },
				{ "ECohtmlKeys::ScrollLock", (int64)ECohtmlKeys::ScrollLock },
				{ "ECohtmlKeys::LeftShift", (int64)ECohtmlKeys::LeftShift },
				{ "ECohtmlKeys::RightShift", (int64)ECohtmlKeys::RightShift },
				{ "ECohtmlKeys::LeftControl", (int64)ECohtmlKeys::LeftControl },
				{ "ECohtmlKeys::RightControl", (int64)ECohtmlKeys::RightControl },
				{ "ECohtmlKeys::LeftAlt", (int64)ECohtmlKeys::LeftAlt },
				{ "ECohtmlKeys::RightAlt", (int64)ECohtmlKeys::RightAlt },
				{ "ECohtmlKeys::LeftCommand", (int64)ECohtmlKeys::LeftCommand },
				{ "ECohtmlKeys::RightCommand", (int64)ECohtmlKeys::RightCommand },
				{ "ECohtmlKeys::Semicolon", (int64)ECohtmlKeys::Semicolon },
				{ "ECohtmlKeys::Equals", (int64)ECohtmlKeys::Equals },
				{ "ECohtmlKeys::Comma", (int64)ECohtmlKeys::Comma },
				{ "ECohtmlKeys::Underscore", (int64)ECohtmlKeys::Underscore },
				{ "ECohtmlKeys::Period", (int64)ECohtmlKeys::Period },
				{ "ECohtmlKeys::Slash", (int64)ECohtmlKeys::Slash },
				{ "ECohtmlKeys::Tilde", (int64)ECohtmlKeys::Tilde },
				{ "ECohtmlKeys::LeftBracket", (int64)ECohtmlKeys::LeftBracket },
				{ "ECohtmlKeys::Backslash", (int64)ECohtmlKeys::Backslash },
				{ "ECohtmlKeys::RightBracket", (int64)ECohtmlKeys::RightBracket },
				{ "ECohtmlKeys::Quote", (int64)ECohtmlKeys::Quote },
				{ "ECohtmlKeys::Unknown", (int64)ECohtmlKeys::Unknown },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "A.Name", "ECohtmlKeys::A" },
				{ "Add.Name", "ECohtmlKeys::Add" },
				{ "B.Name", "ECohtmlKeys::B" },
				{ "Backslash.Name", "ECohtmlKeys::Backslash" },
				{ "BackSpace.Name", "ECohtmlKeys::BackSpace" },
				{ "BlueprintType", "true" },
				{ "C.Name", "ECohtmlKeys::C" },
				{ "CapsLock.Name", "ECohtmlKeys::CapsLock" },
				{ "Comma.Name", "ECohtmlKeys::Comma" },
				{ "D.Name", "ECohtmlKeys::D" },
				{ "Decimal.Name", "ECohtmlKeys::Decimal" },
				{ "Delete.Name", "ECohtmlKeys::Delete" },
				{ "DisplayName", "Prysm Keys" },
				{ "Divide.Name", "ECohtmlKeys::Divide" },
				{ "Down.Name", "ECohtmlKeys::Down" },
				{ "E.Name", "ECohtmlKeys::E" },
				{ "Eight.Name", "ECohtmlKeys::Eight" },
				{ "End.Name", "ECohtmlKeys::End" },
				{ "Enter.Name", "ECohtmlKeys::Enter" },
				{ "Equals.Name", "ECohtmlKeys::Equals" },
				{ "Escape.Name", "ECohtmlKeys::Escape" },
				{ "F.Name", "ECohtmlKeys::F" },
				{ "F1.Name", "ECohtmlKeys::F1" },
				{ "F10.Name", "ECohtmlKeys::F10" },
				{ "F11.Name", "ECohtmlKeys::F11" },
				{ "F12.Name", "ECohtmlKeys::F12" },
				{ "F2.Name", "ECohtmlKeys::F2" },
				{ "F3.Name", "ECohtmlKeys::F3" },
				{ "F4.Name", "ECohtmlKeys::F4" },
				{ "F5.Name", "ECohtmlKeys::F5" },
				{ "F6.Name", "ECohtmlKeys::F6" },
				{ "F7.Name", "ECohtmlKeys::F7" },
				{ "F8.Name", "ECohtmlKeys::F8" },
				{ "F9.Name", "ECohtmlKeys::F9" },
				{ "Five.Name", "ECohtmlKeys::Five" },
				{ "Four.Name", "ECohtmlKeys::Four" },
				{ "G.Name", "ECohtmlKeys::G" },
				{ "H.Name", "ECohtmlKeys::H" },
				{ "Home.Name", "ECohtmlKeys::Home" },
				{ "I.Name", "ECohtmlKeys::I" },
				{ "Insert.Name", "ECohtmlKeys::Insert" },
				{ "J.Name", "ECohtmlKeys::J" },
				{ "K.Name", "ECohtmlKeys::K" },
				{ "L.Name", "ECohtmlKeys::L" },
				{ "Left.Name", "ECohtmlKeys::Left" },
				{ "LeftAlt.Name", "ECohtmlKeys::LeftAlt" },
				{ "LeftBracket.Name", "ECohtmlKeys::LeftBracket" },
				{ "LeftCommand.Name", "ECohtmlKeys::LeftCommand" },
				{ "LeftControl.Name", "ECohtmlKeys::LeftControl" },
				{ "LeftMouseButton.Comment", "// Using macro's in UENUMs doesn't seem to work so we need to duplicate the key declaration.\n// These are copied from the EKeys structure in InputCoreTypes.h\n" },
				{ "LeftMouseButton.Name", "ECohtmlKeys::LeftMouseButton" },
				{ "LeftMouseButton.ToolTip", "Using macro's in UENUMs doesn't seem to work so we need to duplicate the key declaration.\nThese are copied from the EKeys structure in InputCoreTypes.h" },
				{ "LeftShift.Name", "ECohtmlKeys::LeftShift" },
				{ "M.Name", "ECohtmlKeys::M" },
				{ "MiddleMouseButton.Name", "ECohtmlKeys::MiddleMouseButton" },
				{ "ModuleRelativePath", "Classes/CohtmlInputActor.h" },
				{ "Multiply.Name", "ECohtmlKeys::Multiply" },
				{ "N.Name", "ECohtmlKeys::N" },
				{ "Nine.Name", "ECohtmlKeys::Nine" },
				{ "NumLock.Name", "ECohtmlKeys::NumLock" },
				{ "NumPadEight.Name", "ECohtmlKeys::NumPadEight" },
				{ "NumPadFive.Name", "ECohtmlKeys::NumPadFive" },
				{ "NumPadFour.Name", "ECohtmlKeys::NumPadFour" },
				{ "NumPadNine.Name", "ECohtmlKeys::NumPadNine" },
				{ "NumPadOne.Name", "ECohtmlKeys::NumPadOne" },
				{ "NumPadSeven.Name", "ECohtmlKeys::NumPadSeven" },
				{ "NumPadSix.Name", "ECohtmlKeys::NumPadSix" },
				{ "NumPadThree.Name", "ECohtmlKeys::NumPadThree" },
				{ "NumPadTwo.Name", "ECohtmlKeys::NumPadTwo" },
				{ "NumPadZero.Name", "ECohtmlKeys::NumPadZero" },
				{ "O.Name", "ECohtmlKeys::O" },
				{ "One.Name", "ECohtmlKeys::One" },
				{ "P.Name", "ECohtmlKeys::P" },
				{ "PageDown.Name", "ECohtmlKeys::PageDown" },
				{ "PageUp.Name", "ECohtmlKeys::PageUp" },
				{ "Pause.Name", "ECohtmlKeys::Pause" },
				{ "Period.Name", "ECohtmlKeys::Period" },
				{ "Q.Name", "ECohtmlKeys::Q" },
				{ "Quote.Name", "ECohtmlKeys::Quote" },
				{ "R.Name", "ECohtmlKeys::R" },
				{ "Right.Name", "ECohtmlKeys::Right" },
				{ "RightAlt.Name", "ECohtmlKeys::RightAlt" },
				{ "RightBracket.Name", "ECohtmlKeys::RightBracket" },
				{ "RightCommand.Name", "ECohtmlKeys::RightCommand" },
				{ "RightControl.Name", "ECohtmlKeys::RightControl" },
				{ "RightMouseButton.Name", "ECohtmlKeys::RightMouseButton" },
				{ "RightShift.Name", "ECohtmlKeys::RightShift" },
				{ "S.Name", "ECohtmlKeys::S" },
				{ "ScrollLock.Name", "ECohtmlKeys::ScrollLock" },
				{ "Semicolon.Name", "ECohtmlKeys::Semicolon" },
				{ "Seven.Name", "ECohtmlKeys::Seven" },
				{ "Six.Name", "ECohtmlKeys::Six" },
				{ "Slash.Name", "ECohtmlKeys::Slash" },
				{ "SpaceBar.Name", "ECohtmlKeys::SpaceBar" },
				{ "Subtract.Name", "ECohtmlKeys::Subtract" },
				{ "T.Name", "ECohtmlKeys::T" },
				{ "Tab.Name", "ECohtmlKeys::Tab" },
				{ "Three.Name", "ECohtmlKeys::Three" },
				{ "ThumbMouseButton.Name", "ECohtmlKeys::ThumbMouseButton" },
				{ "ThumbMouseButton2.Name", "ECohtmlKeys::ThumbMouseButton2" },
				{ "Tilde.Name", "ECohtmlKeys::Tilde" },
				{ "Two.Name", "ECohtmlKeys::Two" },
				{ "U.Name", "ECohtmlKeys::U" },
				{ "Underscore.Name", "ECohtmlKeys::Underscore" },
				{ "Unknown.DisplayName", "Unknown" },
				{ "Unknown.Name", "ECohtmlKeys::Unknown" },
				{ "Up.Name", "ECohtmlKeys::Up" },
				{ "V.Name", "ECohtmlKeys::V" },
				{ "W.Name", "ECohtmlKeys::W" },
				{ "X.Name", "ECohtmlKeys::X" },
				{ "Y.Name", "ECohtmlKeys::Y" },
				{ "Z.Name", "ECohtmlKeys::Z" },
				{ "Zero.Name", "ECohtmlKeys::Zero" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_CohtmlPlugin,
				nullptr,
				"ECohtmlKeys",
				"ECohtmlKeys::Type",
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
	void ACohtmlInputActor::StaticRegisterNativesACohtmlInputActor()
	{
		UClass* Class = ACohtmlInputActor::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AlwaysAcceptMouseInput", &ACohtmlInputActor::execAlwaysAcceptMouseInput },
			{ "GetInputPropagationBehaviour", &ACohtmlInputActor::execGetInputPropagationBehaviour },
			{ "Initialize", &ACohtmlInputActor::execInitialize },
			{ "IsCohtmlFocused", &ACohtmlInputActor::execIsCohtmlFocused },
			{ "SetCohtmlInputFocus", &ACohtmlInputActor::execSetCohtmlInputFocus },
			{ "SetCohtmlViewFocus", &ACohtmlInputActor::execSetCohtmlViewFocus },
			{ "SetInputPropagationBehaviour", &ACohtmlInputActor::execSetInputPropagationBehaviour },
			{ "SetLineTraceMode", &ACohtmlInputActor::execSetLineTraceMode },
			{ "ToggleCohtmlInputFocus", &ACohtmlInputActor::execToggleCohtmlInputFocus },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ACohtmlInputActor_AlwaysAcceptMouseInput_Statics
	{
		struct CohtmlInputActor_eventAlwaysAcceptMouseInput_Parms
		{
			bool bAccept;
		};
		static void NewProp_bAccept_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bAccept;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_ACohtmlInputActor_AlwaysAcceptMouseInput_Statics::NewProp_bAccept_SetBit(void* Obj)
	{
		((CohtmlInputActor_eventAlwaysAcceptMouseInput_Parms*)Obj)->bAccept = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ACohtmlInputActor_AlwaysAcceptMouseInput_Statics::NewProp_bAccept = { "bAccept", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CohtmlInputActor_eventAlwaysAcceptMouseInput_Parms), &Z_Construct_UFunction_ACohtmlInputActor_AlwaysAcceptMouseInput_Statics::NewProp_bAccept_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ACohtmlInputActor_AlwaysAcceptMouseInput_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACohtmlInputActor_AlwaysAcceptMouseInput_Statics::NewProp_bAccept,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ACohtmlInputActor_AlwaysAcceptMouseInput_Statics::Function_MetaDataParams[] = {
		{ "Category", "Prysm" },
		{ "ModuleRelativePath", "Classes/CohtmlInputActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ACohtmlInputActor_AlwaysAcceptMouseInput_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ACohtmlInputActor, nullptr, "AlwaysAcceptMouseInput", nullptr, nullptr, sizeof(CohtmlInputActor_eventAlwaysAcceptMouseInput_Parms), Z_Construct_UFunction_ACohtmlInputActor_AlwaysAcceptMouseInput_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlInputActor_AlwaysAcceptMouseInput_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ACohtmlInputActor_AlwaysAcceptMouseInput_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlInputActor_AlwaysAcceptMouseInput_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ACohtmlInputActor_AlwaysAcceptMouseInput()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ACohtmlInputActor_AlwaysAcceptMouseInput_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ACohtmlInputActor_GetInputPropagationBehaviour_Statics
	{
		struct CohtmlInputActor_eventGetInputPropagationBehaviour_Parms
		{
			TEnumAsByte<ECohtmlInputPropagationBehaviour::Type> ReturnValue;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ACohtmlInputActor_GetInputPropagationBehaviour_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlInputActor_eventGetInputPropagationBehaviour_Parms, ReturnValue), Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputPropagationBehaviour, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ACohtmlInputActor_GetInputPropagationBehaviour_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACohtmlInputActor_GetInputPropagationBehaviour_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ACohtmlInputActor_GetInputPropagationBehaviour_Statics::Function_MetaDataParams[] = {
		{ "Category", "Prysm" },
		{ "ModuleRelativePath", "Classes/CohtmlInputActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ACohtmlInputActor_GetInputPropagationBehaviour_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ACohtmlInputActor, nullptr, "GetInputPropagationBehaviour", nullptr, nullptr, sizeof(CohtmlInputActor_eventGetInputPropagationBehaviour_Parms), Z_Construct_UFunction_ACohtmlInputActor_GetInputPropagationBehaviour_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlInputActor_GetInputPropagationBehaviour_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ACohtmlInputActor_GetInputPropagationBehaviour_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlInputActor_GetInputPropagationBehaviour_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ACohtmlInputActor_GetInputPropagationBehaviour()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ACohtmlInputActor_GetInputPropagationBehaviour_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ACohtmlInputActor_Initialize_Statics
	{
		struct CohtmlInputActor_eventInitialize_Parms
		{
			TEnumAsByte<ECollisionChannel> CollisionChannel;
			TEnumAsByte<TextureAddress> AddressMode;
			TEnumAsByte<ECohtmlInputWidgetRaycastQuality> RaycastQuality;
			int32 UVChannel;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_UVChannel;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_RaycastQuality;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_AddressMode;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_CollisionChannel;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ACohtmlInputActor_Initialize_Statics::NewProp_UVChannel = { "UVChannel", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlInputActor_eventInitialize_Parms, UVChannel), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ACohtmlInputActor_Initialize_Statics::NewProp_RaycastQuality = { "RaycastQuality", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlInputActor_eventInitialize_Parms, RaycastQuality), Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputWidgetRaycastQuality, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ACohtmlInputActor_Initialize_Statics::NewProp_AddressMode = { "AddressMode", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlInputActor_eventInitialize_Parms, AddressMode), Z_Construct_UEnum_Engine_TextureAddress, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ACohtmlInputActor_Initialize_Statics::NewProp_CollisionChannel = { "CollisionChannel", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlInputActor_eventInitialize_Parms, CollisionChannel), Z_Construct_UEnum_Engine_ECollisionChannel, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ACohtmlInputActor_Initialize_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACohtmlInputActor_Initialize_Statics::NewProp_UVChannel,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACohtmlInputActor_Initialize_Statics::NewProp_RaycastQuality,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACohtmlInputActor_Initialize_Statics::NewProp_AddressMode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACohtmlInputActor_Initialize_Statics::NewProp_CollisionChannel,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ACohtmlInputActor_Initialize_Statics::Function_MetaDataParams[] = {
		{ "Category", "Prysm" },
		{ "CPP_Default_AddressMode", "TA_Wrap" },
		{ "CPP_Default_CollisionChannel", "ECC_WorldDynamic" },
		{ "CPP_Default_RaycastQuality", "CohtmlRaycastQuality_Accurate" },
		{ "CPP_Default_UVChannel", "0" },
		{ "ModuleRelativePath", "Classes/CohtmlInputActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ACohtmlInputActor_Initialize_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ACohtmlInputActor, nullptr, "Initialize", nullptr, nullptr, sizeof(CohtmlInputActor_eventInitialize_Parms), Z_Construct_UFunction_ACohtmlInputActor_Initialize_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlInputActor_Initialize_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ACohtmlInputActor_Initialize_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlInputActor_Initialize_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ACohtmlInputActor_Initialize()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ACohtmlInputActor_Initialize_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ACohtmlInputActor_IsCohtmlFocused_Statics
	{
		struct CohtmlInputActor_eventIsCohtmlFocused_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_ACohtmlInputActor_IsCohtmlFocused_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((CohtmlInputActor_eventIsCohtmlFocused_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ACohtmlInputActor_IsCohtmlFocused_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CohtmlInputActor_eventIsCohtmlFocused_Parms), &Z_Construct_UFunction_ACohtmlInputActor_IsCohtmlFocused_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ACohtmlInputActor_IsCohtmlFocused_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACohtmlInputActor_IsCohtmlFocused_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ACohtmlInputActor_IsCohtmlFocused_Statics::Function_MetaDataParams[] = {
		{ "Category", "Prysm" },
		{ "DisplayName", "IsFocused" },
		{ "ModuleRelativePath", "Classes/CohtmlInputActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ACohtmlInputActor_IsCohtmlFocused_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ACohtmlInputActor, nullptr, "IsCohtmlFocused", nullptr, nullptr, sizeof(CohtmlInputActor_eventIsCohtmlFocused_Parms), Z_Construct_UFunction_ACohtmlInputActor_IsCohtmlFocused_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlInputActor_IsCohtmlFocused_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ACohtmlInputActor_IsCohtmlFocused_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlInputActor_IsCohtmlFocused_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ACohtmlInputActor_IsCohtmlFocused()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ACohtmlInputActor_IsCohtmlFocused_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlInputFocus_Statics
	{
		struct CohtmlInputActor_eventSetCohtmlInputFocus_Parms
		{
			bool FocusUI;
		};
		static void NewProp_FocusUI_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_FocusUI;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlInputFocus_Statics::NewProp_FocusUI_SetBit(void* Obj)
	{
		((CohtmlInputActor_eventSetCohtmlInputFocus_Parms*)Obj)->FocusUI = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlInputFocus_Statics::NewProp_FocusUI = { "FocusUI", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CohtmlInputActor_eventSetCohtmlInputFocus_Parms), &Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlInputFocus_Statics::NewProp_FocusUI_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlInputFocus_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlInputFocus_Statics::NewProp_FocusUI,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlInputFocus_Statics::Function_MetaDataParams[] = {
		{ "Category", "Prysm" },
		{ "DisplayName", "SetInputFocus" },
		{ "ModuleRelativePath", "Classes/CohtmlInputActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlInputFocus_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ACohtmlInputActor, nullptr, "SetCohtmlInputFocus", nullptr, nullptr, sizeof(CohtmlInputActor_eventSetCohtmlInputFocus_Parms), Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlInputFocus_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlInputFocus_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlInputFocus_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlInputFocus_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlInputFocus()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlInputFocus_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlViewFocus_Statics
	{
		struct CohtmlInputActor_eventSetCohtmlViewFocus_Parms
		{
			UCohtmlBaseComponent* NewFocusedView;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NewFocusedView_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_NewFocusedView;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlViewFocus_Statics::NewProp_NewFocusedView_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlViewFocus_Statics::NewProp_NewFocusedView = { "NewFocusedView", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlInputActor_eventSetCohtmlViewFocus_Parms, NewFocusedView), Z_Construct_UClass_UCohtmlBaseComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlViewFocus_Statics::NewProp_NewFocusedView_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlViewFocus_Statics::NewProp_NewFocusedView_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlViewFocus_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlViewFocus_Statics::NewProp_NewFocusedView,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlViewFocus_Statics::Function_MetaDataParams[] = {
		{ "Category", "Prysm" },
		{ "DisplayName", "SetViewFocus" },
		{ "ModuleRelativePath", "Classes/CohtmlInputActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlViewFocus_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ACohtmlInputActor, nullptr, "SetCohtmlViewFocus", nullptr, nullptr, sizeof(CohtmlInputActor_eventSetCohtmlViewFocus_Parms), Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlViewFocus_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlViewFocus_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlViewFocus_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlViewFocus_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlViewFocus()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlViewFocus_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ACohtmlInputActor_SetInputPropagationBehaviour_Statics
	{
		struct CohtmlInputActor_eventSetInputPropagationBehaviour_Parms
		{
			TEnumAsByte<ECohtmlInputPropagationBehaviour::Type> Propagation;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Propagation;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ACohtmlInputActor_SetInputPropagationBehaviour_Statics::NewProp_Propagation = { "Propagation", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlInputActor_eventSetInputPropagationBehaviour_Parms, Propagation), Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputPropagationBehaviour, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ACohtmlInputActor_SetInputPropagationBehaviour_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACohtmlInputActor_SetInputPropagationBehaviour_Statics::NewProp_Propagation,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ACohtmlInputActor_SetInputPropagationBehaviour_Statics::Function_MetaDataParams[] = {
		{ "Category", "Prysm" },
		{ "ModuleRelativePath", "Classes/CohtmlInputActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ACohtmlInputActor_SetInputPropagationBehaviour_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ACohtmlInputActor, nullptr, "SetInputPropagationBehaviour", nullptr, nullptr, sizeof(CohtmlInputActor_eventSetInputPropagationBehaviour_Parms), Z_Construct_UFunction_ACohtmlInputActor_SetInputPropagationBehaviour_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlInputActor_SetInputPropagationBehaviour_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ACohtmlInputActor_SetInputPropagationBehaviour_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlInputActor_SetInputPropagationBehaviour_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ACohtmlInputActor_SetInputPropagationBehaviour()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ACohtmlInputActor_SetInputPropagationBehaviour_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ACohtmlInputActor_SetLineTraceMode_Statics
	{
		struct CohtmlInputActor_eventSetLineTraceMode_Parms
		{
			TEnumAsByte<ECohtmlInputWidgetLineTraceMode> Mode;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Mode;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ACohtmlInputActor_SetLineTraceMode_Statics::NewProp_Mode = { "Mode", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CohtmlInputActor_eventSetLineTraceMode_Parms, Mode), Z_Construct_UEnum_CohtmlPlugin_ECohtmlInputWidgetLineTraceMode, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ACohtmlInputActor_SetLineTraceMode_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ACohtmlInputActor_SetLineTraceMode_Statics::NewProp_Mode,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ACohtmlInputActor_SetLineTraceMode_Statics::Function_MetaDataParams[] = {
		{ "Category", "Prysm" },
		{ "ModuleRelativePath", "Classes/CohtmlInputActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ACohtmlInputActor_SetLineTraceMode_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ACohtmlInputActor, nullptr, "SetLineTraceMode", nullptr, nullptr, sizeof(CohtmlInputActor_eventSetLineTraceMode_Parms), Z_Construct_UFunction_ACohtmlInputActor_SetLineTraceMode_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlInputActor_SetLineTraceMode_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ACohtmlInputActor_SetLineTraceMode_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlInputActor_SetLineTraceMode_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ACohtmlInputActor_SetLineTraceMode()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ACohtmlInputActor_SetLineTraceMode_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ACohtmlInputActor_ToggleCohtmlInputFocus_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ACohtmlInputActor_ToggleCohtmlInputFocus_Statics::Function_MetaDataParams[] = {
		{ "Category", "Prysm" },
		{ "DisplayName", "ToggleInputFocus" },
		{ "ModuleRelativePath", "Classes/CohtmlInputActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ACohtmlInputActor_ToggleCohtmlInputFocus_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ACohtmlInputActor, nullptr, "ToggleCohtmlInputFocus", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ACohtmlInputActor_ToggleCohtmlInputFocus_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ACohtmlInputActor_ToggleCohtmlInputFocus_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ACohtmlInputActor_ToggleCohtmlInputFocus()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ACohtmlInputActor_ToggleCohtmlInputFocus_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ACohtmlInputActor_NoRegister()
	{
		return ACohtmlInputActor::StaticClass();
	}
	struct Z_Construct_UClass_ACohtmlInputActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnCohtmlInputActorKeyUp_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnCohtmlInputActorKeyUp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnCohtmlInputActorKeyDown_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnCohtmlInputActorKeyDown;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnCohtmlInputActorMouseButtonUp_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnCohtmlInputActorMouseButtonUp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnCohtmlInputActorMouseButtonDown_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnCohtmlInputActorMouseButtonDown;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ACohtmlInputActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_CohtmlPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ACohtmlInputActor_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ACohtmlInputActor_AlwaysAcceptMouseInput, "AlwaysAcceptMouseInput" }, // 2870204246
		{ &Z_Construct_UFunction_ACohtmlInputActor_GetInputPropagationBehaviour, "GetInputPropagationBehaviour" }, // 1250430517
		{ &Z_Construct_UFunction_ACohtmlInputActor_Initialize, "Initialize" }, // 1143446317
		{ &Z_Construct_UFunction_ACohtmlInputActor_IsCohtmlFocused, "IsCohtmlFocused" }, // 1268511756
		{ &Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlInputFocus, "SetCohtmlInputFocus" }, // 597260253
		{ &Z_Construct_UFunction_ACohtmlInputActor_SetCohtmlViewFocus, "SetCohtmlViewFocus" }, // 4235063835
		{ &Z_Construct_UFunction_ACohtmlInputActor_SetInputPropagationBehaviour, "SetInputPropagationBehaviour" }, // 3599901922
		{ &Z_Construct_UFunction_ACohtmlInputActor_SetLineTraceMode, "SetLineTraceMode" }, // 3745848675
		{ &Z_Construct_UFunction_ACohtmlInputActor_ToggleCohtmlInputFocus, "ToggleCohtmlInputFocus" }, // 721954062
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACohtmlInputActor_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "DisplayName", "Prysm Input Actor" },
		{ "IncludePath", "CohtmlInputActor.h" },
		{ "ModuleRelativePath", "Classes/CohtmlInputActor.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACohtmlInputActor_Statics::NewProp_OnCohtmlInputActorKeyUp_MetaData[] = {
		{ "Category", "Prysm" },
		{ "DisplayName", "OnInputActorKeyUp" },
		{ "ModuleRelativePath", "Classes/CohtmlInputActor.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_ACohtmlInputActor_Statics::NewProp_OnCohtmlInputActorKeyUp = { "OnCohtmlInputActorKeyUp", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ACohtmlInputActor, OnCohtmlInputActorKeyUp), Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyUp__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_ACohtmlInputActor_Statics::NewProp_OnCohtmlInputActorKeyUp_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ACohtmlInputActor_Statics::NewProp_OnCohtmlInputActorKeyUp_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACohtmlInputActor_Statics::NewProp_OnCohtmlInputActorKeyDown_MetaData[] = {
		{ "Category", "Prysm" },
		{ "DisplayName", "OnInputActorKeyDown" },
		{ "ModuleRelativePath", "Classes/CohtmlInputActor.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_ACohtmlInputActor_Statics::NewProp_OnCohtmlInputActorKeyDown = { "OnCohtmlInputActorKeyDown", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ACohtmlInputActor, OnCohtmlInputActorKeyDown), Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorKeyDown__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_ACohtmlInputActor_Statics::NewProp_OnCohtmlInputActorKeyDown_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ACohtmlInputActor_Statics::NewProp_OnCohtmlInputActorKeyDown_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACohtmlInputActor_Statics::NewProp_OnCohtmlInputActorMouseButtonUp_MetaData[] = {
		{ "Category", "Prysm" },
		{ "DisplayName", "OnInputActorMouseButtonUp" },
		{ "ModuleRelativePath", "Classes/CohtmlInputActor.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_ACohtmlInputActor_Statics::NewProp_OnCohtmlInputActorMouseButtonUp = { "OnCohtmlInputActorMouseButtonUp", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ACohtmlInputActor, OnCohtmlInputActorMouseButtonUp), Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonUp__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_ACohtmlInputActor_Statics::NewProp_OnCohtmlInputActorMouseButtonUp_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ACohtmlInputActor_Statics::NewProp_OnCohtmlInputActorMouseButtonUp_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACohtmlInputActor_Statics::NewProp_OnCohtmlInputActorMouseButtonDown_MetaData[] = {
		{ "Category", "Prysm" },
		{ "DisplayName", "OnInputActorMouseButtonDown" },
		{ "ModuleRelativePath", "Classes/CohtmlInputActor.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_ACohtmlInputActor_Statics::NewProp_OnCohtmlInputActorMouseButtonDown = { "OnCohtmlInputActorMouseButtonDown", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ACohtmlInputActor, OnCohtmlInputActorMouseButtonDown), Z_Construct_UDelegateFunction_CohtmlPlugin_CohtmlInputActorMouseButtonDown__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_ACohtmlInputActor_Statics::NewProp_OnCohtmlInputActorMouseButtonDown_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ACohtmlInputActor_Statics::NewProp_OnCohtmlInputActorMouseButtonDown_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ACohtmlInputActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACohtmlInputActor_Statics::NewProp_OnCohtmlInputActorKeyUp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACohtmlInputActor_Statics::NewProp_OnCohtmlInputActorKeyDown,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACohtmlInputActor_Statics::NewProp_OnCohtmlInputActorMouseButtonUp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACohtmlInputActor_Statics::NewProp_OnCohtmlInputActorMouseButtonDown,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ACohtmlInputActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACohtmlInputActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ACohtmlInputActor_Statics::ClassParams = {
		&ACohtmlInputActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ACohtmlInputActor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ACohtmlInputActor_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ACohtmlInputActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ACohtmlInputActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ACohtmlInputActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ACohtmlInputActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ACohtmlInputActor, 2279771942);
	template<> COHTMLPLUGIN_API UClass* StaticClass<ACohtmlInputActor>()
	{
		return ACohtmlInputActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ACohtmlInputActor(Z_Construct_UClass_ACohtmlInputActor, &ACohtmlInputActor::StaticClass, TEXT("/Script/CohtmlPlugin"), TEXT("ACohtmlInputActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACohtmlInputActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
