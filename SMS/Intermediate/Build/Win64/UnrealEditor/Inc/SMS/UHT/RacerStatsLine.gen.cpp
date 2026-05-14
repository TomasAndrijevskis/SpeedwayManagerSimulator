// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SMS/Public/UI/League/Programm/RacerStatsLine.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRacerStatsLine() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
SMS_API UClass* Z_Construct_UClass_UNamesBox_NoRegister();
SMS_API UClass* Z_Construct_UClass_UNumbersBox_NoRegister();
SMS_API UClass* Z_Construct_UClass_URacerStatsLine();
SMS_API UClass* Z_Construct_UClass_URacerStatsLine_NoRegister();
UMG_API UClass* Z_Construct_UClass_UHorizontalBox_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_SMS();
// End Cross Module References

// Begin Class URacerStatsLine
void URacerStatsLine::StaticRegisterNativesURacerStatsLine()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(URacerStatsLine);
UClass* Z_Construct_UClass_URacerStatsLine_NoRegister()
{
	return URacerStatsLine::StaticClass();
}
struct Z_Construct_UClass_URacerStatsLine_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "UI/League/Programm/RacerStatsLine.h" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/RacerStatsLine.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumbersBox_RiderNumber_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/RacerStatsLine.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NamesBox_RacerName_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/RacerStatsLine.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumbersBox_OverallPoints_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/RacerStatsLine.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HB_Points_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/RacerStatsLine.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PointsBoxClass_MetaData[] = {
		{ "Category", "RacerStatsLine" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/RacerStatsLine.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NumbersBox_RiderNumber;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NamesBox_RacerName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NumbersBox_OverallPoints;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HB_Points;
	static const UECodeGen_Private::FClassPropertyParams NewProp_PointsBoxClass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URacerStatsLine>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URacerStatsLine_Statics::NewProp_NumbersBox_RiderNumber = { "NumbersBox_RiderNumber", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URacerStatsLine, NumbersBox_RiderNumber), Z_Construct_UClass_UNumbersBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumbersBox_RiderNumber_MetaData), NewProp_NumbersBox_RiderNumber_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URacerStatsLine_Statics::NewProp_NamesBox_RacerName = { "NamesBox_RacerName", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URacerStatsLine, NamesBox_RacerName), Z_Construct_UClass_UNamesBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NamesBox_RacerName_MetaData), NewProp_NamesBox_RacerName_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URacerStatsLine_Statics::NewProp_NumbersBox_OverallPoints = { "NumbersBox_OverallPoints", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URacerStatsLine, NumbersBox_OverallPoints), Z_Construct_UClass_UNumbersBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumbersBox_OverallPoints_MetaData), NewProp_NumbersBox_OverallPoints_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URacerStatsLine_Statics::NewProp_HB_Points = { "HB_Points", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URacerStatsLine, HB_Points), Z_Construct_UClass_UHorizontalBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HB_Points_MetaData), NewProp_HB_Points_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_URacerStatsLine_Statics::NewProp_PointsBoxClass = { "PointsBoxClass", nullptr, (EPropertyFlags)0x0044000000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URacerStatsLine, PointsBoxClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UNumbersBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PointsBoxClass_MetaData), NewProp_PointsBoxClass_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_URacerStatsLine_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URacerStatsLine_Statics::NewProp_NumbersBox_RiderNumber,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URacerStatsLine_Statics::NewProp_NamesBox_RacerName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URacerStatsLine_Statics::NewProp_NumbersBox_OverallPoints,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URacerStatsLine_Statics::NewProp_HB_Points,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URacerStatsLine_Statics::NewProp_PointsBoxClass,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URacerStatsLine_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_URacerStatsLine_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_SMS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URacerStatsLine_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_URacerStatsLine_Statics::ClassParams = {
	&URacerStatsLine::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_URacerStatsLine_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_URacerStatsLine_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URacerStatsLine_Statics::Class_MetaDataParams), Z_Construct_UClass_URacerStatsLine_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_URacerStatsLine()
{
	if (!Z_Registration_Info_UClass_URacerStatsLine.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_URacerStatsLine.OuterSingleton, Z_Construct_UClass_URacerStatsLine_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_URacerStatsLine.OuterSingleton;
}
template<> SMS_API UClass* StaticClass<URacerStatsLine>()
{
	return URacerStatsLine::StaticClass();
}
URacerStatsLine::URacerStatsLine(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(URacerStatsLine);
URacerStatsLine::~URacerStatsLine() {}
// End Class URacerStatsLine

// Begin Registration
struct Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_RacerStatsLine_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_URacerStatsLine, URacerStatsLine::StaticClass, TEXT("URacerStatsLine"), &Z_Registration_Info_UClass_URacerStatsLine, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(URacerStatsLine), 2525462230U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_RacerStatsLine_h_1698476367(TEXT("/Script/SMS"),
	Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_RacerStatsLine_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_RacerStatsLine_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
