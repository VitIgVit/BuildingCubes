#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BC_C_Character.generated.h"

class UCameraComponent;

UCLASS()
class BUILDINGCUBES_API ABC_C_Character : public ACharacter
{
	GENERATED_BODY()

public:
	ABC_C_Character();

protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	USkeletalMeshComponent* FirstPersonMesh;

public:	
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
