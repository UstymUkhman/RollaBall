// Fill out your copyright notice in the Description page of Project Settings.


#include "RollaBallPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ARollaBallPlayer::ARollaBallPlayer()
{
 	// Set this pawn to call Tick() every frame.
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create Components:
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	// Set the Root Component to be our Mesh:
	RootComponent = Mesh;

	// Attach the SpringArm to the Mesh,
	// Spring will follow the Mesh transform:
	SpringArm->SetupAttachment(Mesh);

	// Attach the Camera to the SpringArm,
	// Camera will follow the SpringArm transform:
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ARollaBallPlayer::BeginPlay()
{
	Super::BeginPlay();	
}

void ARollaBallPlayer::MoveForward(float Value)
{
}

void ARollaBallPlayer::MoveRight(float Value)
{
}

void ARollaBallPlayer::Jump()
{
}

// Called to bind functionality to input
void ARollaBallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
