#include <student.hpp>
#include "iostream"
#include "gtest/gtest.h"

int main() {
  const std::string &jsonPath =
      "/home/ekaterina/lab1/lab-01-parser/students.json";
  if (jsonPath.empty()) throw std::runtime_error{"Empty file path!"};

  std::ifstream file{jsonPath};
  if (!file) throw std::runtime_error{"Unable to open json: " + jsonPath};

  json data;
  file >> data;
  if (!data.at("items").is_array())
    throw std::runtime_error{"The items in the file must be an array!"};
  if (data.at("items").size() !=
      data.at("_meta").at("count").get<size_t>())
    throw std::runtime_error{"Value in _meta not equal to length of the array"};

  std::vector<student_t> students;

  for (auto const& item : data.at("items")) {
    auto student = item.get<student_t>();
    students.push_back(student);
  }
  print(students, std::cout);
  return 0;
}

// Created by ekaterina on 20.09.2021.