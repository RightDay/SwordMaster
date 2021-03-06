// Fill out your copyright notice in the Description page of Project Settings.


#include "SMItemBox.h"
#include "SMWeapon.h"
#include "SMCharacter.h"

// Sets default values
ASMItemBox::ASMItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);
	Effect->SetupAttachment(RootComponent);

	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("StaticMesh'/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1'"));
	if (SM_BOX.Succeeded())
	{
		Box->SetStaticMesh(SM_BOX.Object);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_CHESTOPEN(TEXT("ParticleSystem'/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh'"));
	if (P_CHESTOPEN.Succeeded())
	{
		Effect->SetTemplate(P_CHESTOPEN.Object);
		Effect->bAutoActivate = false;
	}

	Box->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));

	Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	Box->SetCollisionProfileName(TEXT("NoCollision"));
	WeaponItemClass = ASMWeapon::StaticClass();
}

// Called when the game starts or when spawned
void ASMItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASMItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASMItemBox::OnCharacterOverlap);
}

void ASMItemBox::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SMLOG_S(Warning);

	auto SMCharacter = Cast <ASMCharacter> (OtherActor);
	SMCHECK(nullptr != SMCharacter);

	if (nullptr != SMCharacter && nullptr != WeaponItemClass)
	{
		if (SMCharacter->CanSetWeapon())
		{
			auto NewWeapon = GetWorld()->SpawnActor<ASMWeapon>(WeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
			SMCharacter->SetWeapon(NewWeapon);
			Effect->Activate(true);
			Box->SetHiddenInGame(true, true);
			SetActorEnableCollision(false);
			Effect->OnSystemFinished.AddDynamic(this, &ASMItemBox::OnEffectFinished);
		}
		else
		{
			SMLOG(Warning, TEXT("%s can't equip weapon currently."), * SMCharacter->GetName());
		}
	}
}

void ASMItemBox::OnEffectFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}
