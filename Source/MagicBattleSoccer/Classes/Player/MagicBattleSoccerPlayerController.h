

#pragma once

#include "GameFramework/PlayerController.h"
#include "MagicBattleSoccerPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MAGICBATTLESOCCER_API AMagicBattleSoccerPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

private:
	int64 timeServerTimeRequestWasPlaced;
	int64 timeOffsetFromServer;
	bool timeOffsetIsValid;

	/** Gets the game state */
	class AMagicBattleSoccerGameState* GetGameState();

public:

	/** stores pawn location at last player death, used where player scores a kill after they died **/
	FVector LastDeathLocation;

	/** True if the network time is valid. */
	bool IsNetworkTimeValid();

	/** Gets the current system time in milliseconds */
	static int64 GetLocalTime();

	/** Gets the approximate current network time in milliseconds. */
	int64 GetNetworkTime();

	/** Not null if we need to synchronize the character rotation with the weapon aim next time Tick is called */
	AMagicBattleSoccerWeapon* WeaponToSyncCharacterRotationWith;

	//Begin AController interface

	/** sets up input */
	virtual void SetupInputComponent() override;

	/** This occurs when play begins */
	virtual void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	/** update camera when pawn dies */
	virtual void PawnPendingDestroy(APawn* inPawn) override;

	//End AController interface

	/** try to find spot for death cam */
	bool FindDeathCameraSpot(FVector& CameraLocation, FRotator& CameraRotation);

	/** Determines whether the character can be spawned at this time */
	UFUNCTION(BlueprintCallable, Category = Soccer)
	bool CanSpawnCharacter();

	/** Spawns the character */
	UFUNCTION(BlueprintNativeEvent, Category = Soccer)
	void SpawnCharacter();

	UFUNCTION(reliable, server, WithValidation)
	void ServerSpawnCharacter();

	void TrySyncCharacterRotationToWeaponAim(AMagicBattleSoccerWeapon *Weapon);

	UFUNCTION(reliable, server, WithValidation)
	void ServerForceActorRotation(FRotator rotation);

	//////////////////////////////////////////////////////////////////////////
	// Input handlers

	/** Player move forward event */
	void OnMoveForward(float axisValue);

	/** Player move right event */
	void OnMoveRight(float axisValue);

	/** Player primary action event */
	void OnStartPrimaryAction();

	/** Player primary action event */
	void OnStopPrimaryAction();

	/** Player secondary action event */
	void OnStartSecondaryAction();

	/** Player secondary action event */
	void OnStopSecondaryAction();

	/** Player suicide event */
	void OnSuicide();

	/** Player respawn event */
	void OnRespawn();

	/** Next round event (for debugging only) */
	void OnNextRound();

	/** Quit to the main menu (TODO: Remove as a direct command) */
	void OnQuitToMainMenu();

protected:
	/** Sent from a client to the server to get the server's system time */
	UFUNCTION(reliable, server, WithValidation)
	void ServerGetServerTime();

	/** Sent from the server to a client to give them the server's system time */
	UFUNCTION(reliable, client)
	void ClientGetServerTime(int64 serverTime);

	/** Sent from a client to the server to set the client's player name. We don't use
	any sort of known online subsystem so we do it this way */
	UFUNCTION(reliable, server, WithValidation)
	void ServerSetPlayerName(const FString& PlayerName);
};
