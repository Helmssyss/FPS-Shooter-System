#include "Soldier.h"
#include "../FP_TPGameModeBase.h"
#include "../Weapons/BaseWeaponInterface.h"
#include "../Bullets/BaseBulletInterface.h"
#include "../Widgets/SoldierInterfaceWidget.h"

#include "Camera/CameraComponent.h"
#include "Camera/CameraShakeBase.h"

#include "Animation/AnimBlueprint.h"
#include "Components/SkeletalMeshComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "UObject/ConstructorHelpers.h"

#include "Kismet/GameplayStatics.h"

#include "DrawDebugHelpers.h"

#define printf(color,format,...) GEngine->AddOnScreenDebugMessage(-1, 3, color, FString::Printf(TEXT(format), ##__VA_ARGS__));

ASoldier::ASoldier(){
	PrimaryActorTick.bCanEverTick = true;
	const static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMesh(TEXT("/Game/Character/ThirdPerson/Mesh/TP_BodyMesh"));
	const static ConstructorHelpers::FObjectFinder<USkeletalMesh> FP_ArmsMesh(TEXT("/Game/Character/FirstPerson/Mesh/FP_SK_ArmMesh"));
	const static ConstructorHelpers::FObjectFinder<USkeletalMesh> FP_FootsMesh(TEXT("/Game/Character/FirstPerson/Mesh/SK_Man_Shoes"));
	const static ConstructorHelpers::FObjectFinder<USkeletalMesh> FP_LegsMesh(TEXT("/Game/Character/FirstPerson/Mesh/SK_Man_Pants"));
	const static ConstructorHelpers::FObjectFinder<UAnimBlueprint> FP_RifleAnimClass(TEXT("/Game/Character/FirstPerson/Animation/FP_AnimBP"));
	const static ConstructorHelpers::FObjectFinder<UAnimBlueprint> TP_BodyAnimClass(TEXT("/Game/Character/ThirdPerson/Animation/TP_AnimWtihWeaponBP"));
	const static ConstructorHelpers::FObjectFinder<UCurveFloat> GetADS_Curve(TEXT("/Game/Blueprint/ADS_Curve"));
	const static ConstructorHelpers::FObjectFinder<UCurveFloat> GetRECOIL_PITCH_Curve(TEXT("/Game/Blueprint/RECOIL_PITCH_Curve"));
	const static ConstructorHelpers::FObjectFinder<UCurveFloat> GetRECOIL_YAW_Curve(TEXT("/Game/Blueprint/RECOIL_YAW_Curve"));
	const static ConstructorHelpers::FClassFinder<UCameraShakeBase> FireCameraShake(TEXT("/Game/Blueprint/FireCameraShake"));
	const static ConstructorHelpers::FClassFinder<UUserWidget> GetSoldierInterfaceWidget(TEXT("/Game/Widgets/BP_SoldierInterfaceWidget"));

	GetMesh()->SetAnimClass(TP_BodyAnimClass.Object->GeneratedClass);
	GetMesh()->SetSkeletalMesh(BodyMesh.Object);
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.f, 0.0f));
	GetMesh()->SetRelativeLocation(FVector(-0.000145, 0.0f, -85.010056));
	GetCharacterMovement()->JumpZVelocity = 275.5f;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	FP_CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("FP_CameraBoom"));
	FP_CameraBoom->SetupAttachment(GetMesh(), FName("head"));
	FP_CameraBoom->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	FP_CameraBoom->SetRelativeLocation(FVector(0.000053, 7.872850, -0.000353));
	FP_CameraBoom->TargetArmLength = 0.0f;
	FP_CameraBoom->bUsePawnControlRotation = true;
	
	FP_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FP_Camera"));
	FP_Camera->SetupAttachment(FP_CameraBoom);
	FP_Camera->SetFieldOfView(FOV_Start);

	FP_Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Arms"));
	FP_Arms->SetupAttachment(FP_Camera);
	FP_Arms->SetSkeletalMesh(FP_ArmsMesh.Object);
	FP_Arms->SetRelativeRotation(FP_ArmRotStart);
	FP_Arms->SetRelativeLocation(FP_ArmVecStart);
	FP_Arms->SetAnimClass(FP_RifleAnimClass.Object->GeneratedClass);

	FP_Legs = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_LegsMesh"));
	FP_Legs->SetupAttachment(GetMesh());
	FP_Legs->SetSkeletalMesh(FP_LegsMesh.Object);
	FP_Legs->SetAnimationMode(EAnimationMode::AnimationCustomMode);
	FP_Legs->SetMasterPoseComponent(GetMesh());

	FP_Foots = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_FootsMesh"));
	FP_Foots->SetupAttachment(FP_Legs);
	FP_Foots->SetSkeletalMesh(FP_FootsMesh.Object);
	FP_Foots->SetAnimationMode(EAnimationMode::AnimationCustomMode);
	FP_Foots->SetMasterPoseComponent(GetMesh());

	TP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TP_GunMesh"));
	TP_Gun->SetupAttachment(GetMesh(), FName("TP_rightHand"));
	TP_Gun->SetCastHiddenShadow(true);
	TP_Gun->bOwnerNoSee = true;

	GetMesh()->CastShadow = true;
	GetMesh()->bOwnerNoSee = true;
	GetMesh()->SetCastHiddenShadow(true);
	FP_Arms->bOnlyOwnerSee = true;
	FP_Arms->CastShadow = false;
	FP_Foots->bOnlyOwnerSee = true;
	FP_Foots->CastShadow = false;
	FP_Legs->bOnlyOwnerSee = true;
	FP_Legs->CastShadow = false;

	ADS_Curve = GetADS_Curve.Object;
	PitchCurve = GetRECOIL_PITCH_Curve.Object;
	YawCurve = GetRECOIL_YAW_Curve.Object;

	TCameraShake = FireCameraShake.Class;
	TSoldierInterfaceWidget = GetSoldierInterfaceWidget.Class;
}

void ASoldier::BeginPlay(){
	Super::BeginPlay();

	if (ADS_Curve) {
		FOnTimelineFloat ADS_ProgressUpdate;
		FOnTimelineEvent ADS_FinishEvent;

		ADS_ProgressUpdate.BindUFunction(this, FName("AimDownSightUpdate"));
		ADS_FinishEvent.BindUFunction(this, FName("OnAimDownSightFinished"));

		ADS_Timeline.AddInterpFloat(ADS_Curve, ADS_ProgressUpdate);
		ADS_Timeline.SetTimelineFinishedFunc(ADS_FinishEvent);
		ADS_Timeline.SetLooping(false);
		ADS_Timeline.SetPlayRate(8.0f);
	}
	if (PitchCurve && YawCurve) {
		FOnTimelineFloat PitchCurveFloat;
		FOnTimelineFloat YawCurveFloat;

		PitchCurveFloat.BindUFunction(this, FName("RecoilStartPitch"));
		YawCurveFloat.BindUFunction(this, FName("RecoilStartYaw"));

		RecoilTimeline.AddInterpFloat(PitchCurve, PitchCurveFloat);
		RecoilTimeline.AddInterpFloat(YawCurve, YawCurveFloat);
	}

	SoldierInterfaceWidget = CreateWidget<USoldierInterfaceWidget>(GetWorld()->GetFirstPlayerController(), TSoldierInterfaceWidget);
	SoldierInterfaceWidget->AddToViewport();
}

void ASoldier::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (currentRightHandWeapon) {
		ADS_Timeline.TickTimeline(DeltaTime);
		if (currentRightHandWeapon->GetCurrentAmmo() != 0) {
			RecoilInterpolate(DeltaTime);
		}
	}
}

void ASoldier::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (PlayerInputComponent) {
		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
		PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
		PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASoldier::Sprint);
		PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASoldier::SprintStop);
		PlayerInputComponent->BindAction("AimDownSight", IE_Pressed, this, &ASoldier::AimDownSightStart);
		PlayerInputComponent->BindAction("AimDownSight", IE_Released, this, &ASoldier::AimDownSightReverse);
		PlayerInputComponent->BindAction("OnFire", IE_Pressed, this, &ASoldier::OnFire);
		PlayerInputComponent->BindAction("OnFire", IE_Released, this, &ASoldier::OnFireReleased);
		PlayerInputComponent->BindAction("FireMode", IE_Pressed, this, &ASoldier::FireMode);
		PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ASoldier::Reload);

		PlayerInputComponent->BindAxis("MoveFB", this, &ASoldier::MoveFB);
		PlayerInputComponent->BindAxis("MoveRL", this, &ASoldier::MoveRL);
		PlayerInputComponent->BindAxis("TurnRL", this, &ASoldier::TurnRL);
		PlayerInputComponent->BindAxis("LookUp", this, &ASoldier::LookUp);
	}
}

void ASoldier::MoveFB(float Value){
	if (Controller != nullptr) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ASoldier::MoveRL(float Value){
	if (Controller != nullptr) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ASoldier::TurnRL(float Rate){
	yawInput = Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASoldier::LookUp(float Rate){
	pitchInput = Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds();
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASoldier::Sprint(){
	if (!bAimDownSight) {
		GetCharacterMovement()->MaxWalkSpeed = 600;
		bSprint = true;
	}
}

void ASoldier::SprintStop(){
	if (!bAimDownSight) {
		GetCharacterMovement()->MaxWalkSpeed = 300;
		bSprint = false;
	}
}

void ASoldier::AimDownSightStart() {
	GLog->Log("PLAY");
	ADS_Timeline.Play();
	bAimDownSight = true;
}

void ASoldier::AimDownSightReverse() {
	ADS_Timeline.Reverse();
	bAimDownSight = false;
}

void ASoldier::RecoilStart(){
	RecoilTimeline.PlayFromStart();
}

void ASoldier::RecoilReverse(){
	RecoilTimeline.ReverseFromEnd();
}

void ASoldier::RecoilInterpolate(float DeltaTime){
	if (RecoilTimeline.IsPlaying()) {
		RecoilTimeline.TickTimeline(DeltaTime);
		if (FMath::Abs(yawInput) > 0 || FMath::Abs(pitchInput) > 0)
			RecoilStartRotation = FP_Camera->GetComponentRotation();
	}
	if (RecoilTimeline.IsReversing()) {
		if (GetCharacterMovement()->Velocity != FVector::ZeroVector) {
			RecoilTimeline.Stop();
			return;
		}
		if (FMath::Abs(yawInput) > 0 || FMath::Abs(pitchInput) > 0) {
			RecoilTimeline.Stop();
			return;
		}
		RecoilTimeline.TickTimeline(DeltaTime);
		RecoilEndRotation = FP_Camera->GetComponentRotation();
		const float InterpolatePitch = FMath::FInterpTo(RecoilStartRotation.Pitch, RecoilEndRotation.Pitch, DeltaTime, 35);
		GetController()->SetControlRotation(FRotator(InterpolatePitch, RecoilEndRotation.Yaw, RecoilEndRotation.Roll));
	}
}

void ASoldier::OnAimDownSightFinished() {
	const float CurrentPosition = ADS_Timeline.GetPlaybackPosition();
	if (ADS_Timeline.IsPlaying()) {
		if (CurrentPosition == ADS_Timeline.GetTimelineLength()) {
			ADS_Timeline.Stop();
		}
	}
	else {
		if (CurrentPosition == ADS_Timeline.GetTimelineLength()) {
			ADS_Timeline.Stop();
		}
	}
}

void ASoldier::AimDownSightUpdate(float Alpha) {
	FP_Camera->SetFieldOfView(FMath::Lerp(FOV_Start, FOV_End, Alpha));
	FP_Arms->SetRelativeLocation(FMath::Lerp<FVector>(FP_ArmVecStart, currentRightHandWeapon->GetWeaponInFPLocation(), Alpha));
	FP_Arms->SetRelativeRotation(FMath::Lerp<FRotator>(FP_ArmRotStart, currentRightHandWeapon->GetWeaponInFPRotation(), Alpha));
}

void ASoldier::RecoilStartPitch(float Alpha) {
	if (RecoilTimeline.IsReversing()) { return; }
	AddControllerPitchInput(Alpha);
}

void ASoldier::RecoilStartYaw(float Alpha) {
	if (RecoilTimeline.IsReversing()) { return; }
	AddControllerYawInput(Alpha);
}

void ASoldier::FireMode() {
	currentWeaponFireMode++;
	if (currentWeaponFireMode > 2) currentWeaponFireMode = 0;
	if (currentRightHandWeapon) {
		switch (currentWeaponFireMode){
			case 0:
				currentRightHandWeapon->SetCurrentWeaponFireMode(EWeaponFireModes::AUTO_MODE);
				printf(FColor::Red, "AUTO_MODE");
				break;

			case 1:
				currentRightHandWeapon->SetCurrentWeaponFireMode(EWeaponFireModes::SEMI_AUTO_MODE);
				printf(FColor::Red, "SEMI_AUTO_MODE");
				break;

			case 2:
				currentRightHandWeapon->SetCurrentWeaponFireMode(EWeaponFireModes::SINGLE_MODE);
				printf(FColor::Red, "SINGLE_MODE");
				break;
		}
		SoldierInterfaceWidget->RemoveFromParent();
		SoldierInterfaceWidget->AddToViewport();
	}
}

void ASoldier::OnFire(){
	if (currentRightHandWeapon) {
		if (currentRightHandWeapon->GetCurrentAmmo() != 0) {
			RecoilStartRotation = FP_Camera->GetComponentRotation();
				switch (currentRightHandWeapon->GetCurrentWeaponFireMode()) {
					case EWeaponFireModes::AUTO_MODE: {
						RecoilStart();
						GetWorldTimerManager().SetTimer(T_FireModeHandle, this, &ASoldier::ShootFire, 0.127f, true);
						break;
					}
					case EWeaponFireModes::SEMI_AUTO_MODE: {
						RecoilStart();
						GetWorldTimerManager().SetTimer(T_FireModeHandle, this, &ASoldier::SetSemiAutoFire, 0.127f, true);
						break;
					}
					case EWeaponFireModes::SINGLE_MODE: {
						RecoilStart();
						GetWorldTimerManager().SetTimer(T_FireModeHandle, this, &ASoldier::ShootFire, 0.127f, false);
						break;
					}
			}
		}else {
			// Tetik sesi
		}
	}
}

void ASoldier::SetSemiAutoFire() {
	if (SemiAutoFireCount < 2) {
		ShootFire();
		SemiAutoFireCount++;
	}else {
		SemiAutoFireCount = 0;
		GetWorldTimerManager().ClearTimer(T_FireModeHandle);
	}
}

void ASoldier::ShootFire() {
	if (currentRightHandWeapon) {
		if (currentRightHandWeapon->GetCurrentAmmo() != 0) {
			FHitResult ResultHit;
			const short length = 32700;
			const FVector Start = FP_Camera->GetComponentLocation();
			const FVector distance = FP_Camera->GetForwardVector() * length;
			FVector End = Start + distance;
			currentRightHandWeapon->WeaponSpreadSize(End, bAimDownSight);
			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(this);
			bool trace = this->GetWorld()->LineTraceSingleByChannel(ResultHit, Start, End, ECollisionChannel::ECC_PhysicsBody, QueryParams);
			const FVector selectVector = SelectVector(ResultHit.ImpactPoint, ResultHit.TraceEnd, trace);
			const FRotator lookAtRot = FindLookAtRotation(currentRightHandWeapon->GetWeaponMesh()->GetSocketLocation(FName("Muzzle")), selectVector);
			const FRotator makeRotator = FRotator(lookAtRot.Pitch + 0.3, lookAtRot.Yaw, lookAtRot.Roll);
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 4);
			const FTransform makeTransform = FTransform(makeRotator, currentRightHandWeapon->GetWeaponMesh()->GetSocketLocation(FName("Muzzle")), FVector(1.7, 1.7, 1.7));
			FActorSpawnParameters params;
			params.Instigator = this;
			params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			IBaseBulletInterface* spwnBullet = GetWorld()->SpawnActor<IBaseBulletInterface>(currentRightHandWeapon->GetWeaponBulletClass(), makeTransform, params);
			if (spwnBullet) {
				short bullet = currentRightHandWeapon->GetCurrentAmmo();
				bullet--;
				currentRightHandWeapon->SetCurrentAmmo(bullet);
				const FTransform muzzleSocketTransform(currentRightHandWeapon->GetWeaponMesh()->GetSocketTransform(FName("Muzzle")));
				FP_Arms->GetAnimInstance()->Montage_Play(currentRightHandWeapon->GetWeaponInFPFireAnimation());
				GetMesh()->GetAnimInstance()->Montage_Play(currentRightHandWeapon->GetWeaponInTPFireAnimation());

				UGameplayStatics::PlayWorldCameraShake(GetWorld(), TCameraShake, GetActorLocation(), 80, 0);

				UGameplayStatics::SpawnEmitterAttached(currentRightHandWeapon->GetWeaponMuzzleParticle(), currentRightHandWeapon->GetWeaponMesh(), "Muzzle",
					muzzleSocketTransform.GetLocation(), FP_Camera->GetComponentRotation(), FVector(1, 1, 1), EAttachLocation::Type::KeepWorldPosition);
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), currentRightHandWeapon->GetWeaponFireSound(), GetActorLocation(), 1, 1, 0, currentRightHandWeapon->GetWeaponFireSoundAttenuation());
				currentRightHandWeapon->PlayWeaponFireAnimation();
			}
			DrawDebugBox(GetWorld(), ResultHit.ImpactPoint, FVector(3, 3, 3), FColor::Red, false, 3.f);
		}
		else {
			OnFireReleased();
		}
	}
}

void ASoldier::OnFireReleased(){
	if (currentRightHandWeapon)
		if (currentRightHandWeapon->GetTotalAmmo() != 0) {
			RecoilReverse();
			GetWorldTimerManager().ClearTimer(T_FireModeHandle);
		}
}

void ASoldier::Reload() {
	if (currentRightHandWeapon) {
		//bReloading = true;
		FP_Arms->GetAnimInstance()->Montage_Play(currentRightHandWeapon->GetWeaponInFPReloadAnimation());
		GetMesh()->GetAnimInstance()->Montage_Play(currentRightHandWeapon->GetWeaponInTPReloadAnimation());
	}
}