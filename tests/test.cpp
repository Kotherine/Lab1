#include <gtest/gtest.h>
#include "student.hpp"

const std::string &jsonPath = "/home/ekaterina/lab1/lab-01-parser/students.json";

TEST(ParserTest, EmptyPath) {
  EXPECT_FALSE(jsonPath.empty());
}
TEST(ParserTest, FileExists) {
  std::ifstream file{jsonPath};
  EXPECT_FALSE(!file);
}
TEST(ParserTest, ItemsInArray) {
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  EXPECT_TRUE( data.at("items").is_array());
}
TEST(ParserTest, TrueCount) {
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  EXPECT_EQ(data.at("items").size(), data.at("_meta").at("count").get<size_t>());
}

TEST(ParserTest, TypeGroup) {
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<student_t> students;
  for (auto const& item : data.at("items")) {
    auto student = item.get<student_t>();
    students.push_back(student);
  }
  for (auto const& student : students) {
    bool res = false;
    if (student.group.type() == typeid(std::string)) {
      res = true;
    } else if (student.group.type() == typeid(size_t)) {
      res  = true;
    }
    EXPECT_TRUE( res);
  }
}

TEST(ParserTest, TypeAvg) {
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<student_t> students;
  for (auto const& item : data.at("items")) {
    auto student = item.get<student_t>();
    students.push_back(student);
  }
  for (auto const& student : students) {
    bool res = false;
    if (student.avg.type() == typeid(std::nullptr_t)) {
      res = true;
    } else if (student.avg.type() == typeid(std::string)) {
      res = true;
    } else if (student.avg.type() == typeid(double)) {
      res = true;
    } else if(student.avg.type() == typeid(size_t)){
      res = true;
    }
    EXPECT_TRUE( res);
  }
}

TEST(ParserTest, TypeDebt) {
  std::ifstream file{jsonPath};
  json data;
  file >> data;
  std::vector<student_t> students;
  for (auto const& item : data.at("items")) {
    auto student = item.get<student_t>();
    students.push_back(student);
  }
  for (auto const& student : students) {
    bool res = false;
    if (student.debt.type() == typeid(std::nullptr_t)) {
      res = true;
    } else if (student.debt.type() == typeid(std::string)) {
      res = true;
    } else if(student.debt.type() == typeid(std::vector<std::string>)){
      res = true;
    }
    EXPECT_TRUE( res);
  }
}