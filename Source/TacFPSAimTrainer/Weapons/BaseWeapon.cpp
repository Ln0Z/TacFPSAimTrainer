// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"
#include "../TacFPSCharacter.h"
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

	FVector startP = cam->GetComponentLocation();
	FVector dir = cam->GetForwardVector();

	FVector endP = (this->range * dir) + startP;

	DrawDebugLine(
		GetWorld(),
		startP,
		endP,
		FColor::Green,
		false,
		2.0f
	);


}