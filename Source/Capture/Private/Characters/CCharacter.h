// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "CCharacter.generated.h"

UCLASS()
class ACCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACCharacter();
	
	void ServerSideInit();
	void ClientSideInit();
	bool IsLocallyControlledByPlayer() const;
	virtual void PossessedBy(AController* NewController) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//------------------//
	// Gameplay Ability //
	//------------------//
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
private:
	void BindGASDelegates();
	void DeathTagUpdated(const struct FGameplayTag Tag, int32 Count);
	bool bGASDelegateBound;	
	UPROPERTY(VisibleDefaultsOnly, Category = "Ability System")
	class UCAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY()
	class UCAttributeSet* CAttributeSet;
	//------------------//
	// Death & Respawn	//
	//------------------//
private:
	void StartDeathSequence();
	void Respawn();
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	UAnimMontage* DeathMontage;
	
	void PlayDeathMontage();
	
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	UAnimMontage* RespawnMontage;
	void PlayRespawnMontage();
	
	//------------------//
	//		 Widget		//
	//------------------//
	
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "UI")
	class UWidgetComponent* OverHeadWidgetComponent;
	
	void ConfigureOverHeadWidgetComponent();

};
