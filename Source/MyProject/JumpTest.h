// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "JumpTest.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AJumpTest : public AFunctionalTest
{
	GENERATED_BODY()

private:

	class ACharacter* Player;

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaSeconds) override;

	bool PlayerHasJumped() const;

};
