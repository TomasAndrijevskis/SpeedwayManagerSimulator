// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SMS/Public/UI/League/Programm/ScoreCounter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeScoreCounter() {}

// Begin Cross Module References
SMS_API UClass* Z_Construct_UClass_UNumbersBox_NoRegister();
SMS_API UClass* Z_Construct_UClass_UScoreCounter();
SMS_API UClass* Z_Construct_UClass_UScoreCounter_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_SMS();
// End Cross Module References

// Begin Class UScoreCounter
void UScoreCounter::StaticRegisterNativesUScoreCounter()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UScoreCounter);
UClass* Z_Construct_UClass_UScoreCounter_NoRegister()
{
	return UScoreCounter::StaticClass();
}
struct Z_Construct_UClass_UScoreCounter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "UI/League/Programm/ScoreCounter.h" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/ScoreCounter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumbersBox_HomeTeamRacePoints_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/ScoreCounter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumbersBox_VisitorTeamRacePoints_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/ScoreCounter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumbersBox_HomeTeamOverallPoints_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/ScoreCounter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumbersBox_VisitorTeamOverallPoints_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/ScoreCounter.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NumbersBox_HomeTeamRacePoints;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NumbersBox_VisitorTeamRacePoints;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NumbersBox_HomeTeamOverallPoints;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NumbersBox_VisitorTeamOverallPoints;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UScoreCounter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UScoreCounter_Statics::NewProp_NumbersBox_HomeTeamRacePoints = { "NumbersBox_HomeTeamRacePoints", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UScoreCounter, NumbersBox_HomeTeamRacePoints), Z_Construct_UClass_UNumbersBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumbersBox_HomeTeamRacePoints_MetaData), NewProp_NumbersBox_HomeTeamRacePoints_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UScoreCounter_Statics::NewProp_NumbersBox_VisitorTeamRacePoints = { "NumbersBox_VisitorTeamRacePoints", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UScoreCounter, NumbersBox_VisitorTeamRacePoints), Z_Construct_UClass_UNumbersBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumbersBox_VisitorTeamRacePoints_MetaData), NewProp_NumbersBox_VisitorTeamRacePoints_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UScoreCounter_Statics::NewProp_NumbersBox_HomeTeamOverallPoints = { "NumbersBox_HomeTeamOverallPoints", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UScoreCounter, NumbersBox_HomeTeamOverallPoints), Z_Construct_UClass_UNumbersBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumbersBox_HomeTeamOverallPoints_MetaData), NewProp_NumbersBox_HomeTeamOverallPoints_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UScoreCounter_Statics::NewProp_NumbersBox_VisitorTeamOverallPoints = { "NumbersBox_VisitorTeamOverallPoints", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UScoreCounter, NumbersBox_VisitorTeamOverallPoints), Z_Construct_UClass_UNumbersBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumbersBox_VisitorTeamOverallPoints_MetaData), NewProp_NumbersBox_VisitorTeamOverallPoints_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UScoreCounter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UScoreCounter_Statics::NewProp_NumbersBox_HomeTeamRacePoints,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UScoreCounter_Statics::NewProp_NumbersBox_VisitorTeamRacePoints,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UScoreCounter_Statics::NewProp_NumbersBox_HomeTeamOverallPoints,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UScoreCounter_Statics::NewProp_NumbersBox_VisitorTeamOverallPoints,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UScoreCounter_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UScoreCounter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_SMS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UScoreCounter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UScoreCounter_Statics::ClassParams = {
	&UScoreCounter::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UScoreCounter_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UScoreCounter_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UScoreCounter_Statics::Class_MetaDataParams), Z_Construct_UClass_UScoreCounter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UScoreCounter()
{
	if (!Z_Registration_Info_UClass_UScoreCounter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UScoreCounter.OuterSingleton, Z_Construct_UClass_UScoreCounter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UScoreCounter.OuterSingleton;
}
template<> SMS_API UClass* StaticClass<UScoreCounter>()
{
	return UScoreCounter::StaticClass();
}
UScoreCounter::UScoreCounter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UScoreCounter);
UScoreCounter::~UScoreCounter() {}
// End Class UScoreCounter

// Begin Registration
struct Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_ScoreCounter_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UScoreCounter, UScoreCounter::StaticClass, TEXT("UScoreCounter"), &Z_Registration_Info_UClass_UScoreCounter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UScoreCounter), 1724310993U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_ScoreCounter_h_3064637307(TEXT("/Script/SMS"),
	Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_ScoreCounter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_ScoreCounter_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
