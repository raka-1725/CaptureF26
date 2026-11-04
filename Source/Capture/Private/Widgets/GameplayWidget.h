// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystem/CAbilityInputID.h"
#include "GameplayWidget.generated.h"

class UGameplayAbility;
/**
 * 
 */
UCLASS()
class UGameplayWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void InitializedWithAbilities(const TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& Abilities);
private:
	UPROPERTY(meta=(BindWidget))
	class UValueGuage* HealthBar;
	
	UPROPERTY(meta=(BindWidget))
	class UValueGuage* ManaBar;
	
	UPROPERTY()
	const class UCAbilitySystemComponent* OwnerAbilitySystemComponent;
	
	
};
