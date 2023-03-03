#include "Character/BC_C_Character.h"
#include "Camera/CameraComponent.h"
#include "Components/BC_BuildingComponent.h"


ABC_C_Character::ABC_C_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());

	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>("FirstPersonMesh");
	FirstPersonMesh->SetupAttachment(CameraComponent);
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetRootComponent());

	LightSphereComponent = CreateDefaultSubobject<UStaticMeshComponent>("LightSphereComponent");
	LightSphereComponent->SetupAttachment(WeaponMesh);

	BuildingComponent = CreateDefaultSubobject<UBC_BuildingComponent>("BuildingComponent");
}


void ABC_C_Character::BeginPlay()
{
	Super::BeginPlay();
	
	check(CameraComponent);
	check(FirstPersonMesh);
	check(WeaponMesh);
	check(LightSphereComponent);

	WeaponMesh->AttachToComponent(FirstPersonMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("GripPoint"));
	LightSphereComponent->AttachToComponent(WeaponMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("Muzzle"));

}


void ABC_C_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABC_C_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("Move Forward / Backward"),this, &ABC_C_Character::MoveForward);
	PlayerInputComponent->BindAxis(FName("Move Right / Left"),this, &ABC_C_Character::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn Right / Left Mouse"),this, &ABC_C_Character::AddControllerYawInput);
	PlayerInputComponent->BindAxis(FName("Look Up / Down Mouse"),this, &ABC_C_Character::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(FName("Change Materials"), this, &ABC_C_Character::ChangeMaterials);

	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed,this,&ABC_C_Character::Jump);
	PlayerInputComponent->BindAction(FName("PrimaryAction"), IE_Pressed,this,&ABC_C_Character::StartAction);
	PlayerInputComponent->BindAction(FName("PrimaryAction"), IE_Released,this,&ABC_C_Character::EndAction);
	PlayerInputComponent->BindAction(FName("Switch Action"), IE_Pressed, this, &ABC_C_Character::SwitchAction);
	PlayerInputComponent->BindAction(FName("ShangeBlock"), IE_Pressed, this,&ABC_C_Character::ChangeBlock);
}

void ABC_C_Character::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ABC_C_Character::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ABC_C_Character::StartAction()
{
	BuildingComponent->StartAction();
}

void ABC_C_Character::EndAction()
{
	BuildingComponent->EndAction();
}

void ABC_C_Character::ChangeMaterials(float Value)
{
	if(FMath::IsNearlyZero(Value)) return;
	BuildingComponent->ChangeMaterials(Value);
}

void ABC_C_Character::SwitchAction()
{
	BuildingComponent->SwitchAction();
}

void ABC_C_Character::ChangeBlock()
{
	BuildingComponent->ShangeBlock();
}

