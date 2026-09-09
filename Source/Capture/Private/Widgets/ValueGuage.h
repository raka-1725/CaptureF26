// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ValueGuage.generated.h"

/**
 * 
 */
UCLASS()
class UValueGuage : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativePreConstruct() override;
	void SetAndBindWithAbilitySystemComponent(class UAbilitySystemComponent* AbilitySystemComponent,
		const struct FGameplayAttribute& Attribute, const struct FGameplayAttribute& MaxAttribute);
	
	void SetValue(float NewValue, float NewMaxValue);
private:
	UPROPERTY(meta =(BindWidget))
	class UProgressBar* ProgressBar;
	
	UPROPERTY(meta =(BindWidget))
	class UTextBlock* ValueText;
	
	UPROPERTY(EditAnywhere, Category = "ValueGuage")
	FLinearColor BarColor;
	
	void ValueChanged(const struct FOnAttributeChangeData& ChangedData);
	void MaxValueChanged(const struct FOnAttributeChangeData& ChangedData);
	
	float CachedValue;
	float CachedMaxValue;
};
