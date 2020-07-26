// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UObject;
class UCohtmlJSEvent;
struct FSoundAttenuationSettings;
class UStructProperty;
#ifdef COHTMLPLUGIN_CohtmlBaseComponent_generated_h
#error "CohtmlBaseComponent.generated.h already included, missing '#pragma once' in CohtmlBaseComponent.h"
#endif
#define COHTMLPLUGIN_CohtmlBaseComponent_generated_h

#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_59_SPARSE_DATA
#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_59_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSynchronizeModels) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SynchronizeModels(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUpdateWholeDataModelFromObject) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_Model); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->UpdateWholeDataModelFromObject(Z_Param_Model); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCreateDataModelFromObject) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Name); \
		P_GET_OBJECT(UObject,Z_Param_Model); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->CreateDataModelFromObject(Z_Param_Name,Z_Param_Model); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execTriggerJSEvent) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_name); \
		P_GET_OBJECT(UCohtmlJSEvent,Z_Param_eventData); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->TriggerJSEvent(Z_Param_name,Z_Param_eventData); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCreateJSEvent) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(UCohtmlJSEvent**)Z_Param__Result=P_THIS->CreateJSEvent(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execEnableDelayedUpdate) \
	{ \
		P_GET_UBOOL(Z_Param_bEnabled); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->EnableDelayedUpdate(Z_Param_bEnabled); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execEndDebugFrameSave) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->EndDebugFrameSave(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execBeginDebugFrameSave) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->BeginDebugFrameSave(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execDebugSaveNextFrame) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->DebugSaveNextFrame(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execReload) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->Reload(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoad) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_path); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->Load(Z_Param_path); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execShowPaintRects) \
	{ \
		P_GET_UBOOL(Z_Param_show); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->ShowPaintRects(Z_Param_show); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execHasRequestedView) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->HasRequestedView(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsReadyForBindings) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->IsReadyForBindings(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsReadyToCreateView) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->IsReadyToCreateView(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execResize) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_width); \
		P_GET_PROPERTY(UIntProperty,Z_Param_height); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->Resize(Z_Param_width,Z_Param_height); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetSoundAttenuation) \
	{ \
		P_GET_STRUCT_REF(FSoundAttenuationSettings,Z_Param_Out_Settings); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetSoundAttenuation(Z_Param_Out_Settings); \
		P_NATIVE_END; \
	}


#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_59_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSynchronizeModels) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SynchronizeModels(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUpdateWholeDataModelFromObject) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_Model); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->UpdateWholeDataModelFromObject(Z_Param_Model); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCreateDataModelFromObject) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Name); \
		P_GET_OBJECT(UObject,Z_Param_Model); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->CreateDataModelFromObject(Z_Param_Name,Z_Param_Model); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execTriggerJSEvent) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_name); \
		P_GET_OBJECT(UCohtmlJSEvent,Z_Param_eventData); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->TriggerJSEvent(Z_Param_name,Z_Param_eventData); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCreateJSEvent) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(UCohtmlJSEvent**)Z_Param__Result=P_THIS->CreateJSEvent(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execEnableDelayedUpdate) \
	{ \
		P_GET_UBOOL(Z_Param_bEnabled); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->EnableDelayedUpdate(Z_Param_bEnabled); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execEndDebugFrameSave) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->EndDebugFrameSave(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execBeginDebugFrameSave) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->BeginDebugFrameSave(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execDebugSaveNextFrame) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->DebugSaveNextFrame(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execReload) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->Reload(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoad) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_path); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->Load(Z_Param_path); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execShowPaintRects) \
	{ \
		P_GET_UBOOL(Z_Param_show); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->ShowPaintRects(Z_Param_show); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execHasRequestedView) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->HasRequestedView(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsReadyForBindings) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->IsReadyForBindings(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsReadyToCreateView) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->IsReadyToCreateView(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execResize) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_width); \
		P_GET_PROPERTY(UIntProperty,Z_Param_height); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->Resize(Z_Param_width,Z_Param_height); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetSoundAttenuation) \
	{ \
		P_GET_STRUCT_REF(FSoundAttenuationSettings,Z_Param_Out_Settings); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetSoundAttenuation(Z_Param_Out_Settings); \
		P_NATIVE_END; \
	}


#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_59_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCohtmlBaseComponent(); \
	friend struct Z_Construct_UClass_UCohtmlBaseComponent_Statics; \
public: \
	DECLARE_CLASS(UCohtmlBaseComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/CohtmlPlugin"), NO_API) \
	DECLARE_SERIALIZER(UCohtmlBaseComponent)


#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_59_INCLASS \
private: \
	static void StaticRegisterNativesUCohtmlBaseComponent(); \
	friend struct Z_Construct_UClass_UCohtmlBaseComponent_Statics; \
public: \
	DECLARE_CLASS(UCohtmlBaseComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/CohtmlPlugin"), NO_API) \
	DECLARE_SERIALIZER(UCohtmlBaseComponent)


#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_59_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCohtmlBaseComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCohtmlBaseComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCohtmlBaseComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCohtmlBaseComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCohtmlBaseComponent(UCohtmlBaseComponent&&); \
	NO_API UCohtmlBaseComponent(const UCohtmlBaseComponent&); \
public:


#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_59_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCohtmlBaseComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCohtmlBaseComponent(UCohtmlBaseComponent&&); \
	NO_API UCohtmlBaseComponent(const UCohtmlBaseComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCohtmlBaseComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCohtmlBaseComponent); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCohtmlBaseComponent)


#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_59_PRIVATE_PROPERTY_OFFSET
#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_56_PROLOG
#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_59_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_59_PRIVATE_PROPERTY_OFFSET \
	CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_59_SPARSE_DATA \
	CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_59_RPC_WRAPPERS \
	CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_59_INCLASS \
	CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_59_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_59_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_59_PRIVATE_PROPERTY_OFFSET \
	CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_59_SPARSE_DATA \
	CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_59_RPC_WRAPPERS_NO_PURE_DECLS \
	CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_59_INCLASS_NO_PURE_DECLS \
	CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h_59_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class CohtmlBaseComponent."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> COHTMLPLUGIN_API UClass* StaticClass<class UCohtmlBaseComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID CoherentTest_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlBaseComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
