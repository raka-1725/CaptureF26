// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ValueGuage.h"

#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "ProfilingDebugging/CookStats.h"

void UValueGuage::NativePreConstruct()
{
	//called when something edited in editor
	Super::NativePreConstruct();
	
	ProgressBar->SetFillColorAndOpacity(BarColor);
	
}

void UValueGuage::SetAndBindWithAbilitySystemComponent(class UAbilitySystemComponent* AbilitySystemComponent,
	const struct FGameplayAttribute& Attribute, const struct FGameplayAttribute& MaxAttribute)
{
	if (AbilitySystemComponent)
	{
		bool bIsFound = false;
		float Value = AbilitySystemComponent->GetGameplayAttributeValue(Attribute, bIsFound);
	
		if (!bIsFound)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cant find attribute : %s"), *(Attribute.GetName()))
		}
		
		float MaxValue = AbilitySystemComponent->GetGameplayAttributeValue(MaxAttribute, bIsFound);
		if (!bIsFound)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cant find attribute : %s"), *(MaxAttribute.GetName()))
		}
		
		SetValue(Value, MaxValue);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &UValueGuage::ValueChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUObject(this, &UValueGuage::MaxValueChanged);
	}
}

void UValueGuage::SetValue(float NewValue, float NewMaxValue)
{
	if (NewMaxValue == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("max value cannot be 0 for value gauge"))
		return;
	}
	
	ProgressBar->SetPercent(NewValue / NewMaxValue);
	
	
	static FNumberFormattingOptions FormattingOptions = FNumberFormattingOptions().SetMaximumFractionalDigits(0);
	ValueText->SetText(
		FText::Format
		(
			FTextFormat::FromString("{0}/{1}"),
			FText::AsNumber(NewValue, &FormattingOptions),
			FText::AsNumber(NewMaxValue, &FormattingOptions))
		);
	
	
}

void UValueGuage::ValueChanged(const struct FOnAttributeChangeData& ChangedData)
{
	SetValue(ChangedData.NewValue, CachedMaxValue);
}

void UValueGuage::MaxValueChanged(const struct FOnAttributeChangeData& ChangedData)
{
	SetValue(CachedValue, ChangedData.NewValue);
}
