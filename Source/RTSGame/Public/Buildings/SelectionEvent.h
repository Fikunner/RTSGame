// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectionEvent.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class USelectionEvent : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTSGAME_API ISelectionEvent
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void SelectThisActor(AActor* SelectedActor) { check(0); }
	virtual void SelectThis() { check(0); }
	virtual void ClickSelectThisActor(AActor* SelectedActor) { check(0); }
	virtual void DeselectThisActor(AActor* DeselectedActor) { check(0); }
	virtual void DeselectThis() { check(0); }

};
