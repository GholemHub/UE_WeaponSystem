// Fill out your copyright notice in the Description page of Project Settings.


#include "PistolWeapon.h"
#include "Target.h"

APistolWeapon::APistolWeapon()
{
	//Super::ABaseWeapon();

}

void APistolWeapon::StopFire()
{

}

void APistolWeapon::StartFire()
{
	Super::StartFire();
}

void APistolWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();

	auto MyActor = Cast<ATarget>(DamagedActor);
	if (!MyActor) return;

	MyActor->Health += -Damage;
}
