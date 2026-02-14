// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AItem.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class DZ_CPP_API AWeapon : public AAItem
{
	GENERATED_BODY()

public:
	// Nadpisywanie funkcji PickUp
	virtual void PickUp(class ADZ_CPPCharacter* Character) override;
	
};
