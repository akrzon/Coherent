// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UCohtmlBaseComponent;
#ifdef COHTMLPLUGIN_CohtmlInputActor_generated_h
#error "CohtmlInputActor.generated.h already included, missing '#pragma once' in CohtmlInputActor.h"
#endif
#define COHTMLPLUGIN_CohtmlInputActor_generated_h

#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_179_DELEGATE \
struct _Script_CohtmlPlugin_eventCohtmlInputActorKeyUp_Parms \
{ \
	TEnumAsByte<ECohtmlKeys::Type> Key; \
}; \
static inline void FCohtmlInputActorKeyUp_DelegateWrapper(const FMulticastScriptDelegate& CohtmlInputActorKeyUp, ECohtmlKeys::Type Key) \
{ \
	_Script_CohtmlPlugin_eventCohtmlInputActorKeyUp_Parms Parms; \
	Parms.Key=Key; \
	CohtmlInputActorKeyUp.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_178_DELEGATE \
struct _Script_CohtmlPlugin_eventCohtmlInputActorKeyDown_Parms \
{ \
	TEnumAsByte<ECohtmlKeys::Type> Key; \
}; \
static inline void FCohtmlInputActorKeyDown_DelegateWrapper(const FMulticastScriptDelegate& CohtmlInputActorKeyDown, ECohtmlKeys::Type Key) \
{ \
	_Script_CohtmlPlugin_eventCohtmlInputActorKeyDown_Parms Parms; \
	Parms.Key=Key; \
	CohtmlInputActorKeyDown.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_177_DELEGATE \
struct _Script_CohtmlPlugin_eventCohtmlInputActorMouseButtonUp_Parms \
{ \
	TEnumAsByte<ECohtmlKeys::Type> Button; \
}; \
static inline void FCohtmlInputActorMouseButtonUp_DelegateWrapper(const FMulticastScriptDelegate& CohtmlInputActorMouseButtonUp, ECohtmlKeys::Type Button) \
{ \
	_Script_CohtmlPlugin_eventCohtmlInputActorMouseButtonUp_Parms Parms; \
	Parms.Button=Button; \
	CohtmlInputActorMouseButtonUp.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_176_DELEGATE \
struct _Script_CohtmlPlugin_eventCohtmlInputActorMouseButtonDown_Parms \
{ \
	TEnumAsByte<ECohtmlKeys::Type> Button; \
}; \
static inline void FCohtmlInputActorMouseButtonDown_DelegateWrapper(const FMulticastScriptDelegate& CohtmlInputActorMouseButtonDown, ECohtmlKeys::Type Button) \
{ \
	_Script_CohtmlPlugin_eventCohtmlInputActorMouseButtonDown_Parms Parms; \
	Parms.Button=Button; \
	CohtmlInputActorMouseButtonDown.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_184_SPARSE_DATA
#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_184_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSetLineTraceMode) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_Mode); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetLineTraceMode(ECohtmlInputWidgetLineTraceMode(Z_Param_Mode)); \
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
	DECLARE_FUNCTION(execAlwaysAcceptMouseInput) \
	{ \
		P_GET_UBOOL(Z_Param_bAccept); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->AlwaysAcceptMouseInput(Z_Param_bAccept); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetCohtmlViewFocus) \
	{ \
		P_GET_OBJECT(UCohtmlBaseComponent,Z_Param_NewFocusedView); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetCohtmlViewFocus(Z_Param_NewFocusedView); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execToggleCohtmlInputFocus) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->ToggleCohtmlInputFocus(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsCohtmlFocused) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->IsCohtmlFocused(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetCohtmlInputFocus) \
	{ \
		P_GET_UBOOL(Z_Param_FocusUI); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetCohtmlInputFocus(Z_Param_FocusUI); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execInitialize) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_CollisionChannel); \
		P_GET_PROPERTY(UByteProperty,Z_Param_AddressMode); \
		P_GET_PROPERTY(UByteProperty,Z_Param_RaycastQuality); \
		P_GET_PROPERTY(UIntProperty,Z_Param_UVChannel); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->Initialize(ECollisionChannel(Z_Param_CollisionChannel),TextureAddress(Z_Param_AddressMode),ECohtmlInputWidgetRaycastQuality(Z_Param_RaycastQuality),Z_Param_UVChannel); \
		P_NATIVE_END; \
	}


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_184_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSetLineTraceMode) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_Mode); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetLineTraceMode(ECohtmlInputWidgetLineTraceMode(Z_Param_Mode)); \
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
	DECLARE_FUNCTION(execAlwaysAcceptMouseInput) \
	{ \
		P_GET_UBOOL(Z_Param_bAccept); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->AlwaysAcceptMouseInput(Z_Param_bAccept); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetCohtmlViewFocus) \
	{ \
		P_GET_OBJECT(UCohtmlBaseComponent,Z_Param_NewFocusedView); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetCohtmlViewFocus(Z_Param_NewFocusedView); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execToggleCohtmlInputFocus) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->ToggleCohtmlInputFocus(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsCohtmlFocused) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->IsCohtmlFocused(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetCohtmlInputFocus) \
	{ \
		P_GET_UBOOL(Z_Param_FocusUI); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetCohtmlInputFocus(Z_Param_FocusUI); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execInitialize) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_CollisionChannel); \
		P_GET_PROPERTY(UByteProperty,Z_Param_AddressMode); \
		P_GET_PROPERTY(UByteProperty,Z_Param_RaycastQuality); \
		P_GET_PROPERTY(UIntProperty,Z_Param_UVChannel); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->Initialize(ECollisionChannel(Z_Param_CollisionChannel),TextureAddress(Z_Param_AddressMode),ECohtmlInputWidgetRaycastQuality(Z_Param_RaycastQuality),Z_Param_UVChannel); \
		P_NATIVE_END; \
	}


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_184_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesACohtmlInputActor(); \
	friend struct Z_Construct_UClass_ACohtmlInputActor_Statics; \
public: \
	DECLARE_CLASS(ACohtmlInputActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/CohtmlPlugin"), NO_API) \
	DECLARE_SERIALIZER(ACohtmlInputActor)


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_184_INCLASS \
private: \
	static void StaticRegisterNativesACohtmlInputActor(); \
	friend struct Z_Construct_UClass_ACohtmlInputActor_Statics; \
public: \
	DECLARE_CLASS(ACohtmlInputActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/CohtmlPlugin"), NO_API) \
	DECLARE_SERIALIZER(ACohtmlInputActor)


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_184_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ACohtmlInputActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ACohtmlInputActor) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ACohtmlInputActor); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ACohtmlInputActor); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ACohtmlInputActor(ACohtmlInputActor&&); \
	NO_API ACohtmlInputActor(const ACohtmlInputActor&); \
public:


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_184_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ACohtmlInputActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ACohtmlInputActor(ACohtmlInputActor&&); \
	NO_API ACohtmlInputActor(const ACohtmlInputActor&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ACohtmlInputActor); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ACohtmlInputActor); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ACohtmlInputActor)


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_184_PRIVATE_PROPERTY_OFFSET
#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_181_PROLOG
#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_184_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_184_PRIVATE_PROPERTY_OFFSET \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_184_SPARSE_DATA \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_184_RPC_WRAPPERS \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_184_INCLASS \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_184_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_184_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_184_PRIVATE_PROPERTY_OFFSET \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_184_SPARSE_DATA \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_184_RPC_WRAPPERS_NO_PURE_DECLS \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_184_INCLASS_NO_PURE_DECLS \
	CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h_184_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class CohtmlInputActor."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> COHTMLPLUGIN_API UClass* StaticClass<class ACohtmlInputActor>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID CoherentSample_Plugins_Runtime_Coherent_CohtmlPlugin_Source_CohtmlPlugin_Classes_CohtmlInputActor_h


#define FOREACH_ENUM_ECOHTMLKEYS(op) \
	op(ECohtmlKeys::LeftMouseButton) \
	op(ECohtmlKeys::RightMouseButton) \
	op(ECohtmlKeys::MiddleMouseButton) \
	op(ECohtmlKeys::ThumbMouseButton) \
	op(ECohtmlKeys::ThumbMouseButton2) \
	op(ECohtmlKeys::BackSpace) \
	op(ECohtmlKeys::Tab) \
	op(ECohtmlKeys::Enter) \
	op(ECohtmlKeys::Pause) \
	op(ECohtmlKeys::CapsLock) \
	op(ECohtmlKeys::Escape) \
	op(ECohtmlKeys::SpaceBar) \
	op(ECohtmlKeys::PageUp) \
	op(ECohtmlKeys::PageDown) \
	op(ECohtmlKeys::End) \
	op(ECohtmlKeys::Home) \
	op(ECohtmlKeys::Left) \
	op(ECohtmlKeys::Up) \
	op(ECohtmlKeys::Right) \
	op(ECohtmlKeys::Down) \
	op(ECohtmlKeys::Insert) \
	op(ECohtmlKeys::Delete) \
	op(ECohtmlKeys::Zero) \
	op(ECohtmlKeys::One) \
	op(ECohtmlKeys::Two) \
	op(ECohtmlKeys::Three) \
	op(ECohtmlKeys::Four) \
	op(ECohtmlKeys::Five) \
	op(ECohtmlKeys::Six) \
	op(ECohtmlKeys::Seven) \
	op(ECohtmlKeys::Eight) \
	op(ECohtmlKeys::Nine) \
	op(ECohtmlKeys::A) \
	op(ECohtmlKeys::B) \
	op(ECohtmlKeys::C) \
	op(ECohtmlKeys::D) \
	op(ECohtmlKeys::E) \
	op(ECohtmlKeys::F) \
	op(ECohtmlKeys::G) \
	op(ECohtmlKeys::H) \
	op(ECohtmlKeys::I) \
	op(ECohtmlKeys::J) \
	op(ECohtmlKeys::K) \
	op(ECohtmlKeys::L) \
	op(ECohtmlKeys::M) \
	op(ECohtmlKeys::N) \
	op(ECohtmlKeys::O) \
	op(ECohtmlKeys::P) \
	op(ECohtmlKeys::Q) \
	op(ECohtmlKeys::R) \
	op(ECohtmlKeys::S) \
	op(ECohtmlKeys::T) \
	op(ECohtmlKeys::U) \
	op(ECohtmlKeys::V) \
	op(ECohtmlKeys::W) \
	op(ECohtmlKeys::X) \
	op(ECohtmlKeys::Y) \
	op(ECohtmlKeys::Z) \
	op(ECohtmlKeys::NumPadZero) \
	op(ECohtmlKeys::NumPadOne) \
	op(ECohtmlKeys::NumPadTwo) \
	op(ECohtmlKeys::NumPadThree) \
	op(ECohtmlKeys::NumPadFour) \
	op(ECohtmlKeys::NumPadFive) \
	op(ECohtmlKeys::NumPadSix) \
	op(ECohtmlKeys::NumPadSeven) \
	op(ECohtmlKeys::NumPadEight) \
	op(ECohtmlKeys::NumPadNine) \
	op(ECohtmlKeys::Multiply) \
	op(ECohtmlKeys::Add) \
	op(ECohtmlKeys::Subtract) \
	op(ECohtmlKeys::Decimal) \
	op(ECohtmlKeys::Divide) \
	op(ECohtmlKeys::F1) \
	op(ECohtmlKeys::F2) \
	op(ECohtmlKeys::F3) \
	op(ECohtmlKeys::F4) \
	op(ECohtmlKeys::F5) \
	op(ECohtmlKeys::F6) \
	op(ECohtmlKeys::F7) \
	op(ECohtmlKeys::F8) \
	op(ECohtmlKeys::F9) \
	op(ECohtmlKeys::F10) \
	op(ECohtmlKeys::F11) \
	op(ECohtmlKeys::F12) \
	op(ECohtmlKeys::NumLock) \
	op(ECohtmlKeys::ScrollLock) \
	op(ECohtmlKeys::LeftShift) \
	op(ECohtmlKeys::RightShift) \
	op(ECohtmlKeys::LeftControl) \
	op(ECohtmlKeys::RightControl) \
	op(ECohtmlKeys::LeftAlt) \
	op(ECohtmlKeys::RightAlt) \
	op(ECohtmlKeys::LeftCommand) \
	op(ECohtmlKeys::RightCommand) \
	op(ECohtmlKeys::Semicolon) \
	op(ECohtmlKeys::Equals) \
	op(ECohtmlKeys::Comma) \
	op(ECohtmlKeys::Underscore) \
	op(ECohtmlKeys::Period) \
	op(ECohtmlKeys::Slash) \
	op(ECohtmlKeys::Tilde) \
	op(ECohtmlKeys::LeftBracket) \
	op(ECohtmlKeys::Backslash) \
	op(ECohtmlKeys::RightBracket) \
	op(ECohtmlKeys::Quote) \
	op(ECohtmlKeys::Unknown) 
PRAGMA_ENABLE_DEPRECATION_WARNINGS
