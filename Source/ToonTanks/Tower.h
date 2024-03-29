// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	ATower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRange = 700.f;

	class ATank* Tank;
	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;

private:
	void CheckFireCondition();
	bool InFireRange();
	
public:
	void HandleDestruction();
};
