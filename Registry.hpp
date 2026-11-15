#include <iostream>
#include <memory>
#include <vector>
#pragma once

template <typename T>
class Registry {
  std::vector<std::shared_ptr<T>> data;

 public:
  Registry() {}
  void add(std::shared_ptr<T> object) { data.push_back(object); }
  bool erase(long long id) {
    for (size_t i(0); i < data.size(); ++i) {
      if (data[i]->GetId() == id) {
        data.erase(data.begin() + i);
        return true;
      }
    }
    return false;
  }
  auto begin() { return data.begin(); }
  auto end() { return data.end(); }
  size_t size() const { return data.size(); }
  std::shared_ptr<T>& operator[](size_t i) { return data[i]; }
  friend std::ostream& operator<<(std::ostream& os, const Registry<T>& p) {
    for (auto& e : p.data) {
      os << *e << '\n';
    }
    return os;
  }
};
