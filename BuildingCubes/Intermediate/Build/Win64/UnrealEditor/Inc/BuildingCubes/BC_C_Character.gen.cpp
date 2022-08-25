// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BuildingCubes/Public/Character/BC_C_Character.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBC_C_Character() {}
// Cross Module References
	BUILDINGCUBES_API UClass* Z_Construct_UClass_ABC_C_Character_NoRegister();
	BUILDINGCUBES_API UClass* Z_Construct_UClass_ABC_C_Character();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	UPackage* Z_Construct_UPackage__Script_BuildingCubes();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
// End Cross Module References
	void ABC_C_Character::StaticRegisterNativesABC_C_Character()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ABC_C_Character);
	UClass* Z_Construct_UClass_ABC_C_Character_NoRegister()
	{
		return ABC_C_Character::StaticClass();
	}
	struct Z_Construct_UClass_ABC_C_Character_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CameraComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraComponent;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FirstPersonMesh_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_FirstPersonMesh;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ABC_C_Character_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_BuildingCubes,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABC_C_Character_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Character/BC_C_Character.h" },
		{ "ModuleRelativePath", "Public/Character/BC_C_Character.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABC_C_Character_Statics::NewProp_CameraComponent_MetaData[] = {
		{ "Category", "Camera" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Character/BC_C_Character.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABC_C_Character_Statics::NewProp_CameraComponent = { "CameraComponent", nullptr, (EPropertyFlags)0x002008000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABC_C_Character, CameraComponent), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ABC_C_Character_Statics::NewProp_CameraComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABC_C_Character_Statics::NewProp_CameraComponent_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABC_C_Character_Statics::NewProp_FirstPersonMesh_MetaData[] = {
		{ "Category", "Mesh" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Character/BC_C_Character.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABC_C_Character_Statics::NewProp_FirstPersonMesh = { "FirstPersonMesh", nullptr, (EPropertyFlags)0x002008000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABC_C_Character, FirstPersonMesh), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ABC_C_Character_Statics::NewProp_FirstPersonMesh_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABC_C_Character_Statics::NewProp_FirstPersonMesh_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ABC_C_Character_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABC_C_Character_Statics::NewProp_CameraComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABC_C_Character_Statics::NewProp_FirstPersonMesh,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ABC_C_Character_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABC_C_Character>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ABC_C_Character_Statics::ClassParams = {
		&ABC_C_Character::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ABC_C_Character_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ABC_C_Character_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ABC_C_Character_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ABC_C_Character_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ABC_C_Character()
	{
		if (!Z_Registration_Info_UClass_ABC_C_Character.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ABC_C_Character.OuterSingleton, Z_Construct_UClass_ABC_C_Character_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ABC_C_Character.OuterSingleton;
	}
	template<> BUILDINGCUBES_API UClass* StaticClass<ABC_C_Character>()
	{
		return ABC_C_Character::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ABC_C_Character);
	struct Z_CompiledInDeferFile_FID_BuildingCubes_Source_BuildingCubes_Public_Character_BC_C_Character_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_BuildingCubes_Source_BuildingCubes_Public_Character_BC_C_Character_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ABC_C_Character, ABC_C_Character::StaticClass, TEXT("ABC_C_Character"), &Z_Registration_Info_UClass_ABC_C_Character, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ABC_C_Character), 2379736748U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_BuildingCubes_Source_BuildingCubes_Public_Character_BC_C_Character_h_3207550030(TEXT("/Script/BuildingCubes"),
		Z_CompiledInDeferFile_FID_BuildingCubes_Source_BuildingCubes_Public_Character_BC_C_Character_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_BuildingCubes_Source_BuildingCubes_Public_Character_BC_C_Character_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
