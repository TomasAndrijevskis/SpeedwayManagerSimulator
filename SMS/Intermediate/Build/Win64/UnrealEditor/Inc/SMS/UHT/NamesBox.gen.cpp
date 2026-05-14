// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SMS/Public/UI/BaseClasses/NamesBox.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNamesBox() {}

// Begin Cross Module References
SMS_API UClass* Z_Construct_UClass_UNamesBox();
SMS_API UClass* Z_Construct_UClass_UNamesBox_NoRegister();
UMG_API UClass* Z_Construct_UClass_UTextBlock_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_SMS();
// End Cross Module References

// Begin Class UNamesBox
void UNamesBox::StaticRegisterNativesUNamesBox()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UNamesBox);
UClass* Z_Construct_UClass_UNamesBox_NoRegister()
{
	return UNamesBox::StaticClass();
}
struct Z_Construct_UClass_UNamesBox_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "UI/BaseClasses/NamesBox.h" },
		{ "ModuleRelativePath", "Public/UI/BaseClasses/NamesBox.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Text_Name_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/BaseClasses/NamesBox.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Text_Name;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNamesBox>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UNamesBox_Statics::NewProp_Text_Name = { "Text_Name", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNamesBox, Text_Name), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Text_Name_MetaData), NewProp_Text_Name_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNamesBox_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNamesBox_Statics::NewProp_Text_Name,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNamesBox_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UNamesBox_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_SMS,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNamesBox_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UNamesBox_Statics::ClassParams = {
	&UNamesBox::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UNamesBox_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UNamesBox_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNamesBox_Statics::Class_MetaDataParams), Z_Construct_UClass_UNamesBox_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UNamesBox()
{
	if (!Z_Registration_Info_UClass_UNamesBox.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNamesBox.OuterSingleton, Z_Construct_UClass_UNamesBox_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UNamesBox.OuterSingleton;
}
template<> SMS_API UClass* StaticClass<UNamesBox>()
{
	return UNamesBox::StaticClass();
}
UNamesBox::UNamesBox(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UNamesBox);
UNamesBox::~UNamesBox() {}
// End Class UNamesBox

// Begin Registration
struct Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_BaseClasses_NamesBox_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNamesBox, UNamesBox::StaticClass, TEXT("UNamesBox"), &Z_Registration_Info_UClass_UNamesBox, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNamesBox), 1398419215U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_BaseClasses_NamesBox_h_3263217775(TEXT("/Script/SMS"),
	Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_BaseClasses_NamesBox_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_projects_GIT_HUB_SpeedwayManagerSimulator_SMS_Source_SMS_Public_UI_BaseClasses_NamesBox_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
