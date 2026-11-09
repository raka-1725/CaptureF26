// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ListView.h"
#include "AbilitySystem/CAbilityInputID.h"
#include "AbilityListView.generated.h"

class UGameplayAbility;
/**
 * 
 */
UCLASS()
class UAbilityListView : public UListView
{
	GENERATED_BODY()
public:
	virtual void NativeOnEntryGenerated(UUserWidget* EntryWidget) override;
	void ConfigureAbilities(const TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& Abilities);

	
private:
	UPROPERTY(EditAnywhere, Category = "Data")
	UDataTable* AbilityDataTable;
	
	const struct FAbilityWidgetData* FindWidgetDataForAbility(const TSubclassOf<UGameplayAbility>& AbilityClass) const;
};
