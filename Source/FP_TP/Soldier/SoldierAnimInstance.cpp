#include "SoldierAnimInstance.h"
#include "../Soldier/Soldier.h"
#include "../Weapons/BaseWeaponInterface.h"
#include "GameFramework/CharacterMovementComponent.h"

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
        WeaponSway(TryPawn);
    }
}

FRotator USoldierAnimInstance::GetLookRotation(ASoldier* soldier) {
    const FTransform pawnTransform = soldier->GetActorTransform();
    const FRotator pawnControlRotation = soldier->GetControlRotation();
    const FRotator inverseTransform = InverseTransformRotation(pawnTransform, pawnControlRotation);
    const FRotator makeRotator = FRotator(0.0f, FMath::ClampAngle(inverseTransform.Yaw, -70.0f, 70.0f), FMath::ClampAngle((inverseTransform.Pitch * -1.0f), -70.0f, 70.0f));
    SoldierHeadRotation = FMath::RInterpTo(SoldierHeadRotation, makeRotator, GetWorld()->GetDeltaSeconds(), 9.0f);
    return SoldierHeadRotation;
}

FRotator USoldierAnimInstance::InverseTransformRotation(const FTransform& Transform, FRotator Rotation) {
    return Transform.InverseTransformRotation(Rotation.Quaternion()).Rotator();
}

void USoldierAnimInstance::WeaponSway(ASoldier* soldier){
    const float MouseX = FMath::GetMappedRangeValueClamped(FVector2D(-1, 1), FVector2D(-15, 15), soldier->GetMouseX());
    const float MouseY = FMath::GetMappedRangeValueClamped(FVector2D(-1, 1), FVector2D(-15, 15), soldier->GetMouseY());
    const float MoveSide = FMath::GetMappedRangeValueClamped(FVector2D(-1, 1), FVector2D(-15, 15), soldier->GetMoveSide());

    const float MouseXInterp = FMath::FInterpTo(RightHandRotator.Yaw, MouseX, GetWorld()->GetDeltaSeconds(), 1.5);
    const float MouseYInterp = FMath::FInterpTo(RightHandRotator.Pitch, MouseY, GetWorld()->GetDeltaSeconds(), 1.5);
    const float MoveSideInterp = FMath::FInterpTo(RightHandRotator.Roll, MoveSide, GetWorld()->GetDeltaSeconds(), 1.5);
    RightHandRotator = FRotator(MoveSideInterp, MouseXInterp, MouseYInterp);

    if (soldier->GetCurrentFPRightHandWeapon())
        LeftHandSocketTransform = soldier->GetCurrentFPRightHandWeapon()->GetWeaponLHandSocketTransform();
}
