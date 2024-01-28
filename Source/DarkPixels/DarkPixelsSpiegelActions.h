// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sound/SoundWave.h"
#include "Sound/SoundCue.h"
#include "UObject/ConstructorHelpers.h"
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
	UDarkPixelsSpiegelActions();

	int MaxAudioComponents = 1024;
	int CurrentAudioComponent = 0;
	TMap<FString, URuntimeAudioImporterLibrary*> RuntimeAudioImporterLibraryMap;
	TArray<UAudioComponent*> AudioComponentArray;
	TMap<FString, UAudioComponent*> AudioComponentMap;
	TMap<FString, UImportedSoundWave*> ImportedSoundWaveMap;
	TMap<FString, bool> loadedMap;

	UAudioComponent* Audio;
	// UAudioComponent* Audio;
	// UImportedSoundWave* ImportedSoundWave;
	// bool loaded;
	// bool done;
	virtual void Activate();


	virtual bool AdditionalSpiegelFunctionsSet(FString SpiegelEvent, TArray<FString> SpiegelEventArguments) override;


	//UFUNCTION()
	//void SpawnEnemies(TArray<FString> SpiegelEventArguments);



};
