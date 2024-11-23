// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IWeapon.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIWeapon : public UInterface
{
	GENERATED_BODY()

};

/**
 * 
 */
class WEAPONSYSTEM_API IIWeapon
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Reload() = 0;
	virtual void GetAmmo() = 0;

	virtual void SetAmmo(int Ammo) = 0;
	virtual int GetAmmo() const = 0;

	virtual int GetShopSize() const = 0;
	virtual void SetShopSize(int ShopSize) = 0;

	virtual float GetSpeedOfReloading() const = 0;
	virtual void SetSpeedOfReloading(float Speed) = 0;
};
