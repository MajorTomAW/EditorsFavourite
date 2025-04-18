// Copyright © 2025 MajorT. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class IEditorsFavouriteModule : public IModuleInterface
{
public:
	/**
	 * Singleton-like access to this module's interface. This is just for convenience!
	 * Beware of calling this during the shutdown phase, though. Your module might have been unloaded already.
	 *
	 * @returns Singleton instance, loading the module on demand if needed
	 */
	static IEditorsFavouriteModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IEditorsFavouriteModule>("EditorsFavourite");
	}
	
	/** Returns the command list for this module */
	virtual TSharedPtr<FUICommandList> GetCommandList() const = 0;
};