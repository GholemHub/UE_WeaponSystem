// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "BaseWeapon.h"


#include "WeaponSystemComponent.generated.h"
class WeaponClass;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WEAPONSYSTEM_API UWeaponSystemComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	TArray<TSubclassOf<ABaseWeapon>> WeaponClasses;
public:	
	// Sets default values for this component's properties
	UWeaponSystemComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type) override;
	UPROPERTY(EditAnywhere, Category = Weapon)
	FName WeaponAttachPointName = "weapon_rSocket";

	UPROPERTY()
	ABaseWeapon* CurrentWeapon = nullptr;
	UPROPERTY()
	TSubclassOf<ABaseWeapon> WeaponClass = nullptr;

	void SpawnWeapon();
	
public:	
	void StartFire();
	void StopFire();
	void EquipNewWeapon();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

private:
	bool IsFire = false;
	int WeaponIndex = 0;
	
	FTimerHandle FireTimerHandle;
	
};
