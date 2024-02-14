// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToomTankGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToomTankGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	void ActorDied(AActor* DeadActor);

private:
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;

	float StartDelay = 3.f;

	int32 TargetTowers = 0;

private:
	void HandleGameStart();
	int32 GetTargetTowerCount();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);
};
