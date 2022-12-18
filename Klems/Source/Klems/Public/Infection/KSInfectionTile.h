// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/KSCharacter.h"
#include "GameFramework/Actor.h"
#include "KSInfectionTile.generated.h"

UCLASS(Blueprintable)
class KLEMS_API AKSInfectionTile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AKSInfectionTile();

	UFUNCTION(BlueprintCallable)
	void addInfectionDensity(float newValue);
	
	UFUNCTION()
	void OnRep_InfectionDensity(float LastInfectionDensity);

	UPROPERTY(BlueprintReadWrite, Category = "Material")
	UMaterialInstanceDynamic* TileDynamicMat = nullptr;

	UPROPERTY(BlueprintReadWrite, Replicated, ReplicatedUsing=OnRep_InfectionDensity)
	float InfectionDensity = 0;

	UFUNCTION()
	void InfectPlayer(AKSCharacter* Player);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void ServerInfectPlayer(AKSCharacter* Player);

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> Tile;

private:

	UFUNCTION()
	void SetInfection(float InfectDensity = 0);

	UFUNCTION(BlueprintCallable)    
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
