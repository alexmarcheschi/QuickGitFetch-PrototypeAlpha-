// Prototype Quick git Fetch, Compilable for U.E 5.1.1, Windows Only

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

class FQuickGitFetchStyle
{
public:

	FString InContent(const FString& RelativePath, const ANSICHAR* Extension);

	static void Initialize();

	static void Shutdown();

	/** reloads textures used by slate renderer */
	static void ReloadTextures();

	/** @return The Slate style set for the Shooter game */
	static const ISlateStyle& Get();

	static FName GetStyleSetName();

private:

	static TSharedRef< class FSlateStyleSet > Create();

private:

	static TSharedPtr< class FSlateStyleSet > StyleInstance;
};
