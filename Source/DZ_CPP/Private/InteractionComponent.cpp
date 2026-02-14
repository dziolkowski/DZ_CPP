// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"
#include "DrawDebugHelpers.h"
#include "DZ_CPPCharacter.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UInteractionComponent::AttemptInteract()
{
	AActor* Owner = GetOwner();
	if (!Owner) return;

	FVector Start = Owner->GetActorLocation();
	FVector End = Start + (Owner->GetActorForwardVector() * InteractionRange);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);

	// Strzelamy promieniem przed siebie
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

	if (bHit && HitResult.GetActor())
	{
		// Sprawdzamy czy trafiony obiekt ma nasz interfejs
		if (HitResult.GetActor()->Implements<UInteractionInterface>())
		{
			// Rzutujemy na interfejs i wywolujemy Interact
			IInteractionInterface::Execute_Interact(HitResult.GetActor(), Cast<ADZ_CPPCharacter>(Owner));
		}
	}
}

