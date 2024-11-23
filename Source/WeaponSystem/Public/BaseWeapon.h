// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "IWeapon.h"

#include "BaseWeapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	READY       UMETA(DisplayName = "Idle"),
	FIRING      UMETA(DisplayName = "Firing"),
	RELOADING   UMETA(DisplayName = "Reloading"),
	OUTOFAMMO   UMETA(DisplayName = "Out of Ammo")
};


UCLASS()
class WEAPONSYSTEM_API ABaseWeapon : public AActor, public IIWeapon
{
	GENERATED_BODY()
	
public:	
	
	ABaseWeapon();

protected:
	
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float FireRate = 0.2f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMMO")
	int Ammo = 100 ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMMO")
	int ShopSize = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMMO")
	float SpeedOfReloading = 1.0f;

public:	
	virtual void StopFire();
	virtual void StartFire();
	/// Inteface
	
	virtual void Reload() override;
	virtual void GetAmmo() override;

	virtual void SetAmmo(int Ammo)override;
	virtual int GetAmmo() const override;

	virtual int GetShopSize() const override;
	virtual void SetShopSize(int ShopSize) override;

	virtual float GetSpeedOfReloading() const override;
	virtual void SetSpeedOfReloading(float Speed) override;

	/// </Inteface>
	virtual void MakeDamage(const FHitResult& HitResult);
	inline float GetFireRate() {return FireRate;}


private:
	void CountAmmo(int CurrentAmmo);
	FTimerHandle FireTimerHandle;
	void ChangeWeaponStateTo(EWeaponState State);

	EWeaponState CurrentWeaponState = EWeaponState::READY;
};
