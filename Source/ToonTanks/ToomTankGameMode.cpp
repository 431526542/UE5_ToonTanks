// Fill out your copyright notice in the Description page of Project Settings.


#include "ToomTankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"
#include "TimerManager.h"

void AToomTankGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToomTankGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		--TargetTowers;
		if (TargetTowers == 0)
		{
			GameOver(true);
		}
	}
}

void AToomTankGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController =
		Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;

		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			StartDelay,
			false);
	}
}

int32 AToomTankGameMode::GetTargetTowerCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

	return Towers.Num();
}
