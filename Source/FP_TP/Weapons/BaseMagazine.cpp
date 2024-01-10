#include "BaseMagazine.h"

ABaseMagazine::ABaseMagazine(){
	PrimaryActorTick.bCanEverTick = false;
}

void ABaseMagazine::BeginPlay(){
	Super::BeginPlay();
	
}