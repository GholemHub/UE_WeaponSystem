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
	TSubclassOf<ABaseWeapon> WeaponClass;
public:	
	// Sets default values for this component's properties
	UWeaponSystemComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = Weapon)
	FName WeaponAttachPointName = "weapon_rSocket";

	UPROPERTY()
	ABaseWeapon* CurrentWeapon = nullptr;

	void SpawnWeapon();
	
public:	
	void StartFire();
	void StopFire();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

private:
	bool IsFire = false;

	
	FTimerHandle FireTimerHandle;
	float FireRate = 0.2f;
	
		
};
