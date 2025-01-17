﻿#pragma once

#include "CoreMinimal.h"
#include "Ability/ASAbilityComponent.h"
#include "InputActionValue.h"
#include "Attribute/ASAttributeSetComponent.h"
#include "GameFramework/Character.h"
#include "KSCharacter.generated.h"

class UKSCombatComponent;
class UCameraComponent;
class UKSInputConfig;
struct FInputActionValue;

UCLASS()
class KLEMS_API AKSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AKSCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	UCameraComponent* GetCamera() { return Camera; }

	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent * GetFPSMesh() {return FPSMesh;}
	
	UFUNCTION(BlueprintCallable)
	void SetInfectedMode();

	UFUNCTION(BlueprintCallable)
	void addInfection();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void startInfection();

	UFUNCTION(BlueprintNativeEvent)
	void stopInfection();

	UFUNCTION(BlueprintNativeEvent)
	void Die();

	UFUNCTION(BlueprintNativeEvent)
	void Shoot();

	UFUNCTION(BlueprintNativeEvent)
	void Reload();

	UFUNCTION(BlueprintNativeEvent)
	void TakeHit();

	UFUNCTION(BlueprintNativeEvent)
	void DisplayHitMarker();

	UFUNCTION(BlueprintNativeEvent)
	void DisplayHeadShot();
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Ability")
	TObjectPtr<UASAbilityComponent> AbilityComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Attribute")
	TObjectPtr<UASAttributeSetComponent> Attributes;


	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Combat")
	TObjectPtr<UKSCombatComponent> CombatComponent;

	UPROPERTY(EditDefaultsOnly)
	TArray<FGameplayTag> AbilitiesRemovedByInfection;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UASAbility>> AbilitiesGrantedByInfection;

	UPROPERTY(BlueprintReadWrite, Replicated, ReplicatedUsing=OnRep_InfectionDensityChanged);
	float InfectionDensity = 0;

	UPROPERTY(BlueprintReadWrite, Replicated, ReplicatedUsing=OnRep_HealthChanged);
	float Health = 100;

	UPROPERTY(BlueprintReadWrite, Replicated, ReplicatedUsing=OnRep_HitCountChanged);
	float HitCount = 0;

	UPROPERTY(BlueprintReadWrite, Replicated, ReplicatedUsing=OnRep_HeadShotCountChanged);
	float HeadShotCount = 0;

	UPROPERTY(BlueprintReadWrite)
	bool bRunning = false;

	UFUNCTION()
	void OnRep_InfectionDensityChanged();

	UFUNCTION()
	void OnRep_HealthChanged();

	UFUNCTION()
	void OnRep_HitCountChanged();

	UFUNCTION()
	void OnRep_HeadShotCountChanged();

	/*
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void DecrementHealth(float amount);
	*/
	
	UFUNCTION(BlueprintNativeEvent)
	void OnAmmoChanged(int32 OldValue, int32 NewValue);

protected:
	
	UFUNCTION()
	void OnSpeedChanged(float OldValue, float NewValue);

	UFUNCTION()
	void OnHealthChanged(float OldValue, float NewValue);
	
	UFUNCTION()
	void OnInfectChanged(float OldValue, float NewValue);

	UFUNCTION()
	void OnHitCountChanged(float OldValue, float NewValue);

	UFUNCTION()
	void OnHeadShotCountChanged(float OldValue, float NewValue);
	
	virtual void BeginPlay() override;

	void InputMove(const FInputActionValue& InputActionValue);

	void InputLook(const FInputActionValue& InputActionValue);

	void InputJump(const FInputActionValue& InputActionValue);

	void InputCrouch(const FInputActionValue& InputActionValue);

	void InputRun(const FInputActionValue& InputActionValue);

	void InputShoot(const FInputActionValue& InputActionValue);

	void InputReload(const FInputActionValue& InputActionValue);

	void InputPunch(const FInputActionValue& InputActionValue);

	UFUNCTION(BlueprintNativeEvent)
	void StartRun();

	UFUNCTION(BlueprintNativeEvent)
	void StopRun();
	

	UPROPERTY(VisibleAnywhere, Category="Camera", Replicated)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> FPSMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UKSInputConfig* InputConfig;

	UPROPERTY(BlueprintReadWrite, Category="Pseudo")
	FString pseudo;

	UPROPERTY(BlueprintReadWrite)
	bool bIsInfected = false;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float Sensitivity;

private:
	FTimerHandle MemberTimerHandle;
	
};

