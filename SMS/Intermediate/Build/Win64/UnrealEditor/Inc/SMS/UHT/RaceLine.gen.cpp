// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SMS/Public/UI/League/Programm/RaceLine.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRaceLine() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FColor();
SLATECORE_API UEnum* Z_Construct_UEnum_SlateCore_ESelectInfo();
SMS_API UClass* Z_Construct_UClass_UChooseBox_NoRegister();
SMS_API UClass* Z_Construct_UClass_UNamesBox_NoRegister();
SMS_API UClass* Z_Construct_UClass_UNumbersBox_NoRegister();
SMS_API UClass* Z_Construct_UClass_URaceLine();
SMS_API UClass* Z_Construct_UClass_URaceLine_NoRegister();
UMG_API UClass* Z_Construct_UClass_UOverlay_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_SMS();
// End Cross Module References

// Begin Class URaceLine Function OnRacerReplaced
struct Z_Construct_UFunction_URaceLine_OnRacerReplaced_Statics
{
	struct RaceLine_eventOnRacerReplaced_Parms
	{
		FString SelectedItem;
		TEnumAsByte<ESelectInfo::Type> SelectionType;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/UI/League/Programm/RaceLine.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_SelectedItem;
	static const UECodeGen_Private::FBytePropertyParams NewProp_SelectionType;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URaceLine_OnRacerReplaced_Statics::NewProp_SelectedItem = { "SelectedItem", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RaceLine_eventOnRacerReplaced_Parms, SelectedItem), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_URaceLine_OnRacerReplaced_Statics::NewProp_SelectionType = { "SelectionType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RaceLine_eventOnRacerReplaced_Parms, SelectionType), Z_Construct_UEnum_SlateCore_ESelectInfo, METADATA_PARAMS(0, nullptr) }; // 4040429206
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URaceLine_OnRacerReplaced_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URaceLine_OnRacerReplaced_Statics::NewProp_SelectedItem,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URaceLine_OnRacerReplaced_Statics::NewProp_SelectionType,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URaceLine_OnRacerReplaced_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URaceLine_OnRacerReplaced_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URaceLine, nullptr, "OnRacerReplaced", nullptr, nullptr, Z_Construct_UFunction_URaceLine_OnRacerReplaced_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URaceLine_OnRacerReplaced_Statics::PropPointers), sizeof(Z_Construct_UFunction_URaceLine_OnRacerReplaced_Statics::RaceLine_eventOnRacerReplaced_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URaceLine_OnRacerReplaced_Statics::Function_MetaDataParams), Z_Construct_UFunction_URaceLine_OnRacerReplaced_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_URaceLine_OnRacerReplaced_Statics::RaceLine_eventOnRacerReplaced_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_URaceLine_OnRacerReplaced()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URaceLine_OnRacerReplaced_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URaceLine::execOnRacerReplaced)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_SelectedItem);
	P_GET_PROPERTY(FByteProperty,Z_Param_SelectionType);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRacerReplaced(Z_Param_SelectedItem,ESelectInfo::Type(Z_Param_SelectionType));
	P_NATIVE_END;
}
// End Class URaceLine Function OnRacerReplaced

// Begin Class URaceLine
void URaceLine::StaticRegisterNativesURaceLine()
{
	UClass* Class = URaceLine::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "OnRacerReplaced", &URaceLine::execOnRacerReplaced },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(URaceLine);
UClass* Z_Construct_UClass_URaceLine_NoRegister()
{
	return URaceLine::StaticClass();
}
struct Z_Construct_UClass_URaceLine_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "UI/League/Programm/RaceLine.h" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/RaceLine.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumbersBox_RacerNumber_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/RaceLine.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Overlay_RacerName_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/RaceLine.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NamesBox_RacerName_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/RaceLine.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChooseBox_RacerReplacement_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/RaceLine.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumbersBox_PointsPerRace_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/RaceLine.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HelmetColour_MetaData[] = {
		{ "Category", "RaceLine" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/RaceLine.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RacerName_MetaData[] = {
		{ "Category", "RaceLine" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/RaceLine.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RacerNumber_MetaData[] = {
		{ "Category", "RaceLine" },
		{ "ModuleRelativePath", "Public/UI/League/Programm/RaceLine.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NumbersBox_RacerNumber;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Overlay_RacerName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NamesBox_RacerName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ChooseBox_RacerReplacement;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NumbersBox_PointsPerRace;
	static const UECodeGen_Private::FStructPropertyParams NewProp_HelmetColour;
	static const UECodeGen_Private::FStrPropertyParams NewProp_RacerName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_RacerNumber;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_URaceLine_OnRacerReplaced, "OnRacerReplaced" }, // 378273624
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URaceLine>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URaceLine_Statics::NewProp_NumbersBox_RacerNumber = { "NumbersBox_RacerNumber", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URaceLine, NumbersBox_RacerNumber), Z_Construct_UClass_UNumbersBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumbersBox_RacerNumber_MetaData), NewProp_NumbersBox_RacerNumber_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URaceLine_Statics::NewProp_Overlay_RacerName = { "Overlay_RacerName", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URaceLine, Overlay_RacerName), Z_Construct_UClass_UOverlay_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Overlay_RacerName_MetaData), NewProp_Overlay_RacerName_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URaceLine_Statics::NewProp_NamesBox_RacerName = { "NamesBox_RacerName", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URaceLine, NamesBox_RacerName), Z_Construct_UClass_UNamesBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NamesBox_RacerName_MetaData), NewProp_NamesBox_RacerName_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URaceLine_Statics::NewProp_ChooseBox_RacerReplacement = { "ChooseBox_RacerReplacement", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URaceLine, ChooseBox_RacerReplacement), Z_Construct_UClass_UChooseBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChooseBox_RacerReplacement_MetaData), NewProp_ChooseBox_RacerReplacement_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URaceLine_Statics::NewProp_NumbersBox_PointsPerRace = { "NumbersBox_PointsPerRace", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URaceLine, NumbersBox_PointsPerRace), Z_Construct_UClass_UNumbersBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumbersBox_PointsPerRace_MetaData), NewProp_NumbersBox_PointsPerRace_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_URaceLine_Statics::NewProp_HelmetColour = { "HelmetColour", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URaceLine, HelmetColour), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HelmetColour_MetaData), NewProp_HelmetColour_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_URaceLine_Statics::NewProp_RacerName = { "RacerName", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URaceLine, RacerName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RacerName_MetaData), NewProp_RacerName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_URaceLine_Statics::NewProp_RacerNumber = { "RacerNumber", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URaceLine, RacerNumber), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RacerNumber_MetaData), NewProp_RacerNumber_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_URaceLine_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URaceLine_Statics::NewProp_NumbersBox_RacerNumber,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URaceLine_Statics::NewProp_Overlay_RacerName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URaceLine_Statics::NewProp_NamesBox_RacerName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URaceLine_Statics::NewProp_ChooseBox_RacerReplacement,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URaceLine_Statics::NewProp_NumbersBox_PointsPerRace,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URaceLine_Statics::NewProp_HelmetColour,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URaceLine_Statics::NewProp_RacerName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URaceLine_Statics::NewProp_RacerNumber,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URaceLine_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_URaceLine_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_SMS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URaceLine_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_URaceLine_Statics::ClassParams = {
	&URaceLine::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_URaceLine_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_URaceLine_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URaceLine_Statics::Class_MetaDataParams), Z_Construct_UClass_URaceLine_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_URaceLine()
{
	if (!Z_Registration_Info_UClass_URaceLine.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_URaceLine.OuterSingleton, Z_Construct_UClass_URaceLine_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_URaceLine.OuterSingleton;
}
template<> SMS_API UClass* StaticClass<URaceLine>()
{
	return URaceLine::StaticClass();
}
URaceLine::URaceLine(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(URaceLine);
URaceLine::~URaceLine() {}
// End Class URaceLine

// Begin Registration
struct Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_RaceLine_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_URaceLine, URaceLine::StaticClass, TEXT("URaceLine"), &Z_Registration_Info_UClass_URaceLine, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(URaceLine), 1697906369U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_RaceLine_h_2079039328(TEXT("/Script/SMS"),
	Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_RaceLine_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_League_Programm_RaceLine_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
