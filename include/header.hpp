// Copyright 2020 Anastasiya Smirnova nastya.asya08@yandex.ru

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <string>
#include <vector>

#include "student.hpp"
using nlohmann::json;

class Parser {
 public:
  explicit Parser(const std::string& jsonPath);
  void Print_columns(std::ostream& out) const;
  void Print_lines(std::ostream& out) const;
  friend std::ostream& operator<<(std::ostream& out, const Parser& pars);

 private:
  std::vector<Student> students;
  std::vector<size_t> column_width{0, 9, 7, 15};
};

#endif // INCLUDE_HEADER_HPP_
