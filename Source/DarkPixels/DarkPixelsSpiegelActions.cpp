// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkPixelsSpiegelActions.h"


bool LoadAudioFileToArrayLocal(TArray64<uint8>& AudioData, const FString& FilePath)
{
#if UE_VERSION_OLDER_THAN(4, 26, 0)
	TArray<uint8> AudioData32;
	if (!FFileHelper::LoadFileToArray(AudioData32, *FilePath))
	{
		return false;
	}
	AudioData = AudioData32;
#else
	if (!FFileHelper::LoadFileToArray(AudioData, *FilePath))
	{
		return false;
	}
#endif

	// Removing unused two uninitialized bytes
	AudioData.RemoveAt(AudioData.Num() - 2, 2);

	return true;
}


UDarkPixelsSpiegelActions::UDarkPixelsSpiegelActions()
{
    // for(int i=0;i< this->MaxAudioComponents; i++)
    // {
    //     UAudioComponent* Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
    //     Audio->bAutoActivate = false;
    //     Audio->Play();
    //     this->AudioComponentArray.Add(Audio);
    //     break;
    // }
    Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
    Audio->bAutoActivate = false;
}

void UDarkPixelsSpiegelActions::Activate()
{
	UDarkPixelsSpiegelActions::Audio->Play();
}

bool UDarkPixelsSpiegelActions::AdditionalSpiegelFunctionsSet(FString SpiegelEvent, TArray<FString> SpiegelEventArguments)
{
	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, SpiegelEvent);
    bool Result = true;
    if(SpiegelEvent == "SpawnEnemies")
    {
        AActor* OutActor = UCMSFunctionsLibrary::FindActorByClassAndName(AEnemySpawner::StaticClass(), "EnemySpawner");
		AEnemySpawner* EnemySpawner = Cast<AEnemySpawner>(OutActor);
		if (EnemySpawner != nullptr)
		{
            FString EnemyClass = SpiegelEventArguments[0];
            FString StringNumber = SpiegelEventArguments[1];
            FString StringMinRadius = SpiegelEventArguments[2];
            FString StringMaxRadius = SpiegelEventArguments[3];
            FString StringMinConeAngle = SpiegelEventArguments[4];
            FString StringMaxConeAngle = SpiegelEventArguments[5];
            int Number = 0;
            float MinRadius = 0;
            float MaxRadius = 0;
            float MinConeAngle = 0;
            float MaxConeAngle = 0;
            if(StringNumber.IsNumeric())Number = FCString::Atoi(*StringNumber);
            if(StringMinRadius.IsNumeric())MinRadius = FCString::Atof(*StringMinRadius);
            if(StringMaxRadius.IsNumeric())MaxRadius = FCString::Atof(*StringMaxRadius);
            if(StringMinConeAngle.IsNumeric())MinConeAngle = FCString::Atof(*StringMinConeAngle);
            if(StringMaxConeAngle.IsNumeric())MaxConeAngle = FCString::Atof(*StringMaxConeAngle);


			EnemySpawner->SpawnEnemy(EnemyClass,Number,MinRadius,MaxRadius, MinConeAngle, MaxConeAngle);
		}
    }
    else if(SpiegelEvent == "PlayAudio2")
    {
        FString AudioToPlay         = SpiegelEventArguments[0];
        FString AudioObjectFilename = SpiegelEventArguments[1];
        GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString("JOU!!!!!!"));
        // FString AudioFilePath =  FPaths::ProjectContentDir() / TEXT("/Temp/house_lo.mp3");
        FString android_dir = FPaths::ProjectPersistentDownloadDir();
        FString AudioAssetPath = android_dir/"AudioAssets"/AudioObjectFilename;


        //////////////////////////////////
        URuntimeAudioImporterLibrary* RuntimeAudioImporterLibrary = NewObject<URuntimeAudioImporterLibrary>();
        RuntimeAudioImporterLibrary->ImportAudioFromFile(AudioAssetPath, ERuntimeAudioFormat::Auto);

        ERuntimeAudioFormat AudioFormat = RuntimeAudioImporterLibrary->GetAudioFormat(AudioAssetPath);
        TArray64<uint8> AudioData;
        bool loaded = LoadAudioFileToArrayLocal(AudioData, *AudioAssetPath);

        FEncodedAudioStruct EncodedAudioInfo(AudioData, AudioFormat);
        FDecodedAudioStruct DecodedAudioInfo;
        RuntimeAudioImporterLibrary->DecodeAudioData(MoveTemp(EncodedAudioInfo), DecodedAudioInfo);


        UImportedSoundWave* ImportedSoundWave = UImportedSoundWave::CreateImportedSoundWave();
        ImportedSoundWave->PopulateAudioDataFromDecodedInfo(MoveTemp(DecodedAudioInfo));

        // UAudioComponent* Audio = this->AudioComponentArray[this->CurrentAudioComponent];
        // UAudioComponent* Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
        // this->CurrentAudioComponent+=1;
        // this->CurrentAudioComponent %= this->MaxAudioComponents;


        // Audio->SetupAttachment(RootComponent);


        // this->AudioComponentMap.Emplace(AudioToPlay, Audio);

        Audio->SetSound(ImportedSoundWave);
        Audio->Play(0);
        RuntimeAudioImporterLibrary = nullptr;

    }
    else if(SpiegelEvent == "StopAudio")
    {
        FString AudioToStop = SpiegelEventArguments[0];
        // Audio = this->AudioComponentMap[AudioToStop];
        Audio->Stop();

    }
    else
    {
        Result = false;
    }

    return Result;

}
