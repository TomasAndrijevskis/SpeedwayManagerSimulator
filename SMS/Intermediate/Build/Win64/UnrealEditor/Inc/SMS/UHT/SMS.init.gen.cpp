// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSMS_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_SMS;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_SMS()
	{
		if (!Z_Registration_Info_UPackage__Script_SMS.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/SMS",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0x80967AEA,
				0x119F07EA,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_SMS.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_SMS.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_SMS(Z_Construct_UPackage__Script_SMS, TEXT("/Script/SMS"), Z_Registration_Info_UPackage__Script_SMS, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x80967AEA, 0x119F07EA));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
