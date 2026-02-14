// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatInterface.h"
#include "DestructibleProp.generated.h"

class UAttributeComponent;

UCLASS()
class DZ_CPP_API ADestructibleProp : public AActor, public ICombatInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleProp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Komponent wizualny
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	// Komponent zycia
	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* AttributeComp;

	// Funkcja z interfejsu 
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

	// Funkcja, która odpali siê, gdy HP spadnie do 0
	UFUNCTION()
	void OnDeath();
};
