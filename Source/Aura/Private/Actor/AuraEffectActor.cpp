// Copyright


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	//if (!IsValid(TargetActor) || !IsValid(GameplayEffectClass)) return;
	
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	//if (!IsValid(TargetASC)) return;
	if (TargetASC == nullptr) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(
		GameplayEffectClass, 1.f, EffectContextHandle);

	if (!EffectSpecHandle.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid EffectSpecHandle for effect %s"), *GetNameSafe(GameplayEffectClass));
	}

	// if (EffectSpecHandle.IsValid() && EffectSpecHandle.Data.IsValid())
	// {
	// 	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("EffectSpecHandle is invalid or missing Data for %s"), *GetNameSafe(GameplayEffectClass));
	// }
	
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}