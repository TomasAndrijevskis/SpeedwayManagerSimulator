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
SMS_API UClass* Z_Construct_UClass_UChooseBox_NoRegister();
SMS_API UClass* Z_Construct_UClass_UNumbersBox_NoRegister();
SMS_API UClass* Z_Construct_UClass_URacerStatsLine();
SMS_API UClass* Z_Construct_UClass_URacerStatsLine_NoRegister();
UMG_API UClass* Z_Construct_UClass_UHorizontalBox_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_SMS();
// End Cross Module References

// Begin Class URacerStatsLine Function AddPoints
struct Z_Construct_UFunction_URacerStatsLine_AddPoints_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/UI/League/Programm/RacerStatsLine.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URacerStatsLine_AddPoints_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URacerStatsLine, nullptr, "AddPoints", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URacerStatsLine_AddPoints_Statics::Function_MetaDataParams), Z_Construct_UFunction_URacerStatsLine_AddPoints_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_URacerStatsLine_AddPoints()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URacerStatsLine_AddPoints_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URacerStatsLine::execAddPoints)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AddPoints();
	P_NATIVE_END;
}
// End Class URacerStatsLine Function AddPoints

// Begin Class URacerStatsLine
void URacerStatsLine::StaticRegisterNativesURacerStatsLine()
{
	UClass* Class = URacerStatsLine::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "AddPoints", &URacerStatsLine::execAddPoints },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChooseBox_Racer_MetaData[] = {
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RacerPoints_MetaData[] = {
		{ "Category", "RacerStatsLine" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/RacerStatsLine.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxRacesAmount_MetaData[] = {
		{ "Category", "RacerStatsLine" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/RacerStatsLine.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ID_MetaData[] = {
		{ "Category", "RacerStatsLine" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/RacerStatsLine.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RacerName_MetaData[] = {
		{ "Category", "RacerStatsLine" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/RacerStatsLine.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NumbersBox_RiderNumber;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ChooseBox_Racer;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NumbersBox_OverallPoints;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HB_Points;
	static const UECodeGen_Private::FClassPropertyParams NewProp_PointsBoxClass;
	static const UECodeGen_Private::FStrPropertyParams NewProp_RacerPoints_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RacerPoints;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxRacesAmount;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ID;
	static const UECodeGen_Private::FStrPropertyParams NewProp_RacerName;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_URacerStatsLine_AddPoints, "AddPoints" }, // 2404227256
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URacerStatsLine>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URacerStatsLine_Statics::NewProp_NumbersBox_RiderNumber = { "NumbersBox_RiderNumber", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URacerStatsLine, NumbersBox_RiderNumber), Z_Construct_UClass_UNumbersBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumbersBox_RiderNumber_MetaData), NewProp_NumbersBox_RiderNumber_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URacerStatsLine_Statics::NewProp_ChooseBox_Racer = { "ChooseBox_Racer", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URacerStatsLine, ChooseBox_Racer), Z_Construct_UClass_UChooseBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChooseBox_Racer_MetaData), NewProp_ChooseBox_Racer_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URacerStatsLine_Statics::NewProp_NumbersBox_OverallPoints = { "NumbersBox_OverallPoints", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URacerStatsLine, NumbersBox_OverallPoints), Z_Construct_UClass_UNumbersBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumbersBox_OverallPoints_MetaData), NewProp_NumbersBox_OverallPoints_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URacerStatsLine_Statics::NewProp_HB_Points = { "HB_Points", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URacerStatsLine, HB_Points), Z_Construct_UClass_UHorizontalBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HB_Points_MetaData), NewProp_HB_Points_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_URacerStatsLine_Statics::NewProp_PointsBoxClass = { "PointsBoxClass", nullptr, (EPropertyFlags)0x0044000000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URacerStatsLine, PointsBoxClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UNumbersBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PointsBoxClass_MetaData), NewProp_PointsBoxClass_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_URacerStatsLine_Statics::NewProp_RacerPoints_Inner = { "RacerPoints", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_URacerStatsLine_Statics::NewProp_RacerPoints = { "RacerPoints", nullptr, (EPropertyFlags)0x0040000000020001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URacerStatsLine, RacerPoints), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RacerPoints_MetaData), NewProp_RacerPoints_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_URacerStatsLine_Statics::NewProp_MaxRacesAmount = { "MaxRacesAmount", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URacerStatsLine, MaxRacesAmount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxRacesAmount_MetaData), NewProp_MaxRacesAmount_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_URacerStatsLine_Statics::NewProp_ID = { "ID", nullptr, (EPropertyFlags)0x0040000000020001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URacerStatsLine, ID), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ID_MetaData), NewProp_ID_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_URacerStatsLine_Statics::NewProp_RacerName = { "RacerName", nullptr, (EPropertyFlags)0x0040000000020001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URacerStatsLine, RacerName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RacerName_MetaData), NewProp_RacerName_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_URacerStatsLine_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URacerStatsLine_Statics::NewProp_NumbersBox_RiderNumber,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URacerStatsLine_Statics::NewProp_ChooseBox_Racer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URacerStatsLine_Statics::NewProp_NumbersBox_OverallPoints,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URacerStatsLine_Statics::NewProp_HB_Points,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URacerStatsLine_Statics::NewProp_PointsBoxClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URacerStatsLine_Statics::NewProp_RacerPoints_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URacerStatsLine_Statics::NewProp_RacerPoints,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URacerStatsLine_Statics::NewProp_MaxRacesAmount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URacerStatsLine_Statics::NewProp_ID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URacerStatsLine_Statics::NewProp_RacerName,
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
	FuncInfo,
	Z_Construct_UClass_URacerStatsLine_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
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
		{ Z_Construct_UClass_URacerStatsLine, URacerStatsLine::StaticClass, TEXT("URacerStatsLine"), &Z_Registration_Info_UClass_URacerStatsLine, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(URacerStatsLine), 1817371808U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_RacerStatsLine_h_1631940298(TEXT("/Script/SMS"),
	Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_RacerStatsLine_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_RacerStatsLine_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
