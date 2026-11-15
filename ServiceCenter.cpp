#include <algorithm>
#include <map>
#include <limits>
#include "Errors.hpp"
#include "Inventory.hpp"
#include "Registry.hpp"
#include "Transport.hpp"
#include "things.hpp"

struct Storage {
  Registry<InventoryItem> Inventory;
  Registry<ScoreItem> For_New;
  Registry<EnergyConsumer> EnergyConsumers;
  std::weak_ptr<InventoryItem> focused;
};

bool Cmp(std::shared_ptr<InventoryItem>& a, std::shared_ptr<InventoryItem>& b) {
  return *a < *b;
}

void add(Storage& storage);
void add_bike(Storage& storage);
void add_ebike(Storage& storage);
void add_scooter(Storage& storage);
void add_kick_scooter(Storage& storage);
void add_helmet(Storage& storage);
void add_dock_station(Storage& storage);
void energy(Storage& storage);
void novice(Storage& storage);
void focus(Storage& storage);
void show_focus(Storage& storage);
void erase(Storage& storage);
void count_novice(Storage& storage);

void add(Storage& storage) {
  std::string cmd;
  std::cin >> cmd;
  std::map<std::string, void (*)(Storage&)> commands = {
      {"add_bike", add_bike},       {"add_ebike", add_ebike},
      {"add_scooter", add_scooter}, {"add_kickscooter", add_kick_scooter},
      {"add_helmet", add_helmet},   {"add_dock_station", add_dock_station}};
  auto it = commands.find(cmd);

  if (it == commands.end()) {
    throw GibberishError();
  }
  it->second(storage);
  std::sort(storage.Inventory.begin(), storage.Inventory.end(), Cmp);
  std::cout << "объект успешно добавлен\n";
}
void add_bike(Storage& storage) {
  long long id(0);
  std::string name;
  long long score(0);
  std::cin >> id >> name >> score;
  if (!std::cin) {
    throw std::invalid_argument("неправильный ввод");
  }
  if (name.find("broken") != static_cast<size_t>(-1)) {
    throw InspectionError("вещь неисправна");
  }
  if (score < 1 || score > 10) {
    throw SimplicityError();
  }
  std::shared_ptr<bike> obj = std::make_shared<bike>(id, name, score);
  storage.Inventory.add(obj);
  if (score > 5) {
    storage.For_New.add(obj);
  }
}

void add_ebike(Storage& storage) {
  long long id(0);
  std::string name;
  long long score(0);
  long long energy(0);
  std::cin >> id >> name >> energy >> score;
  if (!std::cin) {
    throw std::invalid_argument("неправильный ввод");
  }
  if (name.find("broken") != static_cast<size_t>(-1)) {
    throw InspectionError("вещь неисправна");
  }
  if (score < 1 || score > 10) {
    throw SimplicityError();
  }
  if (energy < 0) {
    throw EnergyError();
  }
  std::shared_ptr<ebike> obj = std::make_shared<ebike>(id, name, energy, score);
  storage.Inventory.add(obj);
  if (score > 5) {
    storage.For_New.add(obj);
  }
  storage.EnergyConsumers.add(obj);
}

void add_scooter(Storage& storage) {
  long long id(0);
  std::string name;
  long long score(0);
  long long energy(0);
  std::cin >> id >> name >> energy >> score;
  if (!std::cin) {
    throw std::invalid_argument("неправильный ввод");
  }
  if (name.find("broken") != static_cast<size_t>(-1)) {
    throw InspectionError("вещь неисправна");
  }
  if (score < 1 || score > 10) {
    throw SimplicityError();
  }
  if (energy < 0) {
    throw EnergyError();
  }
  std::shared_ptr<scooter> obj =
      std::make_shared<scooter>(id, name, energy, score);
  storage.Inventory.add(obj);
  if (score > 5) {
    storage.For_New.add(obj);
  }
  storage.EnergyConsumers.add(obj);
}

void add_kick_scooter(Storage& storage) {
  long long id(0);
  std::string name;
  long long score(0);
  std::cin >> id >> name >> score;
  if (!std::cin) {
    throw std::invalid_argument("неправильный ввод");
  }
  if (name.find("broken") != static_cast<size_t>(-1)) {
    throw InspectionError("вещь неисправна");
  }
  if (score < 1 || score > 10) {
    throw SimplicityError();
  }
  std::shared_ptr<kick_scooter> obj =
      std::make_shared<kick_scooter>(id, name, score);
  storage.Inventory.add(obj);
  if (score > 5) {
    storage.For_New.add(obj);
  }
}

void add_helmet(Storage& storage) {
  long long id(0);
  std::string name;
  std::cin >> id >> name;
  if (!std::cin) {
    throw std::invalid_argument("неправильный ввод");
  }
  if (name.find("broken") != static_cast<size_t>(-1)) {
    throw InspectionError("вещь неисправна");
  }
  std::shared_ptr<helmet> obj = std::make_shared<helmet>(id, name);
  storage.Inventory.add(obj);
}

void add_dock_station(Storage& storage) {
  long long id(0);
  std::string name;
  long long energy(0);
  std::cin >> id >> name >> energy;
  if (!std::cin) {
    throw std::invalid_argument("неправильный ввод");
  }
  if (name.find("broken") != static_cast<size_t>(-1)) {
    throw InspectionError("вещь неисправна");
  }
  if (energy < 0) {
    throw EnergyError();
  }
  std::shared_ptr<dock_station> obj =
      std::make_shared<dock_station>(id, name, energy);
  storage.Inventory.add(obj);
  storage.EnergyConsumers.add(obj);
}

void energy(Storage& storage) {
  long long total_energy(0);
  for (auto& e : storage.EnergyConsumers) {
    total_energy += e->GetEnergy();
  }
  std::cout << "всего энергии: " << total_energy << '\n';
}

void novice(Storage& storage) {
  std::cout << "список устройств для новичков:\n" << storage.For_New;
}
void list(Storage& storage) {
  std::cout << "список всех предметов\n" << storage.Inventory;
}
void focus(Storage& storage) {
  long long id(0);
  std::cin >> id;
  if (!std::cin) {
    throw std::invalid_argument("неправильный ввод");
  }
  for (auto& e : storage.Inventory) {
    if (e->GetId() == id) {
      storage.focused = e;
      return;
    }
  }
  std::cout << "вещь не найдена\n";
}
void show_focus(Storage& storage) {
  if (auto obj = storage.focused.lock()) {
    obj->describe();
  } else {
    std::cout << "витрина пуста\n";
  }
}
void erase(Storage& storage) {
  long long id(0);
  std::cin >> id;
  if (!std::cin) {
    throw std::invalid_argument("неправильный ввод");
  }
  storage.EnergyConsumers.erase(id);
  storage.For_New.erase(id);
  if (storage.Inventory.erase(id)) {
    std::cout << "объект успешно удален\n";
    return;
  }
  std::cout << "объект не найден\n";
}
void count_novice(Storage& storage) {
  std::cout << storage.For_New.size() << '\n';
}

int main() {
  Storage storage;

  std::string cmd;
  std::map<std::string, void (*)(Storage&)> commands = {
      {"add", add},       {"energy", energy},
      {"novice", novice}, {"list", list},
      {"focus", focus},   {"show", show_focus},
      {"remove", erase},  {"count_novice", count_novice}};
  while (true) {
    std::cin >> cmd;
    if (cmd == "quit") {
      return 0;
    }
    auto it = commands.find(cmd);
    try {
      if (it == commands.end()) {
        throw GibberishError();
      }
      it->second(storage);
    } catch (std::exception& e) {
      std::cout << e.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } catch (...) {
      std::cout << "неправильный ввод" << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}