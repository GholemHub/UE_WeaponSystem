// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystemComponent.h"

#include "BaseWeapon.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h" 
#include "TimerManager.h"


// Sets default values for this component's properties
UWeaponSystemComponent::UWeaponSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UWeaponSystemComponent::StartFire()
{
	UE_LOG(LogTemp, Warning, TEXT("FIREStart:%i"), IsFire);
	if (!IsFire) {
		IsFire = true;
		if (!CurrentWeapon) return;
		//CurrentWeapon->StartFire();
		GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, CurrentWeapon, &ABaseWeapon::StartFire, CurrentWeapon->GetFireRate(), true);
		
	}
}

void UWeaponSystemComponent::StopFire()
{
	UE_LOG(LogTemp, Warning, TEXT("FIREStop:%i"), IsFire);
	if (IsFire) {
		IsFire = false;
		if (!CurrentWeapon) return;
		//CurrentWeapon->OnStopFire();
		GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
	}

	/*if (!CurrentWeapon) return;
	CurrentWeapon->StopFire();*/
}
void UWeaponSystemComponent::EquipNewWeapon()
{
	if(!GetWorld()) return;
	StopFire();
	if (WeaponIndex == 0) {
		
		WeaponIndex = 1;
		UE_LOG(LogTemp, Warning, TEXT("WeaponIndex:%i"), WeaponIndex);
		
		WeaponClass = WeaponClasses[WeaponIndex];
		CurrentWeapon = WeaponClass->GetDefaultObject<ABaseWeapon>();
		
		SpawnWeapon();
	}
	else {
		if (!WeaponClass) return;
		UE_LOG(LogTemp, Warning, TEXT("END PLAY"));
		//auto w = WeaponClass->GetDefaultObject<ABaseWeapon>();
		CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurrentWeapon->Destroy();
		WeaponClass = nullptr;

		WeaponIndex = 0;
		UE_LOG(LogTemp, Warning, TEXT("WeaponIndex:%i"), WeaponIndex);
		
		WeaponClass = WeaponClasses[WeaponIndex];
		CurrentWeapon = WeaponClass->GetDefaultObject<ABaseWeapon>();

		SpawnWeapon();
	}
	
}


// Called when the game starts
void UWeaponSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapon();
	
}

void UWeaponSystemComponent::EndPlay(const EEndPlayReason::Type EEndPlayReason)
{
	

	Super::EndPlay(EEndPlayReason);
}



void UWeaponSystemComponent::SpawnWeapon()
{

	CurrentWeapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);

	if (!GetWorld()) return;
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;
	
	
	if (!CurrentWeapon) return;

	// Find the camera component
	UCameraComponent* CameraComponent = Character->FindComponentByClass<UCameraComponent>();
	if (CameraComponent)
	{
		// Get all attached components
		TArray<USceneComponent*> AttachedComponents;
		CameraComponent->GetChildrenComponents(true, AttachedComponents);

		// Look for the Skeletal Mesh Component among the children
		for (USceneComponent* Component : AttachedComponents)
		{
			USkeletalMeshComponent* SkeletalMeshComp = Cast<USkeletalMeshComponent>(Component); // Renamed variable
			if (SkeletalMeshComp)
			{
				FAttachmentTransformRules AttachmentsRules(EAttachmentRule::SnapToTarget, false);
				CurrentWeapon->AttachToComponent(SkeletalMeshComp, AttachmentsRules, WeaponAttachPointName);
			}
		}
	}
}

// Called every frame
void UWeaponSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

