#include <iostream>
#include <memory>
#include <string>
#pragma once
class InventoryItem {
 protected:
  std::unique_ptr<long long> id;
  std::shared_ptr<std::string> name;

 public:
  bool operator<(InventoryItem& a) { return *id < *a.id; }
  bool operator==(InventoryItem& a) { return *id == *a.id; }
  friend std::ostream& operator<<(std::ostream& stream, InventoryItem& a) {
    return stream << *a.id << ' ' << *a.name;
  }
  virtual ~InventoryItem() = default;

  long long virtual inventoryid() = 0;

  std::string virtual title() = 0;

  void virtual describe() = 0;

  long long GetId() { return *id; }
};

class EnergyConsumer : public virtual InventoryItem {
 protected:
  std::unique_ptr<long long> energy;

 public:
  virtual ~EnergyConsumer() = default;

  long long virtual dailyEnergy() = 0;
  long long GetEnergy() { return *energy; }
};

class ScoreItem : public virtual InventoryItem {
 protected:
  std::unique_ptr<long long> score;

 public:
  virtual ~ScoreItem() = default;
};