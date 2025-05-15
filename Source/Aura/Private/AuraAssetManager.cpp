// Copyright


#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"
#include "EngineGlobals.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Engine/Engine.h"
#include "AbilitySystemGlobals.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);

	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FAuraGameplayTags::InitializeNativeGameplayTags();

	//This is required to use Target Data!
	UAbilitySystemGlobals::Get().InitGlobalData();
}