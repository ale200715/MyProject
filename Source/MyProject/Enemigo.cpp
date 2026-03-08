#include "Enemigo.h"
#include "Components/StaticMeshComponent.h"

AEnemigo::AEnemigo()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemigoMesh"));
	RootComponent = Mesh;

	// Inicializamos el paso en 0
	PasoActual = 0;
}

void AEnemigo::BeginPlay()
{
	Super::BeginPlay();

	// Primero guardamos la posición
	PosicionInicial = GetActorLocation();

	// Luego decimos que el primer destino es esa misma posición
	DestinoActual = PosicionInicial;
	PasoActual = 0;
}

void AEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Mesh) return;

	FVector UbicacionActual = GetActorLocation();

	// Aumentamos el último número (5.0f) para que viaje más RÁPIDO
	FVector NuevaUbicacion = FMath::VInterpTo(UbicacionActual, DestinoActual, DeltaTime, 5.0f);
	SetActorLocation(NuevaUbicacion);

	// Si está cerca del punto (menos de 50 unidades), cambia al siguiente
	if (FVector::Dist(UbicacionActual, DestinoActual) < 50.0f)
	{
		PasoActual++;
		if (PasoActual > 20) PasoActual = 1;

		// --- MOVIMIENTOS LARGOS Y CLAROS ---
		// FVector(X, Y, Z) -> X es adelante, Y es lado, Z es arriba

		if (PasoActual == 1)      DestinoActual = PosicionInicial + FVector(2000, 0, 0);    // 20 metros adelante
		else if (PasoActual == 2) DestinoActual = PosicionInicial + FVector(2000, 0, 800);  // Sube recto
		else if (PasoActual == 3) DestinoActual = PosicionInicial + FVector(0, 0, 800);     // Vuelve atrás por arriba
		else if (PasoActual == 4) DestinoActual = PosicionInicial;                         // Baja a casa
		else if (PasoActual == 5) DestinoActual = PosicionInicial + FVector(0, 2000, 0);    // 20 metros a la derecha
		else if (PasoActual == 6) DestinoActual = PosicionInicial + FVector(2000, 2000, 0); // Diagonal larga
		else if (PasoActual == 7) DestinoActual = PosicionInicial + FVector(2000, -2000, 0);// Gran cruce lateral
		else if (PasoActual == 8) DestinoActual = PosicionInicial + FVector(0, -2000, 1000);// Izquierda y muy arriba
		// ... puedes seguir sumando pasos hasta el 20 siguiendo este patrón
		else { DestinoActual = PosicionInicial; }
	}
}