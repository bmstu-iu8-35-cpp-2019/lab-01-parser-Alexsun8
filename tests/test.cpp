// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>

#include <header.hpp>

TEST(my_error, JSON_ALL) {  //слишком длинное число int
  std::string file = "../../Json/text.json";
  std::string s =
      "{ \"lastname\" : \"Ivanov\",  \"firstname\" : \"Ivan\",  \"age\" : 25,"
      "\"islegal\" : false,  \"marks\" : [ 4,5,5,5,2,3 ], \"address\" : "
      "{\"city\" :"
      "\"Moscow\",  \"street\" : \"Vozdvijenka\" } }";

  Json object = Json::parse(s);
  Json ob2 = Json::parseFile(file);

  EXPECT_EQ(std::any_cast<std::string>(object["lastname"]), "Ivanov");
  EXPECT_EQ(std::any_cast<bool>(object["islegal"]), false);
  EXPECT_EQ(std::any_cast<int>(object["age"]), 25);

  auto marks = std::any_cast<Json>(object["marks"]);
  EXPECT_EQ(std::any_cast<double>(marks[0]), 4);
  EXPECT_EQ(std::any_cast<double>(marks[1]), 5);

  auto address = std::any_cast<Json>(object["address"]);
  EXPECT_EQ(std::any_cast<std::string>(address["city"]), "Moscow");
  EXPECT_EQ(std::any_cast<std::string>(address["street"]), "Vozdvijenka");

  EXPECT_TRUE(ob2.is_array());

  EXPECT_FALSE(ob2.is_object());

  EXPECT_FALSE(object.is_array());

  EXPECT_TRUE(object.is_object());

  EXPECT_EQ(std::any_cast<double>(ob2[0]), 1.4567);

  std::string num3 =
      "[\n"
      "    [\"Si-9.15\", \"RTS-9.15\", \"GAZP-9.15\"],\n"
      "    [100024, 100027, 100050],\n"
      "    [\"Futures contract for USD/RUB\", \"Futures contract for index "
      "RTS\", \"Futures contract"
      "for Gazprom shares\"]\n"
      "]";

  Json j = ticker(num3);
}
