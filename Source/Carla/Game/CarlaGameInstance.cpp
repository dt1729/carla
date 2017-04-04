// CARLA, Copyright (C) 2017 Computer Vision Center (CVC)

#include "Carla.h"
#include "CarlaGameInstance.h"

#include "CarlaGameController.h"
#include "CarlaSettings.h"
#include "MockGameController.h"

UCarlaGameInstance::UCarlaGameInstance() {
  CarlaSettings = CreateDefaultSubobject<UCarlaSettings>(TEXT("CarlaSettings"));
  check(CarlaSettings != nullptr);
  CarlaSettings->LoadSettings();
  CarlaSettings->LogSettings();
}

UCarlaGameInstance::~UCarlaGameInstance() {}

void UCarlaGameInstance::InitializeGameControllerIfNotPresent()
{
  if (GameController == nullptr) {
    if (CarlaSettings->bUseNetworking) {
      GameController = MakeUnique<CarlaGameController>(
          CarlaSettings->WorldPort,
          CarlaSettings->WritePort,
          CarlaSettings->ReadPort);
    } else {
      GameController = MakeUnique<MockGameController>();
      UE_LOG(LogCarla, Warning, TEXT("Using mock CARLA controller"));
    }
  }
}