// Fill out your copyright notice in the Description page of Project Settings.


#include "TanksGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

void ATanksGameModeBase::BeginPlay() 
{
    Super::BeginPlay();
    HandleGameStart();
}

void ATanksGameModeBase::ActorDied(AActor* DeadActor) 
{
    if(DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction();
        HandleGameOver(false);

        if(PlayerControllerRef)
        {
            PlayerControllerRef->SetPlayerEnabledState(false);
        }
    }
    else if(APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
    {
        DestroyedTurret->HandleDestruction();
        if(--TargetTurrets == 0)
        {
            PlayerControllerRef->SetPlayerEnabledState(false);
            HandleGameOver(true);
        }
    }
}

void ATanksGameModeBase::HandleGameStart() 
{
    TargetTurrets = GetTurretCount();

    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this,0));
    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this,0));
    GameStart();
    if(PlayerControllerRef)
        {
            PlayerControllerRef->SetPlayerEnabledState(false);

            FTimerHandle PlayerEnableHandle;
            FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef,&APlayerControllerBase::SetPlayerEnabledState,true);
            GetWorldTimerManager().SetTimer(PlayerEnableHandle,PlayerEnableDelegate,StartDelay,false);
        }
}

void ATanksGameModeBase::HandleGameOver(bool PlayerWon) 
{
    GameOver(PlayerWon);
}

int32 ATanksGameModeBase::GetTurretCount() 
{
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
    return TurretActors.Num();
}


