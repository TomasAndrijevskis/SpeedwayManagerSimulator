// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SMS/Public/UI/League/Programm/Race.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRace() {}

// Begin Cross Module References
SMS_API UClass* Z_Construct_UClass_UNumbersBox_NoRegister();
SMS_API UClass* Z_Construct_UClass_URace();
SMS_API UClass* Z_Construct_UClass_URace_NoRegister();
SMS_API UClass* Z_Construct_UClass_URaceLine_NoRegister();
SMS_API UClass* Z_Construct_UClass_UScoreCounter_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_SMS();
// End Cross Module References

// Begin Class URace
void URace::StaticRegisterNativesURace()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(URace);
UClass* Z_Construct_UClass_URace_NoRegister()
{
	return URace::StaticClass();
}
struct Z_Construct_UClass_URace_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "UI/League/Programm/Race.h" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/Race.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumbersBox_RaceNumber_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/Race.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RaceLine_First_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/Race.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RaceLine_Second_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/Race.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RaceLine_Third_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/Race.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RaceLine_Fourth_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/Race.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScoreCounter_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/Race.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NumbersBox_RaceNumber;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RaceLine_First;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RaceLine_Second;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RaceLine_Third;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RaceLine_Fourth;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ScoreCounter;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URace>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URace_Statics::NewProp_NumbersBox_RaceNumber = { "NumbersBox_RaceNumber", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URace, NumbersBox_RaceNumber), Z_Construct_UClass_UNumbersBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumbersBox_RaceNumber_MetaData), NewProp_NumbersBox_RaceNumber_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URace_Statics::NewProp_RaceLine_First = { "RaceLine_First", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URace, RaceLine_First), Z_Construct_UClass_URaceLine_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RaceLine_First_MetaData), NewProp_RaceLine_First_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URace_Statics::NewProp_RaceLine_Second = { "RaceLine_Second", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URace, RaceLine_Second), Z_Construct_UClass_URaceLine_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RaceLine_Second_MetaData), NewProp_RaceLine_Second_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URace_Statics::NewProp_RaceLine_Third = { "RaceLine_Third", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URace, RaceLine_Third), Z_Construct_UClass_URaceLine_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RaceLine_Third_MetaData), NewProp_RaceLine_Third_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URace_Statics::NewProp_RaceLine_Fourth = { "RaceLine_Fourth", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URace, RaceLine_Fourth), Z_Construct_UClass_URaceLine_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RaceLine_Fourth_MetaData), NewProp_RaceLine_Fourth_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URace_Statics::NewProp_ScoreCounter = { "ScoreCounter", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URace, ScoreCounter), Z_Construct_UClass_UScoreCounter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScoreCounter_MetaData), NewProp_ScoreCounter_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_URace_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URace_Statics::NewProp_NumbersBox_RaceNumber,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URace_Statics::NewProp_RaceLine_First,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URace_Statics::NewProp_RaceLine_Second,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URace_Statics::NewProp_RaceLine_Third,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URace_Statics::NewProp_RaceLine_Fourth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URace_Statics::NewProp_ScoreCounter,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URace_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_URace_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_SMS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URace_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_URace_Statics::ClassParams = {
	&URace::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_URace_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_URace_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URace_Statics::Class_MetaDataParams), Z_Construct_UClass_URace_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_URace()
{
	if (!Z_Registration_Info_UClass_URace.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_URace.OuterSingleton, Z_Construct_UClass_URace_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_URace.OuterSingleton;
}
template<> SMS_API UClass* StaticClass<URace>()
{
	return URace::StaticClass();
}
URace::URace(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(URace);
URace::~URace() {}
// End Class URace

// Begin Registration
struct Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_Race_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_URace, URace::StaticClass, TEXT("URace"), &Z_Registration_Info_UClass_URace, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(URace), 3441828261U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_Race_h_2979085648(TEXT("/Script/SMS"),
	Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_Race_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_Race_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
