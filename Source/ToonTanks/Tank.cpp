// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.f, 12, FColor::Red, false, -1.f);
		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float Value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = MoveSpeed * Value * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotator = FRotator::ZeroRotator;
	DeltaRotator.Yaw = TurnRate *Value *UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotator, true);
}
