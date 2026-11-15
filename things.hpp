#include "Inventory.hpp"
#pragma once

class helmet : public InventoryItem {
 public:
  helmet(long long i, std::string n) {
    id.reset(new long long(i));
    name = std::make_shared<std::string>(n);
  }
  ~helmet() override {
    id.reset();
    name.reset();
  }

  long long inventoryid() override { return *id; }

  std::string title() override { return *name; }

  void describe() override {
    std::cout << "Шлем.\n";
    std::cout << "Модель - " << *name << '\n';
    std::cout << "Регистрационный номер - " << *id << '\n';
    std::cout << "Предоставляемый аксессуар для защиты во время езды.\n";
  }
};

class dock_station : public EnergyConsumer {
 public:
  dock_station(long long i, std::string n, long long e) {
    id.reset(new long long(i));
    name = std::make_shared<std::string>(n);
    energy = std::make_unique<long long>(e);
  }
  ~dock_station() override {
    id.reset();
    name.reset();
    energy = nullptr;
  }

  long long inventoryid() override { return *id; }

  std::string title() override { return *name; }

  void describe() override {
    std::cout << "Док-станция.\n";
    std::cout << "Модель - " << *name << '\n';
    std::cout << "Регистрационный номер - " << *id << '\n';
    std::cout << "Потребляет " << *energy << " энергии в день.\n";
    std::cout << "Нужна для подзарядки.\n";
  }
  long long dailyEnergy() override { return *energy; }
};