// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MusicNote.generated.h"

class ACharacter;
class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class MUSICINMOTION_API AMusicNote : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMusicNote();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	USceneComponent* TopOfNote;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	USceneComponent* BottomOfNote;

	UFUNCTION(BlueprintCallable)
	void Initialize(float speed, FVector Direction);

private:
	float lengthModifier = 1.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere)
	float MusicSpeed;
	UPROPERTY(VisibleAnywhere)
	FVector MusicDirection;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
