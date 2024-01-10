#include "Magazine_AR4.h"

#define printf(color,format,...) GEngine->AddOnScreenDebugMessage(-1, 3, color, FString::Printf(TEXT(format), ##__VA_ARGS__));

AMagazine_AR4::AMagazine_AR4(){
	PrimaryActorTick.bCanEverTick = false;
	magazineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("magazineAR4"));
	magazineMesh->SetupAttachment(GetRootComponent());

	FCollisionResponseContainer CollisionResponseContainer;
	CollisionResponseContainer.SetResponse(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	CollisionResponseContainer.SetResponse(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	CollisionResponseContainer.SetResponse(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	CollisionResponseContainer.SetResponse(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	CollisionResponseContainer.SetResponse(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	CollisionResponseContainer.SetResponse(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
	CollisionResponseContainer.SetResponse(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Ignore);
	CollisionResponseContainer.SetResponse(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Block);

	magazineMesh->SetCollisionResponseToChannels(CollisionResponseContainer);
}

void AMagazine_AR4::SetMagazineMesh(EWeaponMagazineType magazineType){
	switch (magazineType){
		case EWeaponMagazineType::EMPTY:{
			magazineMesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Weapons/Meshes/AR4/SM_AR4_Mag_Empty")));
			break;
		}
		case EWeaponMagazineType::FULL: {
			magazineMesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Weapons/Meshes/AR4/SM_AR4_Mag")));
			break;
		}
		default:
			break;
	}
}

//void AMagazine_AR4::BeginPlay(){
//	Super::BeginPlay();
//}

//UClass* AMagazine_AR4::GetMagazineClass(){
//	return this->StaticClass();
//}