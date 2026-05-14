// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SMS/Public/UI/BaseClasses/NumbersBox.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNumbersBox() {}

// Begin Cross Module References
SMS_API UClass* Z_Construct_UClass_UNumbersBox();
SMS_API UClass* Z_Construct_UClass_UNumbersBox_NoRegister();
UMG_API UClass* Z_Construct_UClass_UBorder_NoRegister();
UMG_API UClass* Z_Construct_UClass_UTextBlock_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_SMS();
// End Cross Module References

// Begin Class UNumbersBox
void UNumbersBox::StaticRegisterNativesUNumbersBox()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UNumbersBox);
UClass* Z_Construct_UClass_UNumbersBox_NoRegister()
{
	return UNumbersBox::StaticClass();
}
struct Z_Construct_UClass_UNumbersBox_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "UI/BaseClasses/NumbersBox.h" },
		{ "ModuleRelativePath", "Public/UI/BaseClasses/NumbersBox.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Text_Number_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/BaseClasses/NumbersBox.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Border_BackgroundColour_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/BaseClasses/NumbersBox.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Text_Number;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Border_BackgroundColour;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNumbersBox>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UNumbersBox_Statics::NewProp_Text_Number = { "Text_Number", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNumbersBox, Text_Number), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Text_Number_MetaData), NewProp_Text_Number_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UNumbersBox_Statics::NewProp_Border_BackgroundColour = { "Border_BackgroundColour", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNumbersBox, Border_BackgroundColour), Z_Construct_UClass_UBorder_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Border_BackgroundColour_MetaData), NewProp_Border_BackgroundColour_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNumbersBox_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNumbersBox_Statics::NewProp_Text_Number,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNumbersBox_Statics::NewProp_Border_BackgroundColour,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNumbersBox_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UNumbersBox_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_SMS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNumbersBox_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UNumbersBox_Statics::ClassParams = {
	&UNumbersBox::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UNumbersBox_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UNumbersBox_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNumbersBox_Statics::Class_MetaDataParams), Z_Construct_UClass_UNumbersBox_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UNumbersBox()
{
	if (!Z_Registration_Info_UClass_UNumbersBox.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNumbersBox.OuterSingleton, Z_Construct_UClass_UNumbersBox_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UNumbersBox.OuterSingleton;
}
template<> SMS_API UClass* StaticClass<UNumbersBox>()
{
	return UNumbersBox::StaticClass();
}
UNumbersBox::UNumbersBox(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UNumbersBox);
UNumbersBox::~UNumbersBox() {}
// End Class UNumbersBox

// Begin Registration
struct Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_BaseClasses_NumbersBox_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNumbersBox, UNumbersBox::StaticClass, TEXT("UNumbersBox"), &Z_Registration_Info_UClass_UNumbersBox, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNumbersBox), 3685781865U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_BaseClasses_NumbersBox_h_617189620(TEXT("/Script/SMS"),
	Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_BaseClasses_NumbersBox_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_BaseClasses_NumbersBox_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
