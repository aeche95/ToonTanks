// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TanksGameModeBase.generated.h"

class APAwnTurret;
class APawnTank;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATanksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	APawnTank* PlayerTank;
	APlayerControllerBase* PlayerControllerRef;
	int32 TargetTurrets = 0;
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);
	int32 GetTurretCount();

public:
	void ActorDied(AActor* DeadActor);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
	int32 StartDelay = 3;
	virtual void BeginPlay();

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);
};
