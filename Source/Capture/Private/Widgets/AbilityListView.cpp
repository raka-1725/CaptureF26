// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/AbilityListView.h"
#include "Abilities/GameplayAbility.h"
#include "AbilityGuage.h"

void UAbilityListView::ConfigureAbilities(const TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& Abilities)
{
	for (const TPair<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& AbilityPair : Abilities)
	{
		//Need inherit from IUserObjectListEntry
		// We use the default object of the ability class to be the item aded in.
		AddItem(AbilityPair.Value->GetDefaultObject());
	}
}

void UAbilityListView::NativeOnEntryGenerated(UUserWidget* EntryWidget)
{
	UAbilityGuage* AbilityGuage = Cast<UAbilityGuage>(EntryWidget);
	if (AbilityGuage)
	{
		AbilityGuage->ConfigureWithWidgetData(FindWidgetDataForAbility(AbilityGuage->GetListItem()->GetClass()));
	}
}

const struct FAbilityWidgetData* UAbilityListView::FindWidgetDataForAbility(
	const TSubclassOf<UGameplayAbility>& AbilityClass) const
{
	if (!AbilityDataTable) return nullptr;
	
	for (auto& AbilityWidgetDataPair : AbilityDataTable->GetRowMap())
	{
		const FAbilityWidgetData* WidgetData = AbilityDataTable->FindRow<struct FAbilityWidgetData>(AbilityWidgetDataPair.Key, "" );
		if (WidgetData->AbilityClass == AbilityClass) return WidgetData;
	}
	
	return nullptr;
}
