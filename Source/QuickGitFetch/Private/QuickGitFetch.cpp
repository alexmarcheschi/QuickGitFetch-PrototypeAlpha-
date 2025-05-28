// Prototype Quick git Fetch, Compilable for U.E 5.1.1, Windows Only

#include "QuickGitFetch.h"
#include "QuickGitFetchStyle.h"
#include "QuickGitFetchCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include <cstdlib>

static const FName QuickGitFetchTabName("QuickGitFetch");

#define LOCTEXT_NAMESPACE "FQuickGitFetchModule"

void FQuickGitFetchModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FQuickGitFetchStyle::Initialize();
	FQuickGitFetchStyle::ReloadTextures();

	FQuickGitFetchCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FQuickGitFetchCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FQuickGitFetchModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FQuickGitFetchModule::RegisterMenus));

	FString ProjectDir = FPaths::ProjectDir();
	FString PluginDir = FPaths::ProjectPluginsDir();
	FString CurrentPluginPath = FPaths::ConvertRelativePathToFull(PluginDir);

	CurrentPluginPath = CurrentPluginPath + +"QuickGitFetch/";

	FString Pull = "GitPull.bat ";
	FString Fetch = "GitFetch.bat ";

	FString FullPathFetch = CurrentPluginPath + Fetch;
	FString FullPathPull = CurrentPluginPath + Pull;

	FString CommandToExecuteFetch = FullPathFetch + ProjectDir;
	FString CommandToExecutePull = FullPathPull + ProjectDir;

	char* CommandCharFetch = TCHAR_TO_ANSI(*CommandToExecuteFetch);
	char* CommandCharPull = TCHAR_TO_ANSI(*CommandToExecutePull);

	UE_LOG(LogTemp, Log, TEXT("Checking GitHub update..."));

	system(CommandCharFetch);
	system(CommandCharPull);
}

void FQuickGitFetchModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FQuickGitFetchStyle::Shutdown();

	FQuickGitFetchCommands::Unregister();
}

void FQuickGitFetchModule::PluginButtonClicked()
{
	FString ProjectDir = FPaths::ProjectDir();
	FString PluginDir = FPaths::ProjectPluginsDir();
	FString CurrentPluginPath = FPaths::ConvertRelativePathToFull(PluginDir);

	CurrentPluginPath = CurrentPluginPath + +"QuickGitFetch/";

	FString File = "GitPush.bat ";

	FString FullPath = CurrentPluginPath + File;
	char* FullPathChar = TCHAR_TO_ANSI(*FullPath);

	FString CommandToExecute = FullPath + ProjectDir;
	char* CommandChar = TCHAR_TO_ANSI(*CommandToExecute);

	UE_LOG(LogTemp, Log, TEXT("Git Fetch requested: %s"), *FullPath);

	system(CommandChar);
}

void FQuickGitFetchModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FQuickGitFetchCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FQuickGitFetchCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQuickGitFetchModule, QuickGitFetch)
