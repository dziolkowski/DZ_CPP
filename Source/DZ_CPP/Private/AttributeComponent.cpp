// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// Wartosci domyslne
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	
}


void UAttributeComponent::ReceiveDamage(float Damage)
{
	// Odejmujemy HP
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);

	UE_LOG(LogTemp, Warning, TEXT("Otrzymano obrazenia. HP: %f"), CurrentHealth);

	// Jesli HP spadlo do 0, oglaszamy smierc
	if (CurrentHealth <= 0.0f)
	{
		OnDeath.Broadcast();
	}
}

float UAttributeComponent::GetHealthPercent() const
{
	return CurrentHealth / MaxHealth;
}

bool UAttributeComponent::IsAlive() const
{
	return CurrentHealth > 0.0f;
}

