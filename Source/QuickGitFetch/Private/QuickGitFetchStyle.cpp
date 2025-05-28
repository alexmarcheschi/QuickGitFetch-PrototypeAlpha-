// Prototype Quick git Fetch, Compilable for U.E 5.1.1, Windows Only

#include "QuickGitFetchStyle.h"
#include "QuickGitFetch.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FQuickGitFetchStyle::StyleInstance = nullptr;

void FQuickGitFetchStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FQuickGitFetchStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FQuickGitFetchStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("QuickGitFetchStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FQuickGitFetchStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("QuickGitFetchStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("QuickGitFetch")->GetBaseDir() / TEXT("Resources"));

	Style->Set("QuickGitFetch.PluginAction", new IMAGE_BRUSH_SVG(TEXT("Button"), Icon20x20));
	return Style;
}

void FQuickGitFetchStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FQuickGitFetchStyle::Get()
{
	return *StyleInstance;
}
