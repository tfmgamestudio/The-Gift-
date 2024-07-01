// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UInteractWidget::SetUp()
{
	//this->SetVisibility(ESlateVisibility::Hidden);
	this->InteractImage->SetVisibility(ESlateVisibility::Visible);
	this->InteractText->SetVisibility(ESlateVisibility::Hidden);
}

void UInteractWidget::OnActivate()
{

}

void UInteractWidget::OnDeactivate()
{

}
