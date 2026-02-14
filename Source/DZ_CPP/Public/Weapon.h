// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AItem.h"
#include "Weapon.generated.h"

class UBoxComponent;
class ADZ_CPPCharacter;
/**
 * 
 */
UCLASS()
class DZ_CPP_API AWeapon : public AAItem
{
	GENERATED_BODY()

public:
	AWeapon();
	virtual void PickUp(ADZ_CPPCharacter* TargetCharacter) override;

protected:
	// To jest wymagane w zadaniu: Component kolizji
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UBoxComponent* WeaponBox;

	// To jest wymagane w zadaniu: Punkty do BoxTraceSingle
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	USceneComponent* TraceStart;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	USceneComponent* TraceEnd;

	// Funkcja wywo³ywana, gdy Box o coœ uderzy
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Te funkcje bêdziemy wywo³ywaæ z Animacji (przez postaæ)
	void EnableCollision();
	void DisableCollision();

	// Lista aktorów, których ju¿ trafiliœmy podczas jednego zamachu (¿eby nie zadawaæ obra¿eñ 100 razy na sekundê)
	TArray<AActor*> IgnoreActors;
	
};
