#pragma once

#include "CoreMinimal.h"
#include "BuildingCubes/BC_Variables.h"
#include "Components/ActorComponent.h"
#include "BC_BuildingComponent.generated.h"

class ABC_C_Character;
class ABC_C_BaseBlock;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGCUBES_API UBC_BuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBC_BuildingComponent();

	void StartAction();
	void EndAction();
	void ChangeMaterials(float Value);
	void SwitchAction();
	void ShangeBlock();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Subclasses")
	TArray<TSubclassOf<AActor>> BlockClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Trace")
	float MaxTraceDistance = 3000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Trace")
	float WithoutHitDistance = 500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Material")
	TArray<FBlockMaterialPair> BlockMaterialPairs;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	ABC_C_Character* M_Owner;

	UPROPERTY()
	ABC_C_BaseBlock* M_CurrentBlock;

	UPROPERTY()
	AActor* M_HitActor;

	UPROPERTY()
	UMaterialInstanceDynamic* M_CurrentMat;
	
	UPROPERTY()
	UMaterialInstanceDynamic* M_LightSphereMat;

	void DrawTrace(TArray<AActor*> IgnoredActors, FHitResult& HitResult, float MaxDistance);
	bool CreateBlock(const FHitResult& HitResult);
	void CalculateStartEndDistance(float Distance, FVector& StartLoc, FVector& EndLoc);
	void SetBlockLocation(const FHitResult& HitResult);
	void CreateAndSetMaterial(UMaterialInterface* ParentMaterial);

	EActionType M_CurrentAction;

	bool isStartBuilding;
	bool isStartDestroy;
	bool isStartPreview;
	FVector BlockLocation;
	int32 CurrentMatIndex;
	int32 M_CurrentBlockIndex;
	int32 DeltaIndex;
	float M_CurrentBlockExtend;
};
