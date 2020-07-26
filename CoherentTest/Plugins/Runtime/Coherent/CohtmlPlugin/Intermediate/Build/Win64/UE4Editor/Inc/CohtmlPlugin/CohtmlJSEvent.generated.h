// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UObject;
class UStructProperty;
#ifdef COHTMLPLUGIN_CohtmlJSEvent_generated_h
#error "CohtmlJSEvent.generated.h already included, missing '#pragma once' in CohtmlJSEvent.h"
#endif
#define COHTMLPLUGIN_CohtmlJSEvent_generated_h

#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_53_SPARSE_DATA
#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_53_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execAddObject) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_object); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->AddObject(Z_Param_object); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddBool) \
	{ \
		P_GET_UBOOL(Z_Param_b); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->AddBool(Z_Param_b); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddFloat) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_fl); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->AddFloat(Z_Param_fl); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddText) \
	{ \
		P_GET_PROPERTY_REF(UTextProperty,Z_Param_Out_text); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->AddText(Z_Param_Out_text); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddName) \
	{ \
		P_GET_PROPERTY_REF(UNameProperty,Z_Param_Out_name); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->AddName(Z_Param_Out_name); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddString) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_str); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->AddString(Z_Param_str); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddInt32) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_integer); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->AddInt32(Z_Param_integer); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddByte) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_byte); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->AddByte(Z_Param_byte); \
		P_NATIVE_END; \
	}


#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_53_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execAddObject) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_object); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->AddObject(Z_Param_object); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddBool) \
	{ \
		P_GET_UBOOL(Z_Param_b); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->AddBool(Z_Param_b); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddFloat) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_fl); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->AddFloat(Z_Param_fl); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddText) \
	{ \
		P_GET_PROPERTY_REF(UTextProperty,Z_Param_Out_text); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->AddText(Z_Param_Out_text); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddName) \
	{ \
		P_GET_PROPERTY_REF(UNameProperty,Z_Param_Out_name); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->AddName(Z_Param_Out_name); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddString) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_str); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->AddString(Z_Param_str); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddInt32) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_integer); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->AddInt32(Z_Param_integer); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddByte) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_byte); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->AddByte(Z_Param_byte); \
		P_NATIVE_END; \
	}


#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_53_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCohtmlJSEvent(); \
	friend struct Z_Construct_UClass_UCohtmlJSEvent_Statics; \
public: \
	DECLARE_CLASS(UCohtmlJSEvent, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CohtmlPlugin"), NO_API) \
	DECLARE_SERIALIZER(UCohtmlJSEvent)


#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_53_INCLASS \
private: \
	static void StaticRegisterNativesUCohtmlJSEvent(); \
	friend struct Z_Construct_UClass_UCohtmlJSEvent_Statics; \
public: \
	DECLARE_CLASS(UCohtmlJSEvent, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CohtmlPlugin"), NO_API) \
	DECLARE_SERIALIZER(UCohtmlJSEvent)


#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_53_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCohtmlJSEvent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCohtmlJSEvent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCohtmlJSEvent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCohtmlJSEvent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCohtmlJSEvent(UCohtmlJSEvent&&); \
	NO_API UCohtmlJSEvent(const UCohtmlJSEvent&); \
public:


#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_53_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCohtmlJSEvent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCohtmlJSEvent(UCohtmlJSEvent&&); \
	NO_API UCohtmlJSEvent(const UCohtmlJSEvent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCohtmlJSEvent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCohtmlJSEvent); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCohtmlJSEvent)


#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_53_PRIVATE_PROPERTY_OFFSET
#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_50_PROLOG
#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_53_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_53_PRIVATE_PROPERTY_OFFSET \
	CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_53_SPARSE_DATA \
	CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_53_RPC_WRAPPERS \
	CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_53_INCLASS \
	CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_53_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_53_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_53_PRIVATE_PROPERTY_OFFSET \
	CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_53_SPARSE_DATA \
	CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_53_RPC_WRAPPERS_NO_PURE_DECLS \
	CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_53_INCLASS_NO_PURE_DECLS \
	CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h_53_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class CohtmlJSEvent."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> COHTMLPLUGIN_API UClass* StaticClass<class UCohtmlJSEvent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlJSEvent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
