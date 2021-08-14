#include "RollaBallPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

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

	// Set physics simulation to true:
	Mesh->SetSimulatePhysics(true);

	// Add collision callback behavior:
	Mesh->OnComponentHit.AddDynamic(this, &ARollaBallPlayer::OnHit);
}

// Called when the game starts or when spawned
void ARollaBallPlayer::BeginPlay()
{
	Super::BeginPlay();

	// Account for mass in MoveForce:
	MoveForce *= Mesh->GetMass();

	// Account for mass in JumpImpulse:
	JumpImpulse *= Mesh->GetMass();
}

// Called to bind functionality to input
void ARollaBallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Input Axis Bindings:
	InputComponent->BindAxis("MoveForward", this, &ARollaBallPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARollaBallPlayer::MoveRight);

	// Input Actions Bindings:
	InputComponent->BindAction("Jump", IE_Pressed, this, &ARollaBallPlayer::Jump);
}

// Called when the player is moving along the Y axis:
void ARollaBallPlayer::MoveForward(float Value)
{
	// Get the forward vector of the camera and move the player
	// in this direction based on the input and MoveForce:
	const FVector Forward = Camera->GetForwardVector();
	Mesh->AddForce(Forward * MoveForce * Value);
}

// Called when the player is moving along the X axis:
void ARollaBallPlayer::MoveRight(float Value)
{
	// Get the right vector of the camera and move the player
	// in this direction based on the input and MoveForce:
	const FVector Right = Camera->GetRightVector();
	Mesh->AddForce(Right * MoveForce * Value);
}

// Called when the player is jumping:
void ARollaBallPlayer::Jump()
{
	// Cap the number of jumps we can make:
	if (JumpCount >= MaxJumpCount) return;

	// Apply an impulse to the Mesh in the Z axis:
	Mesh->AddImpulse(FVector(0.0, 0.0, JumpImpulse));

	// Track how many times we've jumped:
	JumpCount++;
}

void ARollaBallPlayer::OnHit
(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit
)
{
	// Get hit direction on the Z axis:
	//		   -1
	// 			^
	//		    |
	//			|
	// 0 <-- origin --> 0
	//		    |
	//			|
	//			v
	//			1
	const float HitDirection = Hit.Normal.Z;
	if (HitDirection > 0)
	{
		// Onscreen debug message:
		/* GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Black,
			FString::Printf(TEXT("Z Normal: %f"),HitDirection)
		); */

		JumpCount = 0;
	}
}
