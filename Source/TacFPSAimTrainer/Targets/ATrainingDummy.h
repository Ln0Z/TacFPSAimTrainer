// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTarget.h"
#include "ATrainingDummy.generated.h"

/**
 * 
 */



UCLASS()
class TACFPSAIMTRAINER_API AATrainingDummy : public ABaseTarget
{
	GENERATED_BODY()
private:
	bool EndGame = false;
	float TimeSinceLastTrace;


public:
	virtual void Tick(float DeltaTime) override;

	void CreateLineTrace();

};
