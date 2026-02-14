// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DZ_CPP_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

	// Funkcja wywolywana, gdy gracz wcisnie przycisk interakcji
	void AttemptInteract();

protected:
	// Zasieg interakcji
	UPROPERTY(EditAnywhere, Category = "Interaction")
	float InteractionRange = 200.0f;

		
};
