#pragma once

#include <execution>

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BC_C_Character.generated.h"

class UCameraComponent;
class UBC_BuildingComponent;

UCLASS()
class BUILDINGCUBES_API ABC_C_Character : public ACharacter
{
	GENERATED_BODY()

public:
	ABC_C_Character();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* LightSphereComponent;

protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	USkeletalMeshComponent* FirstPersonMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponMesh")
    USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildingComponent")
	UBC_BuildingComponent* BuildingComponent;

public:	
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void StartAction();
	void EndAction();
	void ChangeMaterials(float Value);
	void SwitchAction();
	void ChangeBlock();

};
