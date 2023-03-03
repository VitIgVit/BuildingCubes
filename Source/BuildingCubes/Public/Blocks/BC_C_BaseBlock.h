#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BC_C_BaseBlock.generated.h"

UCLASS()
class BUILDINGCUBES_API ABC_C_BaseBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	ABC_C_BaseBlock();

	void OnEndBuilding();
	void OnStartDestroy();
	void OnResetDestroy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Block")
	UStaticMeshComponent* BlockMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emit")
	float FadeTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emit")
	float FadePowerMult = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emit")
	float RiseTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emit")
	float RisePowerMult = 10.0f;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	bool M_StartFadeEmit;
	bool M_StartRiseEmit;
	bool M_ResetRiseEmit;
	
	float M_FXEmitPower;
	UPROPERTY()
	UMaterialInstanceDynamic* M_BlockDynMat;

	void ChangeEmitPower(float Power);
	void ResetEmitToZero();
};
