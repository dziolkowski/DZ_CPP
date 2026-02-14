// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "DZ_CPPCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h" 
#include "CombatInterface.h"
#include "Components/SceneComponent.h"

AWeapon::AWeapon()
{
	// Tworzymy Box Collision
	WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponBox"));
	WeaponBox->SetupAttachment(GetRootComponent());

	// Domyslnie wylaczamy kolizje 
	WeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	WeaponBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore); // ¯eby nie raniæ samego siebie

	// Tworzymy punkty do sledzenia (Start i Koniec ostrza)
	TraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("TraceStart"));
	TraceStart->SetupAttachment(GetRootComponent());

	TraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("TraceEnd"));
	TraceEnd->SetupAttachment(GetRootComponent());
}

void AWeapon::EnableCollision()
{
	if (WeaponBox)
	{
		WeaponBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		// Czyscimy liste trafionych wrogow przy nowym zamachu
		IgnoreActors.Empty();

		// Zawsze bindujemy funkcje
		WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxOverlap);
	}
}

void AWeapon::DisableCollision()
{
	if (WeaponBox)
	{
		WeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WeaponBox->OnComponentBeginOverlap.RemoveDynamic(this, &AWeapon::OnBoxOverlap);
	}
}

void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Sprawdzamy czy to nie my sami i czy juz tego wroga nie trafilismy
	if (OtherActor == GetOwner() || IgnoreActors.Contains(OtherActor)) return;

	// Dodajemy do ignorowanych, zeby uderzyc go tylko raz na zamach
	IgnoreActors.Add(OtherActor);

	FHitResult BoxHit;

	// Pobieramy pozycje naszych Scene Componentow
	const FVector Start = TraceStart->GetComponentLocation();
	const FVector End = TraceEnd->GetComponentLocation();

	// Wykonujemy Trace, zeby znalezc dokladny punkt uderzenia
	bool bSuccess = UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		FVector(5.f, 5.f, 5.f), // Wielkosc pudelka testowego
		TraceStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		TArray<AActor*>(), // Aktorzy do ignorowania 
		EDrawDebugTrace::ForDuration, // Rysuje debug 
		BoxHit,
		true
	);

	if (bSuccess && BoxHit.GetActor())
	{
		AActor* HitActor = BoxHit.GetActor();

		// Sprawdzamy, czy trafiony obiekt implementuje interfejs walki
		if (HitActor && HitActor->GetClass()->ImplementsInterface(UCombatInterface::StaticClass()))
		{
			// Wywolujemy funkcje z interfejsu
			ICombatInterface::Execute_GetHit(HitActor, BoxHit.ImpactPoint);

			// Dodajmy log dla pewnosci
			UE_LOG(LogTemp, Warning, TEXT("Wywolano GetHit na: %s"), *HitActor->GetName());
		}
	}
}

void AWeapon::PickUp(ADZ_CPPCharacter* TargetCharacter)
{
	if (TargetCharacter)
	{
		// Wylaczamy fizyke itemu, zeby nie wypadl z reki
		if (UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(GetRootComponent()))
		{
			RootComp->SetSimulatePhysics(false);
		}

		SetActorEnableCollision(false);

		// Przyczepiamy miecz do reki 
		FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
		AttachToComponent(TargetCharacter->GetMesh(), AttachRules, TEXT("WeaponSocket"));

		// 3Ustawiamy Wlasciciela 
		SetOwner(TargetCharacter);

		// Przekazujemy bron do postaci 
		TargetCharacter->SetWeapon(this);

		UE_LOG(LogTemp, Warning, TEXT("Podniesiono bron: %s"), *GetName());
	}
}
