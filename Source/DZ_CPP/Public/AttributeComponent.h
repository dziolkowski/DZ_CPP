// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

// Definicja Delegata (Broadcastu) - to pozwoli powiadomiæ inne systemy o œmierci
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DZ_CPP_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAttributeComponent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Attributes")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, Category = "Attributes")
	float CurrentHealth;

public:
	// Delegat, ktory "wykrzyczy", ze wlasciciel umarl
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnDeathSignature OnDeath;

	// Wymagane: Funkcja zadajaca obrazenia
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void ReceiveDamage(float Damage);

	// Wymagane: Gettery i Settery (proste funkcje dostepu)
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHealthPercent() const;

	bool IsAlive() const;
};
