// Prototype Quick git Fetch, Compilable for U.E 5.1.1, Windows Only
#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "QuickGitFetchStyle.h"

class FQuickGitFetchCommands : public TCommands<FQuickGitFetchCommands>
{
public:

	FQuickGitFetchCommands()
		: TCommands<FQuickGitFetchCommands>(TEXT("QuickGitFetch"), NSLOCTEXT("Contexts", "QuickGitFetch", "QuickGitFetch Plugin"), NAME_None, FQuickGitFetchStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
