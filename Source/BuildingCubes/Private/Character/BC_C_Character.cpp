#include "Character/BC_C_Character.h"
#include "Camera/CameraComponent.h"


ABC_C_Character::ABC_C_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());

	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>("FirstPersonMesh");
	FirstPersonMesh->SetupAttachment(CameraComponent);

}

// Called when the game starts or when spawned
void ABC_C_Character::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABC_C_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABC_C_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

