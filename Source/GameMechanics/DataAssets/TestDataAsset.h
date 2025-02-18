// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TestDataAsset.generated.h"

/**
 * 
 */

USTRUCT()
struct FTestAssetInfo 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString AssetName;

	UPROPERTY(EditAnywhere)
	UTexture2D* AssetThumbnail;

	UPROPERTY(EditAnywhere)
	UStaticMesh* AssetStaticMesh;
};



UCLASS()
class GAMEMECHANICS_API UTestDataAsset : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FTestAssetInfo> AssetItems;
	
public:
	//UPROPERTY(EditAnywhere)
	//UInputAction*
};
