// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UCohtmlBaseComponent;
#ifdef COHTMLPLUGIN_CohtmlEventHelpers_generated_h
#error "CohtmlEventHelpers.generated.h already included, missing '#pragma once' in CohtmlEventHelpers.h"
#endif
#define COHTMLPLUGIN_CohtmlEventHelpers_generated_h

#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_45_DELEGATE \
struct _Script_CohtmlPlugin_eventCohtmlOnLiveViewSizeRequest_Parms \
{ \
	UCohtmlBaseComponent* compo; \
	FString name; \
	int32 width; \
	int32 height; \
}; \
static inline void FCohtmlOnLiveViewSizeRequest_DelegateWrapper(const FScriptDelegate& CohtmlOnLiveViewSizeRequest, UCohtmlBaseComponent* compo, const FString& name, int32& width, int32& height) \
{ \
	_Script_CohtmlPlugin_eventCohtmlOnLiveViewSizeRequest_Parms Parms; \
	Parms.compo=compo; \
	Parms.name=name; \
	Parms.width=width; \
	Parms.height=height; \
	CohtmlOnLiveViewSizeRequest.ProcessDelegate<UObject>(&Parms); \
	width=Parms.width; \
	height=Parms.height; \
}


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_44_DELEGATE \
static inline void FCohtmlScriptingReady_DelegateWrapper(const FMulticastScriptDelegate& CohtmlScriptingReady) \
{ \
	CohtmlScriptingReady.ProcessMulticastDelegate<UObject>(NULL); \
}


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_43_DELEGATE \
static inline void FCohtmlBindingsReleasedSignature_DelegateWrapper(const FMulticastScriptDelegate& CohtmlBindingsReleasedSignature) \
{ \
	CohtmlBindingsReleasedSignature.ProcessMulticastDelegate<UObject>(NULL); \
}


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_42_DELEGATE \
static inline void FCohtmlReadyForBindingsSignature_DelegateWrapper(const FMulticastScriptDelegate& CohtmlReadyForBindingsSignature) \
{ \
	CohtmlReadyForBindingsSignature.ProcessMulticastDelegate<UObject>(NULL); \
}


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_82_SPARSE_DATA
#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_82_RPC_WRAPPERS
#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_82_RPC_WRAPPERS_NO_PURE_DECLS
#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_82_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCohtmlEventHelpers(); \
	friend struct Z_Construct_UClass_UCohtmlEventHelpers_Statics; \
public: \
	DECLARE_CLASS(UCohtmlEventHelpers, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CohtmlPlugin"), NO_API) \
	DECLARE_SERIALIZER(UCohtmlEventHelpers)


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_82_INCLASS \
private: \
	static void StaticRegisterNativesUCohtmlEventHelpers(); \
	friend struct Z_Construct_UClass_UCohtmlEventHelpers_Statics; \
public: \
	DECLARE_CLASS(UCohtmlEventHelpers, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CohtmlPlugin"), NO_API) \
	DECLARE_SERIALIZER(UCohtmlEventHelpers)


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_82_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCohtmlEventHelpers(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCohtmlEventHelpers) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCohtmlEventHelpers); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCohtmlEventHelpers); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCohtmlEventHelpers(UCohtmlEventHelpers&&); \
	NO_API UCohtmlEventHelpers(const UCohtmlEventHelpers&); \
public:


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_82_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCohtmlEventHelpers(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCohtmlEventHelpers(UCohtmlEventHelpers&&); \
	NO_API UCohtmlEventHelpers(const UCohtmlEventHelpers&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCohtmlEventHelpers); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCohtmlEventHelpers); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCohtmlEventHelpers)


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_82_PRIVATE_PROPERTY_OFFSET
#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_79_PROLOG
#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_82_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_82_PRIVATE_PROPERTY_OFFSET \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_82_SPARSE_DATA \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_82_RPC_WRAPPERS \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_82_INCLASS \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_82_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_82_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_82_PRIVATE_PROPERTY_OFFSET \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_82_SPARSE_DATA \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_82_RPC_WRAPPERS_NO_PURE_DECLS \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_82_INCLASS_NO_PURE_DECLS \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h_82_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class CohtmlEventHelpers."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> COHTMLPLUGIN_API UClass* StaticClass<class UCohtmlEventHelpers>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlEventHelpers_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
