// Copyright 2020 Anastasiya Smirnova nastya.asya08@yandex.ru

#include "header.hpp"

Parser::Parser(const std::string& jsonPath) {
  json data;
  if (jsonPath[0] != '{') {
    if (jsonPath.empty()) {
      throw std::invalid_argument("path is not available");
    }
    std::ifstream file(jsonPath);
    if (!file) {
      throw std::runtime_error("unable to open json: " + jsonPath);
    }
    file >> data;
  } else {
    data = json::parse(jsonPath);
  }
  if (data.empty()) {
    throw std::invalid_argument("json is empty");
  }
  if (!data.at("items").is_array()) {
    throw std::invalid_argument("json does not contain an array ");
  }
  if (data.at("items").size() != data.at("_meta").at("count")) {
    throw std::out_of_range("_meta.count != len(items)");
  }
  for (auto const& student : data.at("items")) {
    students.push_back(Student(student));
  }
  for (auto const& student : students) {
    if (student.getName().size() + 3 > column_width[0]) {
      column_width[0] = student.getName().size() + 3;
    }
  }
}
void Parser::Print_columns(std::ostream& out) const {
  out << std::setfill(' ') << std::left << std::setw(column_width[0])
      << "| name" << std::setw(column_width[1]) << "| group"
      << std::setw(column_width[2]) << "| avg" << std::setw(column_width[3])
      << "| debt" << '|' << std::endl;
}
void Parser::Print_lines(std::ostream& out) const {
  for (size_t i = 0; i < 4; ++i) {
    out << std::setfill('-') << std::setw(column_width[i]) << "|";
  }
  out << '|' << std::endl;
}
std::ostream& operator<<(std::ostream& out, const Parser& pars) {
  pars.Print_columns(out);
  pars.Print_lines(out);
  for (size_t i = 0; i < pars.students.size(); ++i) {
    out << std::setfill(' ') << std::setw(pars.column_width[0])
        << "| " + pars.students[i].getName();
    if (pars.students[i].getGroup().type() == typeid(std::string)) {
      out << std::setw(pars.column_width[1])
          << "| " + std::any_cast<std::string>(pars.students[i].getGroup());
    } else {
      out << "| " << std::setw(pars.column_width[1] - 2)
          << std::any_cast<size_t>(pars.students[i].getGroup());
    }
    if (pars.students[i].getAvg().type() == typeid(std::nullptr_t)) {
      out << "| " << std::setw(pars.column_width[2] - 2) << "null";
    } else if (pars.students[i].getAvg().type() == typeid(std::string)) {
      out << std::setw(pars.column_width[2])
          << "| " + std::any_cast<std::string>(pars.students[i].getAvg());
    } else if (pars.students[i].getAvg().type() == typeid(std::size_t)) {
      out << "| " << std::setw(pars.column_width[2] - 2)
          << std::any_cast<size_t>(pars.students[i].getAvg());
    } else {
      out << "| " << std::setw(pars.column_width[2] - 2)
          << std::any_cast<double>(pars.students[i].getAvg());
    }
    if (pars.students[i].getDebt().type() == typeid(std::nullptr_t)) {
      out << "| " << std::setw(pars.column_width[3] - 2) << "null";
    } else if (pars.students[i].getDebt().type() == typeid(std::string)) {
      out << std::setw(pars.column_width[3])
          << "| " + std::any_cast<std::string>(pars.students[i].getDebt());
    } else {
      out << "| "
          << std::any_cast<std::vector<std::string>>(pars.students[i].getDebt())
                 .size()
          << std::setw(pars.column_width[3] - 3) << " items";
    }
    out << '|' << std::endl;
    pars.Print_lines(out);
  }
  return out;
}
