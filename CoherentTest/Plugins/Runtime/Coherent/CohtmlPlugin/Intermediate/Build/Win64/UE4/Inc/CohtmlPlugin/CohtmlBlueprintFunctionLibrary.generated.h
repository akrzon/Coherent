// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UCohtmlBaseComponent;
class UCohtmlJSEvent;
class UObject;
class UStructProperty;
#ifdef COHTMLPLUGIN_CohtmlBlueprintFunctionLibrary_generated_h
#error "CohtmlBlueprintFunctionLibrary.generated.h already included, missing '#pragma once' in CohtmlBlueprintFunctionLibrary.h"
#endif
#define COHTMLPLUGIN_CohtmlBlueprintFunctionLibrary_generated_h

#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_49_SPARSE_DATA
#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_49_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execTriggerJSEvent) \
	{ \
		P_GET_OBJECT(UCohtmlBaseComponent,Z_Param_Component); \
		P_GET_PROPERTY(UStrProperty,Z_Param_EventName); \
		P_GET_OBJECT(UCohtmlJSEvent,Z_Param_JSEvent); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UCohtmlBlueprintFunctionLibrary::TriggerJSEvent(Z_Param_Component,Z_Param_EventName,Z_Param_JSEvent); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddArray) \
	{ \
		P_GET_OBJECT(UCohtmlJSEvent,Z_Param_JSEvent); \
		P_GET_TARRAY_REF(int32,Z_Param_Out_Arg); \
		P_GET_PROPERTY(UIntProperty,Z_Param_ArrayType); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UCohtmlBlueprintFunctionLibrary::AddArray(Z_Param_JSEvent,Z_Param_Out_Arg,Z_Param_ArrayType); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddObject) \
	{ \
		P_GET_OBJECT(UCohtmlJSEvent,Z_Param_JSEvent); \
		P_GET_OBJECT(UObject,Z_Param_Arg); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UCohtmlBlueprintFunctionLibrary::AddObject(Z_Param_JSEvent,Z_Param_Arg); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddBool) \
	{ \
		P_GET_OBJECT(UCohtmlJSEvent,Z_Param_JSEvent); \
		P_GET_UBOOL(Z_Param_Arg); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UCohtmlBlueprintFunctionLibrary::AddBool(Z_Param_JSEvent,Z_Param_Arg); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddFloat) \
	{ \
		P_GET_OBJECT(UCohtmlJSEvent,Z_Param_JSEvent); \
		P_GET_PROPERTY(UFloatProperty,Z_Param_Arg); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UCohtmlBlueprintFunctionLibrary::AddFloat(Z_Param_JSEvent,Z_Param_Arg); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddString) \
	{ \
		P_GET_OBJECT(UCohtmlJSEvent,Z_Param_JSEvent); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Arg); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UCohtmlBlueprintFunctionLibrary::AddString(Z_Param_JSEvent,Z_Param_Arg); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddInt32) \
	{ \
		P_GET_OBJECT(UCohtmlJSEvent,Z_Param_JSEvent); \
		P_GET_PROPERTY(UIntProperty,Z_Param_Arg); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UCohtmlBlueprintFunctionLibrary::AddInt32(Z_Param_JSEvent,Z_Param_Arg); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddByte) \
	{ \
		P_GET_OBJECT(UCohtmlJSEvent,Z_Param_JSEvent); \
		P_GET_PROPERTY(UByteProperty,Z_Param_Arg); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UCohtmlBlueprintFunctionLibrary::AddByte(Z_Param_JSEvent,Z_Param_Arg); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCreateJSEvent) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(UCohtmlJSEvent**)Z_Param__Result=UCohtmlBlueprintFunctionLibrary::CreateJSEvent(Z_Param_WorldContextObject); \
		P_NATIVE_END; \
	}


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_49_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execTriggerJSEvent) \
	{ \
		P_GET_OBJECT(UCohtmlBaseComponent,Z_Param_Component); \
		P_GET_PROPERTY(UStrProperty,Z_Param_EventName); \
		P_GET_OBJECT(UCohtmlJSEvent,Z_Param_JSEvent); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UCohtmlBlueprintFunctionLibrary::TriggerJSEvent(Z_Param_Component,Z_Param_EventName,Z_Param_JSEvent); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddArray) \
	{ \
		P_GET_OBJECT(UCohtmlJSEvent,Z_Param_JSEvent); \
		P_GET_TARRAY_REF(int32,Z_Param_Out_Arg); \
		P_GET_PROPERTY(UIntProperty,Z_Param_ArrayType); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UCohtmlBlueprintFunctionLibrary::AddArray(Z_Param_JSEvent,Z_Param_Out_Arg,Z_Param_ArrayType); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddObject) \
	{ \
		P_GET_OBJECT(UCohtmlJSEvent,Z_Param_JSEvent); \
		P_GET_OBJECT(UObject,Z_Param_Arg); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UCohtmlBlueprintFunctionLibrary::AddObject(Z_Param_JSEvent,Z_Param_Arg); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddBool) \
	{ \
		P_GET_OBJECT(UCohtmlJSEvent,Z_Param_JSEvent); \
		P_GET_UBOOL(Z_Param_Arg); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UCohtmlBlueprintFunctionLibrary::AddBool(Z_Param_JSEvent,Z_Param_Arg); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddFloat) \
	{ \
		P_GET_OBJECT(UCohtmlJSEvent,Z_Param_JSEvent); \
		P_GET_PROPERTY(UFloatProperty,Z_Param_Arg); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UCohtmlBlueprintFunctionLibrary::AddFloat(Z_Param_JSEvent,Z_Param_Arg); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddString) \
	{ \
		P_GET_OBJECT(UCohtmlJSEvent,Z_Param_JSEvent); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Arg); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UCohtmlBlueprintFunctionLibrary::AddString(Z_Param_JSEvent,Z_Param_Arg); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddInt32) \
	{ \
		P_GET_OBJECT(UCohtmlJSEvent,Z_Param_JSEvent); \
		P_GET_PROPERTY(UIntProperty,Z_Param_Arg); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UCohtmlBlueprintFunctionLibrary::AddInt32(Z_Param_JSEvent,Z_Param_Arg); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddByte) \
	{ \
		P_GET_OBJECT(UCohtmlJSEvent,Z_Param_JSEvent); \
		P_GET_PROPERTY(UByteProperty,Z_Param_Arg); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UCohtmlBlueprintFunctionLibrary::AddByte(Z_Param_JSEvent,Z_Param_Arg); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCreateJSEvent) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(UCohtmlJSEvent**)Z_Param__Result=UCohtmlBlueprintFunctionLibrary::CreateJSEvent(Z_Param_WorldContextObject); \
		P_NATIVE_END; \
	}


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_49_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCohtmlBlueprintFunctionLibrary(); \
	friend struct Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary_Statics; \
public: \
	DECLARE_CLASS(UCohtmlBlueprintFunctionLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CohtmlPlugin"), NO_API) \
	DECLARE_SERIALIZER(UCohtmlBlueprintFunctionLibrary)


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_49_INCLASS \
private: \
	static void StaticRegisterNativesUCohtmlBlueprintFunctionLibrary(); \
	friend struct Z_Construct_UClass_UCohtmlBlueprintFunctionLibrary_Statics; \
public: \
	DECLARE_CLASS(UCohtmlBlueprintFunctionLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CohtmlPlugin"), NO_API) \
	DECLARE_SERIALIZER(UCohtmlBlueprintFunctionLibrary)


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_49_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCohtmlBlueprintFunctionLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCohtmlBlueprintFunctionLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCohtmlBlueprintFunctionLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCohtmlBlueprintFunctionLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCohtmlBlueprintFunctionLibrary(UCohtmlBlueprintFunctionLibrary&&); \
	NO_API UCohtmlBlueprintFunctionLibrary(const UCohtmlBlueprintFunctionLibrary&); \
public:


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_49_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCohtmlBlueprintFunctionLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCohtmlBlueprintFunctionLibrary(UCohtmlBlueprintFunctionLibrary&&); \
	NO_API UCohtmlBlueprintFunctionLibrary(const UCohtmlBlueprintFunctionLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCohtmlBlueprintFunctionLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCohtmlBlueprintFunctionLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCohtmlBlueprintFunctionLibrary)


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_49_PRIVATE_PROPERTY_OFFSET
#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_46_PROLOG
#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_49_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_49_PRIVATE_PROPERTY_OFFSET \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_49_SPARSE_DATA \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_49_RPC_WRAPPERS \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_49_INCLASS \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_49_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_49_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_49_PRIVATE_PROPERTY_OFFSET \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_49_SPARSE_DATA \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_49_RPC_WRAPPERS_NO_PURE_DECLS \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_49_INCLASS_NO_PURE_DECLS \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h_49_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class CohtmlBlueprintFunctionLibrary."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> COHTMLPLUGIN_API UClass* StaticClass<class UCohtmlBlueprintFunctionLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBlueprintFunctionLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
