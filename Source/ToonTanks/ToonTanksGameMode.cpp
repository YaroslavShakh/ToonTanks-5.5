// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if (ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnableState(false);
            GameOver(false);
        }
    }
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {   
        TowersNumber -= 1;
        DestroyedTower->HandleDestruction();
        if(TowersNumber==0)
        {
            GameOver(true);
        } 
    }
}



void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    GameStartTimer();

}


void AToonTanksGameMode:: GameStartTimer()
{
    TowersNumber = GetTargetOwnerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController> (UGameplayStatics::GetPlayerController(this,0));
    StartGame();    
    if(ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnableState(false);
        FTimerHandle StartGameTimer;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnableState,
            true
            );
       GetWorldTimerManager().SetTimer(
              StartGameTimer,
           PlayerEnableTimerDelegate, 
               TimeToStart,
              false
            );

    }
    
}

int32  AToonTanksGameMode::GetTargetOwnerCount()
{
    TArray<AActor*> Towers; 
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(),Towers);
    return Towers.Num();
}