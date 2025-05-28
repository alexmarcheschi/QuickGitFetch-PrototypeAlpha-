// Prototype Quick git Fetch, Compilable for U.E 5.1.1, Windows Only

#include "QuickGitFetchCommands.h"

#define LOCTEXT_NAMESPACE "FQuickGitFetchModule"

void FQuickGitFetchCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "QuickGitFetch", "Carica le modifiche su GitHub.", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
