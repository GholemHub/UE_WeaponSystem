// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


#include "WeaponSystemComponent.h"
#include "Target.h"


// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();	
}


void ABaseWeapon::StopFire()
{

}

void ABaseWeapon::StartFire()
{
    if (CurrentWeaponState != EWeaponState::READY) return;
    //GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, CurrentWeapon, &ABaseWeapon::StartFire, 0.2f, true);

    USkeletalMeshComponent* SkeletalMeshComp = WeaponMesh;

    if (SkeletalMeshComp)
    {
        
        // Specify the socket name
        FName SocketName = FName(TEXT("MuzzleFlash"));

        // Check if the socket exists
        if (SkeletalMeshComp->DoesSocketExist(SocketName))
        {
            // Get the socket's transform
            FTransform SocketTransform = SkeletalMeshComp->GetSocketTransform(SocketName, RTS_World);
            FVector SocketLocation = SocketTransform.GetLocation();
            FRotator SocketRotation = SocketTransform.GetRotation().Rotator();

            ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

            if (Character) {
               
                APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
                    if (!PlayerController)
                    {
                        UE_LOG(LogTemp, Warning, TEXT("PlayerController not found!"));
                        return;
                    }
                    FVector WorldLocation, WorldDirection;
                    int32 ViewportX, ViewportY;
                    PlayerController->GetViewportSize(ViewportX, ViewportY); // Get screen size
                    FVector2D ScreenCenter(ViewportX * 0.5f, ViewportY * 0.5f);
                    // Convert the screen center to a world direction
                    if (!PlayerController->DeprojectScreenPositionToWorld(ScreenCenter.X, ScreenCenter.Y, WorldLocation, WorldDirection))
                    {
                        UE_LOG(LogTemp, Warning, TEXT("Failed to deproject screen position to world."));
                        return;
                    }

                    FVector TraceStart = SocketLocation;
                    FVector TraceEnd = TraceStart + (WorldDirection * 10000.0f); // Extend the direction vector

                    // Line trace
                    FHitResult HitResult;
                    FCollisionQueryParams QueryParams;
                    QueryParams.AddIgnoredActor(Character); // Ignore the character itself in the trace

                    if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
                    {
                        //UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitResult.Actor->GetName());
                        UE_LOG(LogTemp, Error, TEXT("Fire"));
                        DrawDebugLine(GetWorld(), TraceStart, HitResult.Location, FColor::Red, false, 2.0f, 0, 1.0f);
                        DrawDebugSphere(GetWorld(), HitResult.Location, 15, 12, FColor::Red, false, 2.0f, 0, 1.0f);

                        MakeDamage(HitResult);
                        

                    }
                    else
                    {
                        // No hit
                        UE_LOG(LogTemp, Error, TEXT("Fire"));
                        DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Blue, false, 2.0f, 0, 1.0f);
                    }
                // Log socket transform
                
            }
            UE_LOG(LogTemp, Log, TEXT("Socket %s Transform: Location: %s, Rotation: %s"),
                *SocketName.ToString(),
                *SocketTransform.GetLocation().ToString(),
                *SocketTransform.GetRotation().Rotator().ToString());

            // Example: Attach an actor to the socket
            //FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
            //SomeActor->AttachToComponent(SkeletalMeshComp, AttachmentRules, SocketName);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Socket %s does not exist!"), *SocketName.ToString());
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("SkeletalMeshComponent not found!"));
    }
    CountAmmo(123);
}

void ABaseWeapon::Reload()
{
    UE_LOG(LogTemp, Error, TEXT("Reload"));
}

void ABaseWeapon::GetAmmo()
{
    UE_LOG(LogTemp, Error, TEXT("Interface3"));
}

void ABaseWeapon::MakeDamage(const FHitResult& HitResult)
{
    const auto DamagedActor = HitResult.GetActor();

    auto MyActor = Cast<ATarget>(DamagedActor);
    if (!MyActor) return;

    MyActor->Health += -20;

}

void ABaseWeapon::CountAmmo(int CurrentAmmo)
{
    Ammo -= 1;
    if (Ammo == 0) return;
    if (Ammo % ShopSize == 0) {
        if (!GetWorld()) return;
        CurrentWeaponState = EWeaponState::RELOADING;
        GetWorld()->GetTimerManager().SetTimer(
            FireTimerHandle,
            [this]() {
                ChangeWeaponStateTo(EWeaponState::RELOADING);
            },
            SpeedOfReloading,     // Timer interval (seconds)
            false     // Don't loop, since we only want to change the state once
        );
    }
}

void ABaseWeapon::ChangeWeaponStateTo(EWeaponState State)
{
    UE_LOG(LogTemp, Error, TEXT("STATE IS CHANGED"));
    CurrentWeaponState = EWeaponState::READY;
    if (!GetWorld()) return;
    GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

int ABaseWeapon::GetAmmo() const 
{
    return Ammo;
}

void ABaseWeapon::SetAmmo(int AmmoCount) 
{
    Ammo = AmmoCount;
}

int ABaseWeapon::GetShopSize() const 
{
    return ShopSize;
}

void ABaseWeapon::SetShopSize(int ShopSizeValue) 
{
    ShopSize = ShopSizeValue;
}

float ABaseWeapon::GetSpeedOfReloading() const 
{
    return SpeedOfReloading;
}

void ABaseWeapon::SetSpeedOfReloading(float Speed) 
{
    SpeedOfReloading = Speed;
}


