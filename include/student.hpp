// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <fstream>
#include <iostream>
#include <string>
#include <any>
#include <vector>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <algorithm>

using nlohmann::json;

struct Student {
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};
typedef Student student_t;

void from_json(const json& j, student_t& s);
std::string cut(std::string str);
unsigned len_name(const student_t& student);
unsigned len_group(const student_t& student);
unsigned len_avg(const student_t& student);
unsigned len_debt(const student_t& student);
unsigned max_len_name(const std::vector<student_t>& students);
unsigned max_len_group(const std::vector<student_t>& students);
unsigned max_len_avg(const std::vector<student_t>& students);
unsigned max_len_debt(const std::vector<student_t>& students);
std::string delimiter(unsigned l);
std::string border(unsigned len_name, unsigned len_group, unsigned len_avg, unsigned len_debt);
void head(unsigned len_name, unsigned len_group, unsigned len_avg, unsigned len_debt, std::ostream& os);
std::string cell(unsigned l);
void print(const std::vector<student_t>& students, std::ostream& os);
void print(const student_t& student, std::ostream& os, unsigned len_name, unsigned len_group, unsigned len_avg, unsigned len_debt);


#endif // INCLUDE_HEADER_HPP_
