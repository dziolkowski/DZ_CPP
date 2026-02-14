// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"
#include "AItem.generated.h"

UCLASS()
class DZ_CPP_API AAItem : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAItem();

protected:
	// Mesh przedmiotu, zeby byl widoczny
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	class UStaticMeshComponent* ItemMesh;

public:	
	// Implementacja funkcji z interfejsu
	virtual void Interact_Implementation(class ADZ_CPPCharacter* Character) override;

	// Wirtualna funkcja PickUp wymagana w zadaniu
	virtual void PickUp(class ADZ_CPPCharacter* Character);

};
