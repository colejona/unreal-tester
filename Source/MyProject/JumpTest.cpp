// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpTest.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void AJumpTest::BeginPlay()
{
	Super::BeginPlay();

	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (Player)
	{
		InitialLocation = Player->GetActorLocation();
	}
}

void AJumpTest::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!Player)
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Invalid player character!"));
	}

	//Go forward until we reach our destination
	Player->AddMovementInput(Player->GetActorForwardVector());
	if (TraveledTotalDistance())
	{
		FinishTest(EFunctionalTestResult::Succeeded,FString("Traveled required units!"));
		UKismetSystemLibrary::QuitGame(GetWorld(),UGameplayStatics::GetPlayerController(GetWorld(),0),EQuitPreference::Quit,false);
	}
}

bool AJumpTest::TraveledTotalDistance() const
{
	return (Player) ? (FVector::Distance(Player->GetActorLocation(), InitialLocation + Player->GetActorForwardVector() * MovementDistance) <= DistanceThreshold) : false;
}
