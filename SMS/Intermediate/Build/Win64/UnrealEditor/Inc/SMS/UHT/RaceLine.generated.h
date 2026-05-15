// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "UI/League/Programm/RaceLine.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SMS_RaceLine_generated_h
#error "RaceLine.generated.h already included, missing '#pragma once' in RaceLine.h"
#endif
#define SMS_RaceLine_generated_h

#define FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_RaceLine_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnRacerReplaced);


#define FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_RaceLine_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesURaceLine(); \
	friend struct Z_Construct_UClass_URaceLine_Statics; \
public: \
	DECLARE_CLASS(URaceLine, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SMS"), NO_API) \
	DECLARE_SERIALIZER(URaceLine)


#define FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_RaceLine_h_20_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API URaceLine(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	URaceLine(URaceLine&&); \
	URaceLine(const URaceLine&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, URaceLine); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(URaceLine); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(URaceLine) \
	NO_API virtual ~URaceLine();


#define FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_RaceLine_h_17_PROLOG
#define FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_RaceLine_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_RaceLine_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_RaceLine_h_20_INCLASS_NO_PURE_DECLS \
	FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_RaceLine_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SMS_API UClass* StaticClass<class URaceLine>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_RaceLine_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
