// Copyright Epic Games, Inc. All Rights Reserved.

#include "GeoChatTestStyle.h"
#include "GeoChatTest.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include <Styling/SlateTypes.h>
#include <Styling/CoreStyle.h>

TSharedPtr< FSlateStyleSet > FGeoChatTestStyle::StyleInstance = NULL;

void FGeoChatTestStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FGeoChatTestStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FGeoChatTestStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("GeoChatTestStyle"));
	return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )
#define DEFAULT_FONT(...) FCoreStyle::GetDefaultFontStyle(__VA_ARGS__)

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);

TSharedRef< FSlateStyleSet > FGeoChatTestStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("GeoChatTestStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("GeoChatTest")->GetBaseDir() / TEXT("Resources"));

	Style->Set("GeoChatTest.PluginAction", new IMAGE_BRUSH(TEXT("ButtonIcon_40x"), Icon40x40));

	const FSlateFontInfo Mono9 = DEFAULT_FONT("Mono", 9);
	const FTextBlockStyle Default = FTextBlockStyle()
		.SetFont(Mono9)
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FVector2D::ZeroVector)
		.SetShadowColorAndOpacity(FLinearColor::Black)
		.SetHighlightColor(FLinearColor(0.02f, 0.3f, 0.0f))
		.SetHighlightShape(BOX_BRUSH("UI/TextBlockHighlightShape", FMargin(3.f / 8.f)));

	Style->Set("default", Default);
	Style->Set("others", FTextBlockStyle(Default).SetColorAndOpacity(FLinearColor(FColor(0xff57a64a)))); // green

	const FEditableTextBoxStyle ChatStyle = FEditableTextBoxStyle()
		.SetBackgroundColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.2f));
	

	Style->Set("chatStyle", ChatStyle);
	return Style;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT

void FGeoChatTestStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FGeoChatTestStyle::Get()
{
	return *StyleInstance;
}
