// Copyright 2022 Mateusz Michalak. All rights reserved.


#include "Gameplay/PongCamera.h"

// Sets default values
APongCamera::APongCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APongCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APongCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

