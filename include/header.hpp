// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "any"
#include "unordered_map"

class Json {
  std::unordered_map<std::string, std::any> map;
  std::vector<std::any> vec;

 public:
  // Конструктор из строки, содержащей Json-данные.
  explicit Json(const std::string &s);

  // Метод возвращает true, если данный экземпляр содержит в себе JSON-массив.
  // Иначе false.
  bool is_array() const;

  // Метод возвращает true, если данный экземпляр содержит в себе JSON-объект.
  // Иначе false.
  bool is_object() const;

  // Метод возвращает значение по ключу key, если экземпляр является
  // JSON-объектом. Значение может иметь один из следующих типов: Json,
  // std::string, double, bool или быть пустым. Если экземпляр является
  // JSON-массивом, генерируется исключение.
  std::any &operator[](const std::string &key);

  // Метод возвращает значение по индексу index, если экземпляр является
  // JSON-массивом. Значение может иметь один из следующих типов: Json,
  // std::string, double, bool или быть пустым. Если экземпляр является
  // JSON-объектом, генерируется исключение.
  std::any &operator[](int index);

  // Метод возвращает объект класса Json из строки, содержащей Json-данные.
  static Json parse(const std::string &s) {
    Json j(s);
    return j;
  }

  // Метод возвращает объекта класса Json из файла, содержащего Json-данные в
  // текстовом формате.
  static Json parseFile(const std::string &path_to_file) {
    std::string s;

    std::ifstream f(path_to_file);
    std::stringstream ss;
    ss << f.rdbuf();
    s = ss.str();

    Json j(s);
    return j;
  }
};

Json ticker(std::string &s);

#endif  // INCLUDE_HEADER_HPP_
