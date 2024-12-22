// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FEditorsFavouriteLevelEditorToolbar
{
public:
	static void RegisterToolBar(const TSharedPtr<FUICommandList>& CommandList);

private:
	static TSharedRef<SWidget> GetApplicationActions();
};