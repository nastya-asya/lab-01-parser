// Copyright 2020 Anastasiya Smirnova nastya.asya08@yandex.ru

#include <gtest/gtest.h>

#include <header.hpp>
#include <sstream>
std::string getFullPath(const std::string& name) {
  std::string s(__FILE__);
  for (size_t i = 0; i < 8; ++i) {
    s.pop_back();
  }
  return s + name;
}
TEST(Parser, Empty_path) { ASSERT_THROW(Parser(""), std::invalid_argument); }
TEST(Parser, Opening_file) {
  ASSERT_THROW(Parser("my_jso.json"), std::runtime_error);
}
TEST(Parser, Empty_json) {
  ASSERT_THROW(Parser(R"({})"), std::invalid_argument);
}
TEST(Parser, Empty_file) {
  Parser pars(getFullPath("example_json.json"));
  std::stringstream str;
  str << pars;
  std::string str_example(R"(| name        | group  | avg  | debt         |
|-------------|--------|------|--------------|
| Petrov Petr | IU8-33 | null | C++          |
|-------------|--------|------|--------------|
)");
  std::vector<size_t> column_width{13, 9, 7, 15};
  std::vector<std::string> column_name{"name", "group", "avg", "debt"};
  ASSERT_EQ(str.str(), str_example);
}
TEST(Parser, Correct_array) {
  ASSERT_THROW(Parser(R"({"items": 0})"), std::invalid_argument);
}
TEST(Parser, Count_items) {
  ASSERT_THROW(Parser(R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    }
  ],
  "_meta": {
    "count": 3
  }
})"),
               std::out_of_range);
}
TEST(Parser, correct_output) {
  Parser pars(getFullPath("my_json.json"));
  std::stringstream str;
  str << pars;
  std::string str_example(R"(| name          | group  | avg  | debt         |
|---------------|--------|------|--------------|
| Ivanov Petr   | 1      | 4.25 | null         |
|---------------|--------|------|--------------|
| Sidorov Ivan  | 31     | 4    | C++          |
|---------------|--------|------|--------------|
| Pertov Nikita | IU8-31 | 3.33 | 3 items      |
|---------------|--------|------|--------------|
)");
  ASSERT_EQ(str.str(), str_example);
}
TEST(Student, Empty_student) {
  ASSERT_THROW(Student(json::parse(R"({})")), std::invalid_argument);
}
TEST(Student, correct_out_name) {
  ASSERT_THROW(Student(json::parse(R"({
      "name": [],
      "group": "1",
      "avg": "4.25",
      "debt": null
})")),
               std::invalid_argument);
}
TEST(Student, correct_out_group) {
  ASSERT_THROW(Student(json::parse(R"({
      "name": "Sidorov Ivan",
      "group": [],
      "avg": 4,
      "debt": "C++"
})")),
               std::invalid_argument);
}
TEST(Student, correct_out_avg) {
  ASSERT_THROW(Student st(json::parse(R"({
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": [],
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
})")),
               std::invalid_argument);
}
TEST(Student, correct_out_debt) {
  ASSERT_THROW(Student st(json::parse(R"({
      "name": "Petrov Petr",
      "group": 33,
      "avg": null,
      "debt": 0
})")),
               std::invalid_argument);
}
