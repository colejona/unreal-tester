// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpTest.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void AJumpTest::BeginPlay()
{
	Super::BeginPlay();

	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!Player)
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Invalid player character!"));
	}

	if (Player->JumpCurrentCount != 0)
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Player jump count should be 0"));
	}

	Player->Jump();
}

void AJumpTest::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (PlayerHasJumped())
	{
		FinishTest(EFunctionalTestResult::Succeeded,FString("Reached jump apex!"));
		UKismetSystemLibrary::QuitGame(GetWorld(),UGameplayStatics::GetPlayerController(GetWorld(),0),EQuitPreference::Quit,false);
	}
}

bool AJumpTest::PlayerHasJumped() const
{
	return Player->JumpCurrentCount > 0;
}
