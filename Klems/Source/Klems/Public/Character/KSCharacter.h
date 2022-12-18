#pragma once

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
	UFUNCTION()
	void SetInfectedMode();

	UFUNCTION(BlueprintCallable)
	void addInfection();

	UFUNCTION(BlueprintCallable)
	void startInfection();

	UFUNCTION(BlueprintNativeEvent)
	void stopInfection();

	UFUNCTION(BlueprintNativeEvent)
	void ShowTabUI();

	UFUNCTION(BlueprintNativeEvent)
	void HideTabUI();
	
	UPROPERTY(VisibleAnywhere, Category = "Ability")
	TObjectPtr<UASAbilityComponent> AbilityComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Attribute")
	TObjectPtr<UASAttributeSetComponent> Attributes;


	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Combat")
	TObjectPtr<UKSCombatComponent> CombatComponent;

	UPROPERTY(EditDefaultsOnly)
	TArray<FGameplayTag> AbilitiesRemovedByInfection;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UASAbility>> AbilitiesGrantedByInfection;

	UPROPERTY(BlueprintReadWrite, Replicated, ReplicatedUsing=OnRep_InfectDensity)
	float InfectionDensity = 0;

	UFUNCTION()
	void OnRep_InfectDensity();

	UPROPERTY(BlueprintReadWrite, Replicated)
	float Health = 100;

	
protected:
	
	UFUNCTION()
	void OnSpeedChanged(float OldValue, float NewValue);
	
	UFUNCTION()
	void OnInfectChanged(float OldValue, float NewValue);

	UFUNCTION()
	void OnHealthChanged(float OldValue, float NewValue);

	UFUNCTION(Server, Reliable)
	void ServerSetInfectedMode();

	
	
	virtual void BeginPlay() override;

	void InputMove(const FInputActionValue& InputActionValue);

	void InputLook(const FInputActionValue& InputActionValue);

	void InputJump(const FInputActionValue& InputActionValue);

	void InputCrouch(const FInputActionValue& InputActionValue);

	void InputRun(const FInputActionValue& InputActionValue);

	void InputShoot(const FInputActionValue& InputActionValue);

	void InputReload(const FInputActionValue& InputActionValue);

	void InputPunch(const FInputActionValue& InputActionValue);
	
	void InputTab(const FInputActionValue& InputActionValue);
	


	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> FPSMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UKSInputConfig* InputConfig;

	UPROPERTY(BlueprintReadWrite, Category="Pseudo")
	FString pseudo;

private:
	FTimerHandle MemberTimerHandle;
	
};

