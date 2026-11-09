

#include "Widgets/AbilityGuage.h"

#include "Abilities/GameplayAbility.h"
#include "AbilitySystemComponent.h"
#include  "AbilitySystemBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UAbilityGuage::NativeConstruct()
{
	Super::NativeConstruct();
	
	CooldownCounterText->SetVisibility(ESlateVisibility::Hidden);
	
	UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningPlayerPawn());
	if (OwnerASC)
	{
		OwnerASC->AbilityCommittedCallbacks.AddUObject(this, &UAbilityGuage::AbilityCommitted);
		OwnerASC->AbilitySpecDirtiedCallbacks.AddUObject(this, &UAbilityGuage::AbilitySpecUpdated);
	}
}

void UAbilityGuage::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	UE_LOG(LogTemp, Warning, TEXT("AbilityGuage created for ability : %s"), *(ListItemObject->GetName()));
	CachedAbilityCDO = Cast<UGameplayAbility>(ListItemObject);
	
	float CooldownDuration = GetStaticCooldownDuration();
	float Cost = GetStaticCost();
	
	CooldownDurationText->SetText(FText::AsNumber(CooldownDuration));
	CostText->SetText(FText::AsNumber(FMath::Abs(Cost)));
}

void UAbilityGuage::ConfigureWithWidgetData(const FAbilityWidgetData* AbilityWidgetData)
{
	if(Icon && AbilityWidgetData)
	{
		Icon->GetDynamicMaterial()->SetTextureParameterValue(IconTextureParamName, AbilityWidgetData->Icon.LoadSynchronous());
	}
}

float UAbilityGuage::GetStaticCooldownDuration() const
{
	if (!CachedAbilityCDO)
		return 0.0f;
	const UGameplayEffect* CooldownEffect = CachedAbilityCDO->GetCooldownGameplayEffect();
	if (!CooldownEffect)
		return 0.0f;
	
	float CooldownDuration = 0.0f;
	if (CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1, CooldownDuration))
	{
		return CooldownDuration;
	}
	
	return 0.0f;
}

float UAbilityGuage::GetStaticCost() const
{
	if (!CachedAbilityCDO)
		return 0.0f;
	
	const UGameplayEffect* CostEffect = CachedAbilityCDO->GetCostGameplayEffect();
	if (!CostEffect || CostEffect->Modifiers.Num() == 0)
		return 0.0f;
	
	float Cost = 0.0f;
	if (CostEffect->Modifiers[0].ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Cost))
		return Cost;
	
	return 0.0f;
}

void UAbilityGuage::AbilityCommitted(UGameplayAbility* Ability)
{
	if (Ability->GetClass()->GetDefaultObject() == CachedAbilityCDO)
	{
		float CooldownTimeRemaining = 0.0f;
		float CooldownDuration = 0.0f;
		
		Ability->GetCooldownTimeRemainingAndDuration(Ability->GetCurrentAbilitySpecHandle(),
			Ability->GetCurrentActorInfo(), CooldownTimeRemaining, CooldownDuration);
		
		StartCooldown(CooldownTimeRemaining, CooldownDuration);
	}
}

void UAbilityGuage::StartCooldown(float CooldownTimeRemaining, float CooldownDuration)
{
	CachedCooldownDuration = CooldownDuration;
	CooldownCounterText->SetText(FText::AsNumber(CooldownDuration));
	CachedCooldownTimeRemaining = CooldownTimeRemaining;
	
	CooldownCounterText->SetVisibility(ESlateVisibility::Visible);
	
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UAbilityGuage::CooldownFinished, CooldownTimeRemaining);
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerUpdateHandle, this, &UAbilityGuage::UpdateCooldown, CooldownUpdateInterval, true, 0.0f);
}

void UAbilityGuage::UpdateCooldown()
{
	CachedCooldownTimeRemaining -= CooldownUpdateInterval;
	int NumberDigits = CachedCooldownTimeRemaining >= 1.0 ? 0 : 2;
	FNumberFormattingOptions FormattingOptions = FNumberFormattingOptions().SetMaximumFractionalDigits(NumberDigits);
	CooldownCounterText->SetText(FText::AsNumber(CachedCooldownTimeRemaining, &FormattingOptions));
	Icon->GetDynamicMaterial()->SetScalarParameterValue(CooldownPercentParamName, 1 - (CachedCooldownTimeRemaining / CachedCooldownDuration));
	//UE_LOG(LogTemp, Warning, TEXT("CooldownProgressPercent: %f"), CooldownProgressPercent);
	
}
void UAbilityGuage::CooldownFinished()
{
	CachedCooldownDuration = CachedCooldownTimeRemaining = 0.0f;
	GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandle);
	CooldownCounterText->SetVisibility(ESlateVisibility::Hidden);	
}

void UAbilityGuage::AbilitySpecUpdated(const FGameplayAbilitySpec& AbilitySpec)
{
	//react to spec changes like level.
}

