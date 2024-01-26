#include "SoldierAnimInstance.h"
#include "../Soldier/Soldier.h"
#include "../Weapons/BaseWeaponInterface.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#define printf(color,format,...) GEngine->AddOnScreenDebugMessage(-1, 3, color, FString::Printf(TEXT(format), ##__VA_ARGS__));

void USoldierAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (ASoldier* TryPawn = Cast<ASoldier>(this->TryGetPawnOwner())) {
        soldierSpeed = TryPawn->GetVelocity().Size();
        soldierIsAir = TryPawn->GetMovementComponent()->IsFalling();
        soldierDirection = CalculateDirection(TryPawn->GetVelocity(), TryPawn->GetActorRotation());
        GetLookRotation(TryPawn);
        const FRotator deltaRotator = TryPawn->GetBaseAimRotation() - TryPawn->GetActorRotation();
        soldierPitch = deltaRotator.Pitch;
        soldierAimDownSight = TryPawn->GetAimDownSightState();
        soldierReload = TryPawn->GetReloadState();
        soldierWeaponCustomize = TryPawn->GetWeaponCustomizeState();
        soldierSprint = TryPawn->GetSprintState();
        soldierIsSwitchSecondWeapon = TryPawn->GetSwitchWeaponState();
        soldierWeaponClipDistanceLast = TryPawn->GetCurrentWeaponClipDistance();
        soldierWeaponClipDistanceCurrent = FMath::FInterpTo(soldierWeaponClipDistanceLast, soldierWeaponClipDistanceCurrent, GetWorld()->GetDeltaSeconds(), 30);
        WeaponSway(TryPawn);
        SoldierLean(TryPawn);
    }
}

FRotator USoldierAnimInstance::GetLookRotation(ASoldier* soldier) {
    const FTransform pawnTransform = soldier->GetActorTransform();
    const FRotator pawnControlRotation = soldier->GetControlRotation();
    const FRotator inverseTransform = InverseTransformRotation(pawnTransform, pawnControlRotation);
    const FRotator makeRotator = FRotator(0.0f, FMath::ClampAngle(inverseTransform.Yaw, -70.0f, 70.0f), FMath::ClampAngle((inverseTransform.Pitch * -1.0f), -70.0f, 70.0f));
    soldierHeadRotation = FMath::RInterpTo(soldierHeadRotation, makeRotator, GetWorld()->GetDeltaSeconds(), 9.0f);
    return soldierHeadRotation;
}

FRotator USoldierAnimInstance::InverseTransformRotation(const FTransform& Transform, FRotator Rotation) {
    return Transform.InverseTransformRotation(Rotation.Quaternion()).Rotator();
}

void USoldierAnimInstance::WeaponSway(ASoldier* soldier){
    const float MouseX = FMath::GetMappedRangeValueClamped(FVector2D(-1, 1), FVector2D(-15, 15), soldier->GetMouseX());
    const float MouseY = FMath::GetMappedRangeValueClamped(FVector2D(-1, 1), FVector2D(-15, 15), soldier->GetMouseY());

    const float MouseXInterp = FMath::FInterpTo(RightHandRotator.Yaw, MouseX, GetWorld()->GetDeltaSeconds(), 3);
    const float MouseYInterp = FMath::FInterpTo(RightHandRotator.Pitch, MouseY, GetWorld()->GetDeltaSeconds(), 3);
    RightHandRotator = FRotator(MouseYInterp, MouseXInterp, MouseYInterp);

    if (soldier->GetCurrentFPRightHandWeapon()) {
        leftFPHandSocketTransform = soldier->GetCurrentFPRightHandWeapon()->GetWeaponMesh()->GetSocketTransform(FName("FPLeftHandSocket"));
        leftTPHandSocketTransform = soldier->GetTPGunMesh()->GetSocketTransform(FName("TPLeftHandSocket"));
    }
}

void USoldierAnimInstance::SoldierLean(ASoldier* soldier){
    if (soldier->GetLeanLeftState()) {
        soldierLeanLast = -1.f;
    } else if(soldier->GetLeanRightState()){
        soldierLeanLast = 1.f;
    } else {
        soldierLeanLast = 0.f;
    }
    const float LeanInterp = FMath::FInterpTo(soldierLeanCurrent, soldierLeanLast, GetWorld()->GetDeltaSeconds(), 10);
    soldierLeanCurrent = LeanInterp;
    soldierLeanRotation.Pitch = soldierLeanCurrent * 20.f;
    const FRotator soldierCameraRotation = soldier->GetCameraComponent()->GetComponentRotation();
    soldier->GetCameraComponent()->SetWorldRotation(FRotator(soldierCameraRotation.Pitch, soldierCameraRotation.Yaw, soldierLeanRotation.Pitch));
}
