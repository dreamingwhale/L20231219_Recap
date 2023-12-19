// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UFloatingPawnMovement;
class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;
class URotatorComponent;

UCLASS()
class L20231219_RECAP_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,Category = "Component")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,Category = "Component")
	TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,Category = "Component")
	TObjectPtr<UStaticMeshComponent> Left;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,Category = "Component")
	TObjectPtr<UStaticMeshComponent> Right;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,Category = "Component")
	TObjectPtr<UFloatingPawnMovement> Movement;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,Category = "Component")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,Category = "Component")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,Category = "Component")
	TObjectPtr<UArrowComponent> Arrow;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,Category = "Component")
	TObjectPtr<URotatorComponent> RotatorComponent;

	void Fire();
	void Pitch(float Input);
	void Roll(float Input);
};