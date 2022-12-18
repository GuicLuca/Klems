// Fill out your copyright notice in the Description page of Project Settings.


#include "Klems/Public/Infection/KSInfectionTile.h"

#include "Character/KSCharacter.h"
#include "GameplayTags/KSGameplayTags.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AKSInfectionTile::AKSInfectionTile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	Tile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile"));
	Tile->SetupAttachment(RootComponent);
	//Tile->OnComponentHit.AddDynamic(this, &AKSInfectionTile::OnCompHit);
}

void AKSInfectionTile::addInfectionDensity(float newValue)
{
	if(!HasAuthority()) return;

	if(InfectionDensity >= 1) return;

	this->InfectionDensity = this->InfectionDensity+newValue;

	SetInfection(InfectionDensity);
}

void AKSInfectionTile::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	DOREPLIFETIME( AKSInfectionTile, InfectionDensity );
}

void AKSInfectionTile::SetInfection(float InfectDensity)
{
	
	if(!TileDynamicMat) return;

	TileDynamicMat->SetScalarParameterValue(FName("InfectionDensity"),InfectDensity);
	
}

void AKSInfectionTile::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AKSCharacter* PlayerHit= Cast<AKSCharacter>(OtherActor);
	InfectPlayer(PlayerHit);
}

void AKSInfectionTile::OnRep_InfectionDensity(float LastInfectionDensity)
{
	SetInfection(InfectionDensity);
}

void AKSInfectionTile::InfectPlayer(AKSCharacter* Player)
{
	ServerInfectPlayer(Player);
}

void AKSInfectionTile::ServerInfectPlayer_Implementation(AKSCharacter* Player)
{
	if(!HasAuthority()) return;

	auto InfectionAttribute = Player->Attributes->GetAttribute(TAG_Attribute_Infection);

	if(!ensureAlwaysMsgf(InfectionAttribute, TEXT("No infection attribute, your character is ill formated !"))) return;

	InfectionAttribute->SetCurrentValue(InfectionAttribute->GetCurrentValue()+this->InfectionDensity);
		
}

// Called when the game starts or when spawned
void AKSInfectionTile::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInterface* objectMaterial = this->Tile->GetMaterial(0);

	this->TileDynamicMat = UMaterialInstanceDynamic::Create(objectMaterial, Tile);

	this->Tile->SetMaterial(0,TileDynamicMat);

	SetInfection();
}

