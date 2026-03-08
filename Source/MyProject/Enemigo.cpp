#include "Enemigo.h"
#include "Components/StaticMeshComponent.h"

AEnemigo::AEnemigo()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemigoMesh"));
	RootComponent = Mesh;

	PasoActual = 0;
}

void AEnemigo::BeginPlay()
{
	Super::BeginPlay();

	PosicionInicial = GetActorLocation();

	DestinoActual = PosicionInicial;
	PasoActual = 0;
}

void AEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Mesh) return;

	FVector UbicacionActual = GetActorLocation();

	FVector NuevaUbicacion = FMath::VInterpTo(UbicacionActual, DestinoActual, DeltaTime, 5.0f);
	SetActorLocation(NuevaUbicacion);

	if (FVector::Dist(UbicacionActual, DestinoActual) < 50.0f)
	{
		PasoActual++;
		if (PasoActual > 20) PasoActual = 1;


		if (PasoActual == 1)      DestinoActual = PosicionInicial + FVector(2000, 0, 0);    
		else if (PasoActual == 2) DestinoActual = PosicionInicial + FVector(2000, 0, 800);  
		else if (PasoActual == 3) DestinoActual = PosicionInicial + FVector(0, 0, 800);    
		else if (PasoActual == 4) DestinoActual = PosicionInicial;                        
		else if (PasoActual == 5) DestinoActual = PosicionInicial + FVector(0, 2000, 0);    
		else if (PasoActual == 6) DestinoActual = PosicionInicial + FVector(2000, 2000, 0); 
		else if (PasoActual == 7) DestinoActual = PosicionInicial + FVector(2000, -2000, 0);
		else if (PasoActual == 8) DestinoActual = PosicionInicial + FVector(0, -2000, 1000);
		else { DestinoActual = PosicionInicial; }
	}
}