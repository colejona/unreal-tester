#include "MyFunctionalTest.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void AMyFunctionalTest::BeginPlay()
{
	Super::BeginPlay();


	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);

	if (Player)
	{
		InitialLocation = Player->GetActorLocation();
	}
}

void AMyFunctionalTest::Tick(float DeltaSeconds)
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

bool AMyFunctionalTest::TraveledTotalDistance() const
{
	return (Player) ? (FVector::Distance(Player->GetActorLocation(), InitialLocation + Player->GetActorForwardVector() * MovementDistance) <= DistanceThreshold) : false;
}
