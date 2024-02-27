// Fill t your copyright notice in the Description page of Project Settings.


#include "SMainMenuWidget.h"
# define LOCTEXT_NAMESPACE "MainMenu"
#include "MenuHUD.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

void SMainMenuWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	OwningHUD = InArgs._OwningHUD;

	const FMargin ContentPadding = FMargin(500.0f, 300.0f);
	const FMargin ButtonPadding = FMargin(10.0f);

	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextStyle.Size = 40.0f;

	FSlateFontInfo TitleTextStyle = ButtonTextStyle;
	TitleTextStyle.Size = 60.0f;

	const FText TitleText = LOCTEXT("GameTitle", "Music in Motion");
	const FText PlayText = LOCTEXT("PlayText", "Play");
	const FText QuitText = LOCTEXT("QuitText", "Exit");


	ChildSlot[
		SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.ColorAndOpacity(FColor::Black)
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(ContentPadding)
			[
				SNew(SVerticalBox)

				//Title Text
				+ SVerticalBox::Slot()
				[
					SNew(STextBlock)
					.Text(TitleText)
					.Font(TitleTextStyle)
					.Justification(ETextJustify::Center)
				]

				//Play Button
				+ SVerticalBox::Slot()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SMainMenuWidget::OnPlayClicked)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(PlayText)
						.Justification(ETextJustify::Center)
					]
				]

				//Quit Button
				+ SVerticalBox::Slot()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SMainMenuWidget::OnQuitClicked)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(QuitText)
						.Justification(ETextJustify::Center)
					]
				]
			]
	];
}
FReply SMainMenuWidget::OnPlayClicked() const
{
	OwningHUD->RemoveMenu();
	UGameplayStatics::OpenLevel(OwningHUD->PlayerOwner->GetWorld(), "BeachLevel");
	return FReply::Handled();
}
FReply SMainMenuWidget::OnQuitClicked() const
{
	if (OwningHUD.IsValid()) {
		if (APlayerController* PC = OwningHUD->PlayerOwner) {
			PC->ConsoleCommand("quit");
		}
	}
	return FReply::Handled();
}
#undef LOCTEXT_NAMESPACE