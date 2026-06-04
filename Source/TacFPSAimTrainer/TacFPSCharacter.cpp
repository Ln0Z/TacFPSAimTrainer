// Fill out your copyright notice in the Description page of Project Settings.


#include "TacFPSCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ATacFPSCharacter::ATacFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true; 
    bUseControllerRotationYaw = true;
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;

}

// Called when the game starts or when spawned
void ATacFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATacFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATacFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(
        "MoveForward",
        this,
        &ATacFPSCharacter::MoveForward
    );

    PlayerInputComponent->BindAxis(
        "MoveRight",
        this,
        &ATacFPSCharacter::MoveRight
    );


    PlayerInputComponent->BindAxis(
        "Turn", 
        this, 
        &ATacFPSCharacter::Turn
    );
    
    PlayerInputComponent->BindAxis(
        "LookUp", 
        this, 
        &ATacFPSCharacter::LookUp
    );

    PlayerInputComponent->BindAction(
        "Jump",
        IE_Pressed,
        this,
        &ACharacter::Jump
    );

    PlayerInputComponent->BindAction(
        "Jump",
        IE_Released,
        this,
        &ACharacter::StopJumping
    );
}

void ATacFPSCharacter::MoveRight(float Value)
{
    if (!Controller || FMath::IsNearlyZero(Value))
    {
        return;
    }

    const FRotator ControlRotation = Controller->GetControlRotation();
    const FRotator YawRotation(0.0f, ControlRotation.Yaw, 0.0f);

    const FVector RightDirection =
        FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    AddMovementInput(RightDirection, Value);

    if (bEnableAirStrafe && GetCharacterMovement()->IsFalling())
    {
        const FVector Velocity = GetVelocity();
        const FVector HorizontalVelocity(Velocity.X, Velocity.Y, 0.0f);

        if (HorizontalVelocity.Size() < MaxAirStrafeSpeed)
        {
            LaunchCharacter(
                RightDirection * Value * AirStrafeStrength,
                false,
                false
            );
        }
    }
}

void ATacFPSCharacter::MoveForward(float Value)
{
    if (!Controller || FMath::IsNearlyZero(Value))
    {
        return;
    }

    const FRotator ControlRotation = Controller->GetControlRotation();
    const FRotator YawRotation(0.0f, ControlRotation.Yaw, 0.0f);

    const FVector ForwardDirection =
        FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

    AddMovementInput(ForwardDirection, Value);
}

void ATacFPSCharacter::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void ATacFPSCharacter::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}