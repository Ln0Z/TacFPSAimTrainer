// Fill out your copyright notice in the Description page of Project Settings.


#include "ATrainingDummy.h"
#include "../Characters/TacFPSCharacter.h"
#include "Camera/CameraComponent.h"


void AATrainingDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeSinceLastTrace += DeltaTime;

	if (TimeSinceLastTrace >= 3.0f)
	{
		CreateLineTrace();
		TimeSinceLastTrace = 0.0f;
	}

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("EndGame: %s"),
		EndGame ? TEXT("true") : TEXT("false")
	);
}

void AATrainingDummy::CreateLineTrace()
{
	UCameraComponent* cam = this->FindComponentByClass<UCameraComponent>();

	if (!cam) return;

	FVector StartP = cam->GetComponentLocation();
	FVector Dir = cam->GetForwardVector();

	FVector EndP = StartP + (1500.0f * Dir);

	DrawDebugLine(
		GetWorld(),
		StartP,
		EndP,
		FColor::Green,
		false,
		1.0f,
		0,
		3.0f
	);

	UE_LOG(LogTemp, Warning, TEXT("Start: %s"), *StartP.ToString());
	UE_LOG(LogTemp, Warning, TEXT("End: %s"), *EndP.ToString());

	FCollisionQueryParams Params;

	Params.AddIgnoredActor(this);

	FHitResult Hit;
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		StartP,
		EndP,
		ECC_Visibility,
		Params
	);

	UE_LOG(LogTemp, Warning, TEXT("bHit: %s"), bHit ? TEXT("true") : TEXT("false"));

	if (bHit) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *Hit.GetActor()->GetName());
		UE_LOG(LogTemp, Warning, TEXT("Hit Class: %s"), *Hit.GetActor()->GetClass()->GetName());
		UE_LOG(LogTemp, Warning, TEXT("Parent Class: %s"), *Hit.GetActor()->GetClass()->GetSuperClass()->GetName());

		AActor* HitActor = Hit.GetActor();

		ATacFPSCharacter* actor = Cast<ATacFPSCharacter>(HitActor);

		EndGame = actor != nullptr;
	}
}