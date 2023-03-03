#include "Blocks/BC_C_BaseBlock.h"


ABC_C_BaseBlock::ABC_C_BaseBlock()
{
	PrimaryActorTick.bCanEverTick = true;

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>("BlockMesh");
	SetRootComponent(BlockMesh);

}


void ABC_C_BaseBlock::BeginPlay()
{
	Super::BeginPlay();
	M_FXEmitPower = FadeTime;
}


void ABC_C_BaseBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(M_StartFadeEmit)
	{
		if(M_FXEmitPower > 0)
		{
			M_FXEmitPower -= DeltaTime;
			const float Power = M_FXEmitPower * (M_ResetRiseEmit ? RisePowerMult : FadePowerMult);
			ChangeEmitPower(Power);
		}
		else
		{
			ResetEmitToZero();
		}
	}
	else if(M_StartRiseEmit)
	{
		if(M_FXEmitPower < RiseTime)
		{
			M_FXEmitPower += DeltaTime;
			ChangeEmitPower(M_FXEmitPower * RisePowerMult);
		}
		else
		{
			Destroy();
		}
	}

}

void ABC_C_BaseBlock::OnEndBuilding()
{
	M_StartFadeEmit = true;

	if(IsValid(BlockMesh) && IsValid(BlockMesh->GetMaterial(0)))
	{
		M_BlockDynMat = Cast<UMaterialInstanceDynamic>(BlockMesh->GetMaterial(0));
	}
}

void ABC_C_BaseBlock::ChangeEmitPower(float Power)
{
	if(!IsValid(M_BlockDynMat)) return;
	M_BlockDynMat->SetScalarParameterValue(FName("Emit Power"), Power * Power);
}

void ABC_C_BaseBlock::ResetEmitToZero()
{
	ChangeEmitPower(0.0f);
	M_FXEmitPower = 0.0f;
	M_StartFadeEmit = false;
}

void ABC_C_BaseBlock::OnStartDestroy()
{
	if(!IsValid(this)) return;
	M_StartFadeEmit = false;
	M_StartRiseEmit = true;
	M_ResetRiseEmit = false;
}

void ABC_C_BaseBlock::OnResetDestroy()
{
	if(!IsValid(this)) return;
	M_StartFadeEmit = true;
	M_StartRiseEmit = false;
	M_ResetRiseEmit = true;
}

