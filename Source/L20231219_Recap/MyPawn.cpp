// Fill out your copyright notice in the Description page of Project Settings.



#include "MyPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RotatorComponent.h"
#include "MyRocket.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	RootComponent = Box;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Box);

	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Box);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Box);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	RotatorComponent = CreateDefaultSubobject<URotatorComponent>(TEXT("RotatorComponent"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/downloadedAssets/SM_P38_Body.SM_P38_Body'"));
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/downloadedAssets/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_Propeller.Succeeded())
	{
		Left->SetStaticMesh(SM_Propeller.Object);
		Right->SetStaticMesh(SM_Propeller.Object);
	}
	Left->AddLocalOffset(FVector(37.0f, -21.0f, 1.0f));
	Right->AddLocalOffset(FVector(37.0f, 21.0f, 1.0f));

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	RotatorComponent->Components.Add(Left);
	RotatorComponent->Components.Add(Right);

	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;

}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector());

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMyPawn::Fire);
	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMyPawn::Pitch);
	PlayerInputComponent->BindAxis(TEXT("Roll"), this, &AMyPawn::Roll);
}

void AMyPawn::Fire()
{
	GetWorld()->SpawnActor<AMyRocket>(
		AMyRocket::StaticClass()
		, Arrow->K2_GetComponentLocation()
		, Arrow->GetComponentRotation()
	);

}

void AMyPawn::Pitch(float Input)
{
	if (Input != 0)
	{
		AddActorLocalRotation(FRotator(
			UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60 * Input
			, 0
			, 0
		));
	}
}

void AMyPawn::Roll(float Input)
{
	if (Input != 0)
	{
		AddActorLocalRotation(FRotator(
			0
			, 0
			, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60 * Input
		));
	}
}

