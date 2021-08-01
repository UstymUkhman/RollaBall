// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RollaBallPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ROLLABALL_API ARollaBallPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Sets default values for this pawn's properties
	ARollaBallPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Define Components:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* Camera;

	// Define Variables:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MoveForce = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float JumpImpulse = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaxJumpCount = 1;

private:
	// Define Functions:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Jump();

	int32 JumpCount = 0;
};
