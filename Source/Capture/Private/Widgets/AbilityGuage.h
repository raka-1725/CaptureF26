

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityGuage.generated.h"

/**
 * 
 */
UCLASS()
class UAbilityGuage : public UUserWidget
{
	GENERATED_BODY()
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
