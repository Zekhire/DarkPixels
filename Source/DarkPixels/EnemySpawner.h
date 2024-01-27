// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpiegelElement.h"
#include "EnemySpawner.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DARKPIXELS_API AEnemySpawner : public ASpiegelElement
{
	GENERATED_BODY()
	public:

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable )
	void SpawnEnemy(const FString &EnemyClass, int Number, float MinRadiusDistance, float MaxRadiusDistance, float MinConeAngle, float MaxConeAngle);
};
