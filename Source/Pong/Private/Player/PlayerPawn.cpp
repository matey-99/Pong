// Copyright 2022 Mateusz Michalak. All rights reserved.

#include "Player/PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	auto PC = Cast<APlayerController>(GetController());

	FString Message = "Possessed by: ";
	Message.Append(FString::FromInt(UGameplayStatics::GetPlayerControllerID(PC)));

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Red, Message);
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (StaticMeshComponent->GetLocation)

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerPawn::Move(float Value)
{
	if (Value != 0.0f)
		AddMovementInput(-GetActorRightVector(), Value);
}

