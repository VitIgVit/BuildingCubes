#include "Components/BC_BuildingComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/BC_C_Character.h"
#include "Blocks/BC_C_BaseBlock.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(Log_BC_BuildingComponent, All, All);

UBC_BuildingComponent::UBC_BuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UBC_BuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	M_Owner = Cast<ABC_C_Character>(GetOwner());

	M_CurrentAction = EActionType::Build;

	CurrentMatIndex = 0;

	if (IsValid(M_Owner) &&
		IsValid(M_Owner->LightSphereComponent) &&
		IsValid(M_Owner->LightSphereComponent->GetMaterial(0)) &&
		IsValid(GetWorld()))
    {
	M_LightSphereMat = UMaterialInstanceDynamic::Create(M_Owner->LightSphereComponent->GetMaterial(0), GetWorld());
		if(M_LightSphereMat)
		{
			M_Owner->LightSphereComponent->SetMaterial(0, M_LightSphereMat);
		}
    }
}


void UBC_BuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (isStartBuilding)
	{
		TArray<AActor*> IgnoredActors;
		IgnoredActors.Add(M_Owner);
		IgnoredActors.AddUnique(M_CurrentBlock);

		FHitResult HitResult;
		DrawTrace(IgnoredActors, HitResult, MaxTraceDistance);

		if (CreateBlock(HitResult))
		{
			SetBlockLocation(HitResult);
		}
	}
	else if(isStartDestroy)
	{
		TArray<AActor*> IgnoredActors;
		IgnoredActors.Add(M_Owner);

		FHitResult HitResult;
		DrawTrace(IgnoredActors, HitResult, MaxTraceDistance);
		if(HitResult.bBlockingHit && IsValid(HitResult.GetActor()))
		{
			if(HitResult.GetActor()->IsA<ABC_C_BaseBlock>())
			{
				Cast<ABC_C_BaseBlock>(HitResult.GetActor())->OnStartDestroy();
			}

			if(IsValid(M_HitActor) && M_HitActor->GetName() != HitResult.GetActor()->GetName())
			{
				Cast<ABC_C_BaseBlock>(M_HitActor)->OnResetDestroy();
			}
			M_HitActor = HitResult.GetActor();
		}
	}
}


void UBC_BuildingComponent::StartAction()
{
	if (M_CurrentAction == EActionType::Build)
	{
		isStartBuilding = true;
	}
	if (M_CurrentAction == EActionType::Destroy)
	{
		isStartDestroy = true;
	}
}

void UBC_BuildingComponent::EndAction()
{
	if (M_CurrentAction == EActionType::Build)
	{
		isStartBuilding = false;
		isStartPreview = false;

		CreateAndSetMaterial(BlockMaterialPairs[CurrentMatIndex].Base);
		if(IsValid(M_CurrentMat) && IsValid(M_CurrentBlock))
		{
			M_CurrentMat->SetVectorParameterValue(FName("Emit Color"), BlockMaterialPairs[CurrentMatIndex].EmitColor);
			M_CurrentBlock->OnEndBuilding();
		}
	}
	if (M_CurrentAction == EActionType::Destroy)
	{
		isStartDestroy = false;
		Cast<ABC_C_BaseBlock>(M_HitActor)->OnResetDestroy();
	}
}

void UBC_BuildingComponent::DrawTrace(TArray<AActor*> IgnoredActors, FHitResult& HitResult, float MaxDistance)
{
	if (!IsValid(M_Owner)) return;
	FVector StartLoc(ForceInitToZero), EndLoc(ForceInitToZero);
	CalculateStartEndDistance(MaxDistance, StartLoc, EndLoc);

	UKismetSystemLibrary::LineTraceSingle(GetWorld(), StartLoc, EndLoc,
	                                      TraceTypeQuery1,
	                                      false,
	                                      IgnoredActors,
	                                      EDrawDebugTrace::None,
	                                      HitResult,
	                                      true,
	                                      FLinearColor::Red,
	                                      FLinearColor::Green, 0.5f);
}

bool UBC_BuildingComponent::CreateBlock(const FHitResult& HitResult)
{
	if (isStartPreview) return true;
	if (!IsValid(BlockClasses[M_CurrentBlockIndex])) return false;

	FTransform BlockTransform;
	BlockTransform.SetLocation(HitResult.Location);
	M_CurrentBlock = GetWorld()->SpawnActor<ABC_C_BaseBlock>(BlockClasses[M_CurrentBlockIndex], BlockTransform);
	if(IsValid(M_CurrentBlock))
	{
		FVector Origin(ForceInitToZero), Extend(ForceInitToZero);
		M_CurrentBlock->GetActorBounds(false, Origin, Extend);
		M_CurrentBlockExtend = Extend.X;
	}

	CreateAndSetMaterial(BlockMaterialPairs[CurrentMatIndex].Preview);
	
	return isStartPreview = IsValid(M_CurrentBlock);
}

void UBC_BuildingComponent::CalculateStartEndDistance(float Distance, FVector& StartLoc, FVector& EndLoc)
{
	StartLoc = M_Owner->LightSphereComponent->GetComponentLocation();
	EndLoc = StartLoc + M_Owner->FindComponentByClass<UCameraComponent>()->GetForwardVector() * Distance;
}

void UBC_BuildingComponent::SetBlockLocation(const FHitResult& HitResult)
{
	if (HitResult.bBlockingHit)
	{
		BlockLocation = (HitResult.Location.GridSnap(M_CurrentBlockExtend) + HitResult.Normal * M_CurrentBlockExtend);
	}
	else
	{
		FVector StartLoc(ForceInitToZero), EndLoc(ForceInitToZero);
		CalculateStartEndDistance(WithoutHitDistance, StartLoc, EndLoc);
		BlockLocation = EndLoc.GridSnap(M_CurrentBlockExtend);
	}
	const TArray<AActor*> ActorsToIgnored{M_Owner, M_CurrentBlock};
	TArray<FHitResult> BoxHits;

	UKismetSystemLibrary::BoxTraceMulti(GetWorld(), BlockLocation,
										BlockLocation, FVector(M_CurrentBlockExtend),
										FRotator::ZeroRotator, TraceTypeQuery1,
										false, ActorsToIgnored, EDrawDebugTrace::None,
										BoxHits, true);

	for (const auto& OneHit : BoxHits)
	{
		BlockLocation += OneHit.Normal;
		UE_LOG(Log_BC_BuildingComponent, Display, TEXT("Hit: %s"), *OneHit.Normal.ToString());
	}
	
	if(!IsValid(M_CurrentBlock)) return;
	M_CurrentBlock->SetActorLocation(BlockLocation);
}

void UBC_BuildingComponent::ChangeMaterials(float Value)
{
	CurrentMatIndex += FMath::Clamp(Value, -1.0f, 1.0f);

	if(CurrentMatIndex == BlockMaterialPairs.Num())
	{
		CurrentMatIndex = 0;
	}
	else if(CurrentMatIndex == -1)
	{
		CurrentMatIndex = BlockMaterialPairs.Num()-1;
	}
	if(isStartPreview)
	{
		CreateAndSetMaterial(BlockMaterialPairs[CurrentMatIndex].Preview);
	}
	UE_LOG(Log_BC_BuildingComponent, Display, TEXT("CurrentMatIndex: %i"), CurrentMatIndex);
}

void UBC_BuildingComponent::CreateAndSetMaterial(UMaterialInterface* ParentMaterial)
{
		if(IsValid(M_CurrentBlock) && IsValid(GetWorld()) && IsValid(ParentMaterial))
        	{
        		M_CurrentMat = UMaterialInstanceDynamic::Create(ParentMaterial, GetWorld());
        		M_CurrentBlock->BlockMesh->SetMaterial(0, M_CurrentMat);
			    DeltaIndex = CurrentMatIndex;
        	}
}

void UBC_BuildingComponent::SwitchAction()
{
	if(M_CurrentAction == EActionType::Destroy || M_CurrentAction == EActionType::None)
	{
		M_CurrentAction = EActionType::Build;
		M_LightSphereMat->SetVectorParameterValue(FName("Color"), FLinearColor::Green);
	}
	else
	{
		M_CurrentAction =EActionType::Destroy;
		M_LightSphereMat->SetVectorParameterValue(FName("Color"), FLinearColor::Red);
	}
}

void UBC_BuildingComponent::ShangeBlock()
{
	M_CurrentBlockIndex ++;

	if(M_CurrentBlockIndex == BlockClasses.Num())
	{
		M_CurrentBlockIndex = 0;
	}
	else if(M_CurrentBlockIndex == -1)
	{
		M_CurrentBlockIndex = BlockMaterialPairs.Num() - 1;
	}
	if(isStartPreview)
	{
		M_CurrentBlock->Destroy();
		isStartPreview = false;
		isStartBuilding = true;
	}
	
}
