// Fill out your copyright notice in the Description page of Project Settings.


#include "AItem.h"
#include "Components/StaticMeshComponent.h"
#include "DZ_CPPCharacter.h"

// Sets default values
AAItem::AAItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMesh;

	// Ustawiamy kolizjê tak, by blokowala promienie (LineTrace) interakcji
	ItemMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));

}

void AAItem::Interact_Implementation(ADZ_CPPCharacter* Character)
{
	// Kiedy gracz wchodzi w interakcjê, wywo³ujemy PickUp
	PickUp(Character);
}

void AAItem::PickUp(ADZ_CPPCharacter* Character)
{
	// Domyœlna implementacja (mo¿e byæ pusta lub logowaæ coœ)
	UE_LOG(LogTemp, Warning, TEXT("Podniesiono przedmiot: %s"), *GetName());


	Destroy(); 
}

