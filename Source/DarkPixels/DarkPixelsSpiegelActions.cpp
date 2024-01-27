// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkPixelsSpiegelActions.h"

bool UDarkPixelsSpiegelActions::AdditionalSpiegelFunctionsSet(FString SpiegelEvent, TArray<FString> SpiegelEventArguments)
{

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
    else
    {
        Result = false;
    }

    return Result;

}
