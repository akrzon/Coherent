// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef COHTMLPLUGIN_CohtmlGameHUD_generated_h
#error "CohtmlGameHUD.generated.h already included, missing '#pragma once' in CohtmlGameHUD.h"
#endif
#define COHTMLPLUGIN_CohtmlGameHUD_generated_h

#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_54_SPARSE_DATA
#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_54_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSetupView) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_PageUrl); \
		P_GET_UBOOL(Z_Param_bEnableComplexCSSSupport); \
		P_GET_UBOOL(Z_Param_bDelayedUpdate); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetupView(Z_Param_PageUrl,Z_Param_bEnableComplexCSSSupport,Z_Param_bDelayedUpdate); \
		P_NATIVE_END; \
	}


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_54_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSetupView) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_PageUrl); \
		P_GET_UBOOL(Z_Param_bEnableComplexCSSSupport); \
		P_GET_UBOOL(Z_Param_bDelayedUpdate); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetupView(Z_Param_PageUrl,Z_Param_bEnableComplexCSSSupport,Z_Param_bDelayedUpdate); \
		P_NATIVE_END; \
	}


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_54_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesACohtmlGameHUD(); \
	friend struct Z_Construct_UClass_ACohtmlGameHUD_Statics; \
public: \
	DECLARE_CLASS(ACohtmlGameHUD, AHUD, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/CohtmlPlugin"), COHTMLPLUGIN_API) \
	DECLARE_SERIALIZER(ACohtmlGameHUD)


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_54_INCLASS \
private: \
	static void StaticRegisterNativesACohtmlGameHUD(); \
	friend struct Z_Construct_UClass_ACohtmlGameHUD_Statics; \
public: \
	DECLARE_CLASS(ACohtmlGameHUD, AHUD, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/CohtmlPlugin"), COHTMLPLUGIN_API) \
	DECLARE_SERIALIZER(ACohtmlGameHUD)


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_54_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	COHTMLPLUGIN_API ACohtmlGameHUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ACohtmlGameHUD) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(COHTMLPLUGIN_API, ACohtmlGameHUD); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ACohtmlGameHUD); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	COHTMLPLUGIN_API ACohtmlGameHUD(ACohtmlGameHUD&&); \
	COHTMLPLUGIN_API ACohtmlGameHUD(const ACohtmlGameHUD&); \
public:


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_54_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	COHTMLPLUGIN_API ACohtmlGameHUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	COHTMLPLUGIN_API ACohtmlGameHUD(ACohtmlGameHUD&&); \
	COHTMLPLUGIN_API ACohtmlGameHUD(const ACohtmlGameHUD&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(COHTMLPLUGIN_API, ACohtmlGameHUD); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ACohtmlGameHUD); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ACohtmlGameHUD)


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_54_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__CohtmlHUD() { return STRUCT_OFFSET(ACohtmlGameHUD, CohtmlHUD); } \
	FORCEINLINE static uint32 __PPO__CohtmlHUDInternal() { return STRUCT_OFFSET(ACohtmlGameHUD, CohtmlHUDInternal); }


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_51_PROLOG
#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_54_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_54_PRIVATE_PROPERTY_OFFSET \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_54_SPARSE_DATA \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_54_RPC_WRAPPERS \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_54_INCLASS \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_54_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_54_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_54_PRIVATE_PROPERTY_OFFSET \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_54_SPARSE_DATA \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_54_RPC_WRAPPERS_NO_PURE_DECLS \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_54_INCLASS_NO_PURE_DECLS \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h_54_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class CohtmlGameHUD."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> COHTMLPLUGIN_API UClass* StaticClass<class ACohtmlGameHUD>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlGameHUD_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
