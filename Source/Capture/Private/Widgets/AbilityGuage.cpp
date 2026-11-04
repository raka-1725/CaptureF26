

#include "Widgets/AbilityGuage.h"

void UAbilityGuage::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	UE_LOG(LogTemp, Warning, TEXT("AbilityGuage created for ability : %s"), *(ListItemObject->GetName()));
}
