// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "CMSFunctionsLibrary.h"
#include "EnemySpawner.h"
#include "ExternalSpiegelFunctionsSet.h"
#include "DarkPixelsSpiegelActions.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DARKPIXELS_API UDarkPixelsSpiegelActions : public UExternalSpiegelFunctionsSet
{
	GENERATED_BODY()

public:

	virtual bool AdditionalSpiegelFunctionsSet(FString SpiegelEvent, TArray<FString> SpiegelEventArguments) override;


	//UFUNCTION()
	//void SpawnEnemies(TArray<FString> SpiegelEventArguments);



};
