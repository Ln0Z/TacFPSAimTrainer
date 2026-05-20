// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TacFPSCharacter.generated.h"

UCLASS()
class TACFPSAIMTRAINER_API ATacFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATacFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Air Strafe")
	float AirStrafeStrength = 120.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Air Strafe")
	float MaxAirStrafeSpeed = 900.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Air Strafe")
	bool bEnableAirStrafe = true;

	void MoveRight(float Value);

	void MoveForward(float Value);

	void Turn(float Value);

	void LookUp(float Value);

};
