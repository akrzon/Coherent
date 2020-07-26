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
class UTextureRenderTarget2D;
struct FSoundAttenuationSettings;
class UStructProperty;
#ifdef COHTMLPLUGIN_CohtmlWidget_generated_h
#error "CohtmlWidget.generated.h already included, missing '#pragma once' in CohtmlWidget.h"
#endif
#define COHTMLPLUGIN_CohtmlWidget_generated_h

#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_59_SPARSE_DATA
#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_59_RPC_WRAPPERS \
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
	DECLARE_FUNCTION(execGetRenderTexture) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(UTextureRenderTarget2D**)Z_Param__Result=P_THIS->GetRenderTexture(); \
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
	DECLARE_FUNCTION(execGetInputPropagationBehaviour) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(TEnumAsByte<ECohtmlInputPropagationBehaviour::Type>*)Z_Param__Result=P_THIS->GetInputPropagationBehaviour(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetInputPropagationBehaviour) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_Propagation); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetInputPropagationBehaviour(ECohtmlInputPropagationBehaviour::Type(Z_Param_Propagation)); \
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


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_59_RPC_WRAPPERS_NO_PURE_DECLS \
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
	DECLARE_FUNCTION(execGetRenderTexture) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(UTextureRenderTarget2D**)Z_Param__Result=P_THIS->GetRenderTexture(); \
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
	DECLARE_FUNCTION(execGetInputPropagationBehaviour) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(TEnumAsByte<ECohtmlInputPropagationBehaviour::Type>*)Z_Param__Result=P_THIS->GetInputPropagationBehaviour(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetInputPropagationBehaviour) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_Propagation); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetInputPropagationBehaviour(ECohtmlInputPropagationBehaviour::Type(Z_Param_Propagation)); \
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


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_59_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCohtmlWidget(); \
	friend struct Z_Construct_UClass_UCohtmlWidget_Statics; \
public: \
	DECLARE_CLASS(UCohtmlWidget, UWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CohtmlPlugin"), NO_API) \
	DECLARE_SERIALIZER(UCohtmlWidget)


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_59_INCLASS \
private: \
	static void StaticRegisterNativesUCohtmlWidget(); \
	friend struct Z_Construct_UClass_UCohtmlWidget_Statics; \
public: \
	DECLARE_CLASS(UCohtmlWidget, UWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CohtmlPlugin"), NO_API) \
	DECLARE_SERIALIZER(UCohtmlWidget)


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_59_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCohtmlWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCohtmlWidget) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCohtmlWidget); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCohtmlWidget); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCohtmlWidget(UCohtmlWidget&&); \
	NO_API UCohtmlWidget(const UCohtmlWidget&); \
public:


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_59_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCohtmlWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCohtmlWidget(UCohtmlWidget&&); \
	NO_API UCohtmlWidget(const UCohtmlWidget&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCohtmlWidget); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCohtmlWidget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCohtmlWidget)


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_59_PRIVATE_PROPERTY_OFFSET
#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_56_PROLOG
#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_59_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_59_PRIVATE_PROPERTY_OFFSET \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_59_SPARSE_DATA \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_59_RPC_WRAPPERS \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_59_INCLASS \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_59_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_59_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_59_PRIVATE_PROPERTY_OFFSET \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_59_SPARSE_DATA \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_59_RPC_WRAPPERS_NO_PURE_DECLS \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_59_INCLASS_NO_PURE_DECLS \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h_59_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class CohtmlWidget."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> COHTMLPLUGIN_API UClass* StaticClass<class UCohtmlWidget>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlWidget_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
