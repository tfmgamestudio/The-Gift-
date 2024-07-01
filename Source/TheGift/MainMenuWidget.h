#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

UCLASS()
class THEGIFT_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	// Principal buttons
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) UUserWidget* MainButtonWidget = nullptr;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) UUserWidget* SettingsButtonWidget = nullptr;

	// // Secondary buttons
	// UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UUserWidget* NewGameButton = nullptr;
	// UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UUserWidget* LoadGameButton = nullptr;
	// UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UUserWidget* SettingsGameButton = nullptr;
	// UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UUserWidget* SettingsVideoButton = nullptr;
	// UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UUserWidget* SettingsSoundButton = nullptr;
	// UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UUserWidget* SettingsControlsButton = nullptr;

protected:

	//virtual void NativeConstruct() override;
};