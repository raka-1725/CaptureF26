

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "AbilityGuage.generated.h"

/**
 * 
 */
UCLASS()
class UAbilityGuage : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject);
	
private:
	UPROPERTY(meta=(BindWidget))
	class UImage* Icon;
	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* CooldownDurationText;
	
	UPROPERTY(meta=(BindWidget))
	class  UTextBlock* CostText;
	
	UPROPERTY(meta=(BindWidget))
	class  UTextBlock* CooldownCounterText;
};
