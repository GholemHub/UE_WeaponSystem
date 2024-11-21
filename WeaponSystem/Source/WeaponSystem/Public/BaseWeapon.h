// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"


#include "BaseWeapon.generated.h"



UCLASS()
class WEAPONSYSTEM_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABaseWeapon();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

public:	
	virtual void StopFire();
	virtual void StartFire();
	//virtual void OnStopFire();
	//virtual void OnStartFire();
	virtual void MakeDamage(const FHitResult& HitResult);

private:
	

};
