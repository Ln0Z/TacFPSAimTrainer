// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"
#include "../Characters/TacFPSCharacter.h"
#include "../Targets/BaseTarget.h"
#include "Camera/CameraComponent.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseWeapon::SetWeaponOwner(ATacFPSCharacter* actor) {
	WeaponOwner = actor;
}

ATacFPSCharacter* ABaseWeapon::GetWeaponOwner()
{
	return this->WeaponOwner;
}

void ABaseWeapon::FireWeapon() {

	if (!this) return;

	if (CanShoot) {
		CanShoot = false;
		IsFiring = true;
		CreateLineTrace();
	}

	CanShoot = true;
	IsFiring = false;
}

void ABaseWeapon::CreateLineTrace() {
	if (!WeaponOwner) return;

	UCameraComponent* cam = WeaponOwner->FindComponentByClass<UCameraComponent>();

	if (!cam) return;

	FVector StartP = cam->GetComponentLocation();
	FVector Dir = cam->GetForwardVector();

	FVector EndP = (this->Range * Dir) + StartP;

	FCollisionQueryParams Params;

	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(this->GetWeaponOwner());

	DrawDebugLine(
		GetWorld(),
		StartP,
		EndP,
		FColor::Green,
		false,
		2.0f
	);

	TArray<FHitResult> Hits;

	bool bHit = GetWorld()->LineTraceMultiByChannel(
		Hits,
		StartP,
		EndP,
		ECC_Visibility,
		Params
	);

	if (bHit)
	{
		for(FHitResult& Hit : Hits)
		{
			AActor* HitActor = Hit.GetActor();

			ABaseTarget* actor = Cast<ABaseTarget>(HitActor);

			if (actor) {
				actor->Destroy();
			}
		}
	}

}