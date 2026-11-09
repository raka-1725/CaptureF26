

#include "Widgets/AbilityGuage.h"

#include "Components/Image.h"

void UAbilityGuage::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	UE_LOG(LogTemp, Warning, TEXT("AbilityGuage created for ability : %s"), *(ListItemObject->GetName()));
}

void UAbilityGuage::ConfigureWithWidgetData(const FAbilityWidgetData* AbilityWidgetData)
{
	if(Icon && AbilityWidgetData)
	{
		Icon->GetDynamicMaterial()->SetTextureParameterValue(IconTextureParamName, AbilityWidgetData->Icon.LoadSynchronous());
	}
}
