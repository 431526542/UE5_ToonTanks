// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

ATower::ATower()
{
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//find the distance to the tank
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		//UE_LOG(LogTemp, Display, TEXT("%f"), Distance);
		//check to see if the tank is in range
		if (Distance <= FireRange)
		{
			RotateTurret(Tank->GetActorLocation());
		}
		//if in range, rotate turrent toward tank
	}
	}
