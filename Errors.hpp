#include <stdexcept>
#pragma once

class SimplicityError : public std::runtime_error {
 public:
  SimplicityError() : std::runtime_error("Простота вне диапазона от 1 до 10") {}
};

class EnergyError : public std::runtime_error {
 public:
  EnergyError() : std::runtime_error("Энергия предмета инвентаря меньше 0") {}
};

class GibberishError : public std::runtime_error {
 public:
  GibberishError() : std::runtime_error("Не распознано имя команды") {}
};

class InspectionError : public std::exception {
  std::string msg;

 public:
  explicit InspectionError(std::string m) : msg(std::move(m)) {}
  const char* what() const noexcept override { return msg.c_str(); }
};