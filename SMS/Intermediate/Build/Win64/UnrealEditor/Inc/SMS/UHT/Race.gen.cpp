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
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
SMS_API UClass* Z_Construct_UClass_UNumbersBox_NoRegister();
SMS_API UClass* Z_Construct_UClass_URace();
SMS_API UClass* Z_Construct_UClass_URace_NoRegister();
SMS_API UClass* Z_Construct_UClass_URaceLine_NoRegister();
SMS_API UClass* Z_Construct_UClass_URacePatternsDataAsset_NoRegister();
SMS_API UClass* Z_Construct_UClass_UScoreCounter_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UMG_API UClass* Z_Construct_UClass_UVerticalBox_NoRegister();
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScoreCounter_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/Race.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VB_Content_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/Race.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RaceDataAsset_MetaData[] = {
		{ "Category", "Race" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/Race.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RaceLineClass_MetaData[] = {
		{ "Category", "Race" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/Race.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NumbersBox_RaceNumber;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ScoreCounter;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_VB_Content;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RaceDataAsset;
	static const UECodeGen_Private::FClassPropertyParams NewProp_RaceLineClass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URace>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URace_Statics::NewProp_NumbersBox_RaceNumber = { "NumbersBox_RaceNumber", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URace, NumbersBox_RaceNumber), Z_Construct_UClass_UNumbersBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumbersBox_RaceNumber_MetaData), NewProp_NumbersBox_RaceNumber_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URace_Statics::NewProp_ScoreCounter = { "ScoreCounter", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URace, ScoreCounter), Z_Construct_UClass_UScoreCounter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScoreCounter_MetaData), NewProp_ScoreCounter_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URace_Statics::NewProp_VB_Content = { "VB_Content", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URace, VB_Content), Z_Construct_UClass_UVerticalBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VB_Content_MetaData), NewProp_VB_Content_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URace_Statics::NewProp_RaceDataAsset = { "RaceDataAsset", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URace, RaceDataAsset), Z_Construct_UClass_URacePatternsDataAsset_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RaceDataAsset_MetaData), NewProp_RaceDataAsset_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_URace_Statics::NewProp_RaceLineClass = { "RaceLineClass", nullptr, (EPropertyFlags)0x0044000000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URace, RaceLineClass), Z_Construct_UClass_UClass, Z_Construct_UClass_URaceLine_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RaceLineClass_MetaData), NewProp_RaceLineClass_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_URace_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URace_Statics::NewProp_NumbersBox_RaceNumber,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URace_Statics::NewProp_ScoreCounter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URace_Statics::NewProp_VB_Content,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URace_Statics::NewProp_RaceDataAsset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URace_Statics::NewProp_RaceLineClass,
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
		{ Z_Construct_UClass_URace, URace::StaticClass, TEXT("URace"), &Z_Registration_Info_UClass_URace, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(URace), 4025511326U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_Race_h_250662312(TEXT("/Script/SMS"),
	Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_Race_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_Race_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
