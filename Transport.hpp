#include "Inventory.hpp"
#pragma once

class bike : public ScoreItem {
 public:
  bike(long long i, std::string n, long long s) {
    id.reset(new long long(i));
    name = std::make_shared<std::string>(n);
    score = std::make_unique<long long>(s);
  }
  ~bike() override {
    id.reset();
    name.reset();
    score = nullptr;
  }

  long long inventoryid() override { return *id; }

  std::string title() override { return *name; }

  void describe() override {
    std::cout << "Велосипед.\n";
    std::cout << "Модель - " << *name << '\n';
    std::cout << "Регистрационный номер - " << *id << '\n';
    std::cout << "Сложность для новичка - " << *score << '\n';
    std::cout << "Механический участник парка. Электроэнергию не потребляет.\n";
  }
};

class kick_scooter : public ScoreItem {
 public:
  kick_scooter(long long i, std::string n, long long s) {
    id.reset(new long long(i));
    name = std::make_shared<std::string>(n);
    score = std::make_unique<long long>(s);
  }
  ~kick_scooter() override {
    id.reset();
    name.reset();
    score = nullptr;
  }

  long long inventoryid() override { return *id; }

  std::string title() override { return *name; }

  void describe() override {
    std::cout << "Самокат.\n";
    std::cout << "Модель - " << *name << '\n';
    std::cout << "Регистрационный номер - " << *id << '\n';
    std::cout << "Сложность для новичка - " << *score << '\n';
    std::cout << "Механический участник парка. Электроэнергию не потребляет.\n";
  }
};

class scooter : public ScoreItem, public EnergyConsumer {
 public:
  scooter(long long i, std::string n, long long e, long long s) {
    id.reset(new long long(i));
    name = std::make_shared<std::string>(n);
    score = std::make_unique<long long>(s);
    energy = std::make_unique<long long>(e);
  }
  ~scooter() override {
    id.reset();
    name.reset();
    score = nullptr;
    energy = nullptr;
  }

  long long inventoryid() override { return *id; }

  std::string title() override { return *name; }

  void describe() override {
    std::cout << "Электросамокат.\n";
    std::cout << "Модель - " << *name << '\n';
    std::cout << "Регистрационный номер - " << *id << '\n';
    std::cout << "Сложность для новичка - " << *score << '\n';
    std::cout << "Потребляет " << *energy << " энергии в день.\n";
  }

  long long dailyEnergy() override { return *energy; }
};

class ebike : public ScoreItem, public EnergyConsumer {
 public:
  ebike(long long i, std::string n, long long e, long long s) {
    id.reset(new long long(i));
    name = std::make_shared<std::string>(n);
    score = std::make_unique<long long>(s);
    energy = std::make_unique<long long>(e);
  }
  ~ebike() override {
    id.reset();
    name.reset();
    score = nullptr;
    energy = nullptr;
  }

  long long inventoryid() override { return *id; }

  std::string title() override { return *name; }

  void describe() override {
    std::cout << "Электровелосипед.\n";
    std::cout << "Модель - " << *name << '\n';
    std::cout << "Регистрационный номер - " << *id << '\n';
    std::cout << "Сложность для новичка - " << *score << '\n';
    std::cout << "Потребляет " << *energy << " энергии в день.\n";
  }

  long long dailyEnergy() override { return *energy; }
};