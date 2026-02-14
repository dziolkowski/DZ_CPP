// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "DZ_CPPCharacter.h"

void AWeapon::PickUp(ADZ_CPPCharacter* Character)
{
	if (Character)
	{
		// Wywolujemy funkcje Equip na postaci
		Character->Equip(this);
	}
}

