// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "PistolWeapon.generated.h"

/**
 * 
 */
UCLASS()
class WEAPONSYSTEM_API APistolWeapon : public ABaseWeapon
{
	GENERATED_BODY()
	APistolWeapon();

public:
	void StopFire() override;
	void StartFire() override;

	void MakeDamage(const FHitResult& HitResult) override;
	
};
