// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputDataConfig.generated.h"

/**
 * 
 */
UCLASS()
class GAMEMECHANICS_API UInputDataConfig : public UDataAsset
{
	GENERATED_BODY()
	

	
public:
	// Remember to write class in front of UInputAction

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* IA_Move;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* IA_Look;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* IA_Jump;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* IA_Shoot;
	
}; 
