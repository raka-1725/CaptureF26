// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CCharacter.h"

#include "AbilitySystem/CAbilitySystemComponent.h"
#include "AbilitySystem/CAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "Widgets/OverheadStatusGauge.h"
//#include "AbilitySystemComponent.h"

// Sets default values
ACCharacter::ACCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<UCAbilitySystemComponent>("AbilitySystemComponent");
	CAttributeSet = CreateDefaultSubobject<UCAttributeSet>("CAttributeSet");
	
	OverHeadWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Overhead Widget Component");
	OverHeadWidgetComponent->SetupAttachment(GetRootComponent());
}

void ACCharacter::ServerSideInit()
{
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	AbilitySystemComponent->ApplyInitialEffects();
}

void ACCharacter::ClientSideInit()
{
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
}



// Called when the game starts or when spawned
void ACCharacter::BeginPlay()
{
	Super::BeginPlay();
	/*if (!CAttributeSet)
	{
		CAttributeSet = NewObject<UCAttributeSet>(this);
		AbilitySystemComponent->AddAttributeSetSubobject(CAttributeSet);
	}*/
	ConfigureOverHeadWidgetComponent();
}

// Called every frame
void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ACCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACCharacter::ConfigureOverHeadWidgetComponent()
{
	if (!OverHeadWidgetComponent) return;
	
	if (IsLocallyControlledByPlayer())
	{
		OverHeadWidgetComponent->SetHiddenInGame(true);
		return;
	}
		
	UOverheadStatusGauge* OverheadStatusGauge = Cast<UOverheadStatusGauge>(OverHeadWidgetComponent->GetUserWidgetObject());
	if (OverheadStatusGauge)
	{
		OverheadStatusGauge->ConfigureWithAbilitySystemComponent(GetAbilitySystemComponent());
	}
	OverHeadWidgetComponent->SetHiddenInGame(false);
}

bool ACCharacter::IsLocallyControlledByPlayer() const
{
	//checking if it is local AND if it is player controller NOT AI
 	return IsLocallyControlled() && GetController()->IsPlayerController();
}
void ACCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (NewController && !NewController->IsPlayerController())
	{
		ServerSideInit();
	}
}
