// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleProp.h"
#include "AttributeComponent.h"

// Sets default values
ADestructibleProp::ADestructibleProp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Tworzymy Mesh
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	// Tworzymy Komponent Zycia
	AttributeComp = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComp"));

}

// Called when the game starts or when spawned
void ADestructibleProp::BeginPlay()
{
	Super::BeginPlay();

	if (AttributeComp)
	{
		AttributeComp->OnDeath.AddDynamic(this, &ADestructibleProp::OnDeath);
	}
	
}

void ADestructibleProp::GetHit_Implementation(const FVector& ImpactPoint)
{
	if (AttributeComp)
	{
		// Zadajemy obrazenia 
		AttributeComp->ReceiveDamage(50.0f);
	}
}

void ADestructibleProp::OnDeath()
{
	// Niszczymy obiekt
	Destroy();

	UE_LOG(LogTemp, Warning, TEXT("Obiekt zniszczony!"));
}

