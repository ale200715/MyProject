
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemigo.generated.h"

UCLASS()
class MYPROJECT_API AEnemigo : public AActor
{
	GENERATED_BODY()

public:
	AEnemigo();

protected:
	virtual void BeginPlay() override;
	FVector PosicionInicial = FVector::ZeroVector;
	FVector DestinoActual = FVector::ZeroVector;
	int32 PasoActual = 0;

public:
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;
};