// Copyright 2018 Your Name <your_email>

#include <array>
#include <cstdlib>
#include <header.hpp>
#include "exception"
#include "string"

Json::Json(const std::string &s) {
  size_t i = 0;
  while (s[i] == ' ' || s[i] == '\n') i++;
  if (s[i] != '{' && s[i] != '[') {
    throw std::logic_error("Начало другое, нет {");
  } else {
    if (s[i] == '{') {
      i++;
      for (; i < s.size(); i++) {
        //  if (s[i] != ' ') {
        while (s[i] == ' ' || s[i] == '\n') i++;
        if (s[i] != '"' && s[i] != '\\')
          throw std::logic_error("Нет кавычек в начале строки");
        else {
          if (s[i] == '\\') i++;  // key
          i++;
          std::string key = "";
          while (s[i] != '"' && s[i] != '\\') {
            key += s[i];
            i++;
          }
          if (s[i] != '"' && s[i] != '\\') {
            throw std::logic_error("нет кавычки, искл 3");
          } else {
            if (s[i] == '\\') i++;
            i++;
            std::any val;
            while (s[i] == ' ' || s[i] == '\n') i++;
            if (s[i] != ':') {
              throw std::logic_error("искл 4 нет двоеточия ");
            } else {
              i++;
              while (s[i] == ' ' || s[i] == '\n') i++;
              if (s[i] == '{') {
                std::string temp = "";
                while (s[i] != '}') {
                  temp += s[i];
                  i++;
                }
                temp += '}';
                Json te(temp);
                i++;
                val = te;
              }
              if (s[i] == '[') {
                std::string tem;
                while (s[i] != ']') {
                  tem += s[i];
                  i++;
                }
                tem += ']';
                i++;
                Json l(tem);
                val = l;
              }
              /*  std::vector<std::any> vector;
                i++;
                while(s[i] == ' '|| s[i] == '\n') i ++;
                while (s[i] != ']') {
                    if (s[i] == ',') i++;
                    if (s[i] == '"') {
                        std::string tem;
                        i++;
                        while (s[i] != '"') {
                            tem += s[i];
                            i++;
                        }
                        vector.push_back(tem);
                        i++;
                    }
                    if (s[i] == '-' || (s[i] >= '0' && s[i] <= '9')) {
                        std::string t;
                        t += s[i];
                        i++;
                        bool point = true;
                        while ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') {
                            if (s[i] == '.') {
                                if (point) {
                                    point = false;
                                    t += s[i];
                                } else { throw std::logic_error("искл 5, в
            числах лишняя точка "); } } else { t += s[i];
                            }
                            i++;
                        }
                        vector.push_back(std::atof(t.c_str()));

                    }

                    while(s[i] == ' '|| s[i] == '\n') i ++;
                    if (s[i] != ',' && s[i] != ']')
                        throw std::logic_error("искл 6 замятая или скобочка
            массива  ");
                }

                val = vector;
                i++;

            }*/
              if (s[i] == '"') {
                std::string tem;
                i++;
                while (s[i] != '"') {
                  tem += s[i];
                  i++;
                }
                val = tem;
                i++;
              }
              if (s[i] == '-' || (s[i] >= '0' && s[i] <= '9')) {
                std::string t;
                t += s[i];
                i++;
                bool point = true;
                while ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') {
                  if (s[i] == '.') {
                    if (point) {
                      point = false;
                      t += s[i];
                    } else {
                      throw std::logic_error("искл 7 лишняя точка ");
                    }
                  } else {
                    t += s[i];
                  }
                  i++;
                }
                if (point) {
                  val = atoi(t.c_str());
                } else {
                  val = atof(t.c_str());
                }
              }
              if (s[i] == 't') {
                std::string vr2;
                for (size_t j = 0; j < 4; j++, i++) vr2 += s[i];
                if (vr2 == "true") val = true;
                // i++;
              }
              if (s[i] == 'f') {
                std::string vr1;
                for (size_t j = 0; j < 5; j++, i++) vr1 += s[i];
                if (vr1 == "false") val = false;
                //   i++;
              }
              if (s[i] == 'n') {
                std::string vr;
                for (size_t j = 0; j < 4; j++, i++) vr += s[i];
                if (vr == "null") val = NULL;
                // i++;
              }
              map[key] = val;
            }
          }
        }
        while (s[i] == ' ' || s[i] == '\n') i++;
        if (s[i] == '}') return;
        if (s[i] != ',') throw std::logic_error("искл 9 нет запятой");
        i++;
        while (s[i] == ' ' || s[i] == '\n') i++;
        if (s[i] == '}') return;
        i--;
      }

      throw std::logic_error("искл 10 скобки нет }");
    } else {
      i++;
      while (s[i] == ' ') i++;
      while (s[i] != ']') {
        if (s[i] == ',') i++;
        while (s[i] == ' ' || s[i] == '\n') i++;
        if (s[i] == '"') {
          std::string tem;
          i++;
          while (s[i] != '"') {
            tem += s[i];
            i++;
          }
          vec.push_back(tem);
          i++;
        }
        if (s[i] == 't') {
          std::string vr2;
          for (size_t j = 0; j < 4; j++, i++) vr2 += s[i];
          if (vr2 == "true") vec.push_back(true);
          // i++;
        }
        if (s[i] == 'f') {
          std::string vr1;
          for (size_t j = 0; j < 5; j++, i++) vr1 += s[i];
          if (vr1 == "false") vec.push_back(false);
          //   i++;
        }
        if (s[i] == 'n') {
          std::string vr;
          for (size_t j = 0; j < 4; j++, i++) vr += s[i];
          if (vr == "null") vec.push_back(NULL);
          // i++;
        }
        if (s[i] == '-' || (s[i] >= '0' && s[i] <= '9')) {
          std::string t;
          t += s[i];
          i++;
          bool point = true;
          while ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') {
            if (s[i] == '.') {
              if (point) {
                point = false;
                t += s[i];
              } else {
                throw std::logic_error("искл 5, в числах лишняя точк 22 а");
              }
            } else {
              t += s[i];
            }
            i++;
          }
          vec.push_back(std::atof(t.c_str()));
        }
        if (s[i] == '{') {
          std::string temp = "";
          while (s[i] != '}') {
            temp += s[i];
            i++;
          }
          temp += '}';
          Json te(temp);
          i++;
          vec.push_back(te);
        }

        while (s[i] == ' ' || s[i] == '\n') i++;
        if (s[i] != ',' && s[i] != ']')
          throw std::logic_error("искл 6 замятая или скобочка массива 22");
        if (s[i] == ',' && s[i + 1] == ']') i++;
      }
    }
  }
}

bool Json::is_array() const {
  if (vec.empty()) return false;
  return true;
}

bool Json::is_object() const {
  if (vec.empty()) return true;
  return false;
}

std::any &Json::operator[](int index) {
  if (!is_array()) throw std::logic_error("Не массив");
  return vec[index];
}

std::any &Json::operator[](const std::string &key) {
  if (is_array()) throw std::exception();
  return map[key];
}

Json ticker(std::string &s) {
  size_t i = 0;
  while (s[i] == ' ' || s[i] == '\n') i++;
  if (s[i] != '[') throw std::logic_error("№3! нет скобки");
  i++;
  while (s[i] == ' ' || s[i] == '\n') i++;
  if (s[i] != '[') throw std::logic_error("№3! нет1 скобки 1 мас");
  i++;
  std::string temp;
  std::vector<std::string> vticker, vid, vdescription;
  while (s[i] != ']') {
    if (s[i] == ',') i++;
    while (s[i] == ' ' || s[i] == '\n') i++;
    if (s[i] != '"' && s[i] != '\\') throw std::logic_error("№3! нет кавычки");
    if (s[i] == '\\') i++;
    i++;
    temp += '"';
    while (s[i] != '"') {
      temp += s[i];
      i++;
    }
    temp += '"';
    vticker.push_back(temp);
    temp.clear();
    // if (s[i] == '\\')i++;
    i++;
    while (s[i] == ' ' || s[i] == '\n') i++;

    if (s[i] != ',' && s[i] != ']') throw std::logic_error("ном3 запятая");
  }
  i++;
  if (s[i] == ',') i++;
  while (s[i] == ' ' || s[i] == '\n') i++;

  while (s[i] != ']') {
    i++;
    if (s[i] == ',') i++;
    while (s[i] == ' ' || s[i] == '\n') i++;
    while ((s[i] >= '0' && s[i] <= '9')) {
      temp += s[i];
      i++;
    }
    vid.push_back(temp);
    temp.clear();
    while (s[i] == ' ' || s[i] == '\n') i++;

    if (s[i] != ',' && s[i] != ']') throw std::logic_error("ном3 cjs запятая");
  }

  i++;
  if (s[i] == ',') i++;
  while (s[i] == ' ' || s[i] == '\n') i++;

  while (s[i] != ']') {
    i++;
    if (s[i] == ',') i++;
    while (s[i] == ' ' || s[i] == '\n') i++;
    if (s[i] != '"' && s[i] != '\\') throw std::logic_error("№3! нет кавычки");
    if (s[i] == '\\') i++;
    i++;
    temp += '"';
    while (s[i] != '"') {
      temp += s[i];
      i++;
    }
    temp += '"';
    vdescription.push_back(temp);
    temp.clear();
    // if (s[i] == '\\')i++;
    i++;
    while (s[i] == ' ' || s[i] == '\n') i++;

    if (s[i] != ',' && s[i] != ']') throw std::logic_error("ном3 запятая");
  }
  i++;
  if (s[i] == ',') i++;
  while (s[i] == ' ' || s[i] == '\n') i++;
  if (s[i] != ']') throw std::logic_error("ном3 скобка вкцн");

  temp += '[';
  for (size_t k = 0; k < vid.size(); k++) {
    temp += "{\"ticker\":";
    temp += vticker[k];
    temp += ", \"id\":";
    temp += vid[k];
    temp += ", \"description\":";
    temp += vdescription[k];
    temp += "},";
  }
  temp += ']';

  Json j(temp);
  return j;
}
