// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	public:

	void ActorDied(AActor* DeadActor);
   
protected:

	virtual void BeginPlay() override;
  UFUNCTION(BlueprintImplementableEvent)
  void StartGame();

  UFUNCTION(BlueprintImplementableEvent)
  void GameOver(bool bWonGame);

private:
    UPROPERTY(EditAnywhere,Category = "GameStartComponents")
	float TimeToStart = 4.f;

	void  GameStartTimer();

	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;
    int32 TowersNumber;
	int32 GetTargetOwnerCount();

};

