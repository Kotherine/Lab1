#include "student.hpp"

auto get_name(const json& j) -> std::string {
  return j.get<std::string>();
}

auto get_debt(const json& j) -> std::any {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<std::vector<std::string> >();
}

auto get_avg(const json& j) -> std::any {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<std::string>();
  else if (j.is_number_float())
    return j.get<double>();
  else
    return j.get<std::size_t>();
}

auto get_group(const json& j) -> std::any {
  if (j.is_string())
    return  j.get<std::string>();
  else
    return j.get<std::size_t>();
}

void from_json(const json& j, student_t& s) {
  s.name = get_name(j.at("name"));
  s.group = get_group(j.at("group"));
  s.avg = get_avg(j.at("avg"));
  s.debt = get_debt(j.at("debt"));
}

std::string cut(std::string str){
  for(int i = str.length()-1; i>0; i-=1){
    if(str[i] == '0')  str.erase(i, 1);
  }
  return str;
}

unsigned len_name(const student_t& student){
  return student.name.length();
}

unsigned max_len_name(const std::vector<student_t>& students){ // максимальная длина ячейки с именем
  unsigned l = 0;
  for (auto const& student : students) {
    l = fmax(l, len_name(student));
  }
  l += 2;
  return l;
}

unsigned len_group(const student_t& student){
  std::string str;
  if (student.group.type() == typeid(std::string)) {
    str = std::any_cast<std::string>(student.group);
  } else {
    str = std::to_string(std::any_cast<std::size_t>(student.group));
  }
  return str.length();
}

unsigned max_len_group(const std::vector<student_t>& students){ // максимальная длина ячейки с группой
  unsigned l = 0;
  for (auto const& student : students) {
    l = fmax(l, len_group(student));
  }
  l += 2;
  return l;
}

unsigned len_avg(const student_t& student){
  std::string str;
  if (student.avg.type() == typeid(std::nullptr_t)) { //тип среднего балла
    str = "null";
  } else if (student.avg.type() == typeid(std::string)) {
    str = std::any_cast<std::string>(student.avg);
  } else if (student.avg.type() == typeid(double)) {
    str = cut(std::to_string(std::any_cast<double>(student.avg)));
  } else {
    str = std::to_string(std::any_cast<std::size_t>(student.avg));
  }
  return str.length();
}

unsigned max_len_avg(const std::vector<student_t>& students){ // максимальная длина ячейки со средним баллом
  unsigned l = 0;
  for (auto const& student : students) {
    l = fmax(l, len_avg(student));
  }
  l += 2;
  return l;
}

unsigned len_debt(const student_t& student){
  std::string str;
  if (student.debt.type() == typeid(std::nullptr_t)) { //тип задолженности
    str = "null";
  } else if (student.debt.type() == typeid(std::string)) {
    str = std::any_cast<std::string>(student.debt);
  } else {
    str = std::to_string(std::any_cast<std::vector<std::string>>(student.debt).size()) + " items";
  }
  return str.length();
}

unsigned max_len_debt(const std::vector<student_t>& students){ // максимальная длина ячейки с задолженностями
  unsigned l = 0;
  for (auto const& student : students) {
    l = fmax(l, len_debt(student));
  }
  l += 2;
  return l;
}

std::string delimiter(unsigned l){
  std::string str = "";
  for(unsigned i = 0; i<l; i++) {
    str += "-";
  }
  return str;
}

std::string border(unsigned len_name, unsigned len_group, unsigned len_avg, unsigned len_debt){
  return "|" + delimiter(len_name) + "|" + delimiter(len_group) + "|" + delimiter(len_avg) + "|" + delimiter(len_debt) + "|\n";
}

std::string cell(unsigned l) {
  std::string str = "";
  for (unsigned i = 0; i < l; i++) {
    str += " ";
  }
  return str;
}

void head(unsigned len_name, unsigned len_group, unsigned len_avg, unsigned len_debt, std::ostream& os){
  os << "|" << "name" << cell(len_name - strlen("name")) << "|";
  os << "group" << cell(len_group - strlen("group")) << "|";
  os << "avg" << cell(len_avg - strlen("avg")) << "|";
  os << "debt" << cell(len_debt - strlen("debt")) << "|\n";
}

void print(const std::vector<student_t>& students, std::ostream& os){
  unsigned len_name = max_len_name(students);
  unsigned len_group = max_len_group(students);
  unsigned len_avg = max_len_avg(students);
  unsigned len_debt = max_len_debt(students);
  head(len_name, len_group, len_avg, len_debt, os);
  os << border(len_name, len_group, len_avg, len_debt);
  for (auto const& student : students) {
    print(student, os, len_name, len_group, len_avg, len_debt);
    os << border(len_name, len_group, len_avg, len_debt);
  }
}

void print(const student_t& student, std::ostream& os, unsigned name, unsigned group, unsigned avg, unsigned debt) {

  os << "|" << student.name << cell(name - len_name(student)) << "|"; // вывод имени

  if (student.group.type() == typeid(std::string)) { // вывод группы
    os << std::any_cast<std::string>(student.group);
  } else {
    os
        << std::any_cast<std::size_t>(student.group);
  }
  os << cell(group-len_group(student)) << "|";

  if (student.avg.type() == typeid(std::nullptr_t)) { //вывод среднего балла
    os << "null";
  } else if (student.avg.type() == typeid(std::string)) {
    os << std::any_cast<std::string>(student.avg);
  } else if (student.avg.type() == typeid(double)) {
    os << std::any_cast<double>(student.avg);
  } else {
    os
        << std::any_cast<std::size_t>(student.avg);
  }
  os << cell(avg - len_avg(student)) << "|";

  if (student.debt.type() == typeid(std::nullptr_t)) { //вывод задолженности
    os << "null";
  } else if (student.debt.type() == typeid(std::string)) {
    os << std::any_cast<std::string>(student.debt);
  } else {
    os
        << std::any_cast<std::vector<std::string> >(student.debt).size()
        << " items";
  }
  os << cell(debt- len_debt(student)) << "|\n";
}
