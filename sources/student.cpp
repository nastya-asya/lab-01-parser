// Copyright 2020 Anastasiya Smirnova nastya.asya08@yandex.ru

#include "student.hpp"

using nlohmann::json;

Student::Student(const json& js) {
  if (js.empty()) {
    throw std::invalid_argument("json empty!");
  }
  if (js.at("name").is_string()) {
    Name = js.at("name").get<std::string>();
  } else {
    throw std::invalid_argument("name is not correct");
  }
  if (js.at("group").is_string()) {
    Group = js.at("group").get<std::string>();
  } else if (js.at("group").is_number_unsigned()) {
    Group = js.at("group").get<size_t>();
  } else {
    throw std::invalid_argument("group is not correct");
  }
  if (js.at("avg").is_null()) {
    Avg = nullptr;
  } else if (js.at("avg").is_string()) {
    Avg = js.at("avg").get<std::string>();
  } else if (js.at("avg").is_number_float()) {
    Avg = js.at("avg").get<double>();
  } else if (js.at("avg").is_number_unsigned()) {
    Avg = js.at("avg").get<size_t>();
  } else {
    throw std::invalid_argument("avg is not correct");
  }
  if (js.at("debt").is_null()) {
    Debt = nullptr;
  } else if (js.at("debt").is_string()) {
    Debt = js.at("debt").get<std::string>();
  } else if (js.at("debt").is_array()) {
    Debt = js.at("debt").get<std::vector<std::string>>();
  } else {
    throw std::invalid_argument("debt is not correct");
  }
}
const std::string& Student::getName() const { return Name; }
const std::any& Student::getGroup() const { return Group; }
const std::any& Student::getAvg() const { return Avg; }
const std::any& Student::getDebt() const { return Debt; }
