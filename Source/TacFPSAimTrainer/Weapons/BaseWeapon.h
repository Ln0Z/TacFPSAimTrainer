// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class ATacFPSCharacter;

UCLASS()
class TACFPSAIMTRAINER_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

private: 
	UPROPERTY(VisibleAnywhere)
	ATacFPSCharacter* WeaponOwner;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanShoot = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFiring = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetWeaponOwner(ATacFPSCharacter* actor);
	ATacFPSCharacter* GetWeaponOwner();

	void FireWeapon();
	void CreateLineTrace();
};