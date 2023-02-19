#include <iostream>
#include <string>

#include "state_record/deserialize/deserializer.h"
#include "state_record/parsers/json_parser.h"
#include "state_record/utils/macros.h"

// define and reflect a struct
DEFINE_SCHEMA(Point,                          // struct Point {
              (std::string) name,             //     std::string name;
              (double) x,                     //     double x;
              (double) y);                    //     double y;
                                              // };

int main() {
  Point point;
  state_record::Load2Obj<state_record::JsonParser> parser;
  auto res = parser([] {
    return R"(
      {
        "name": "One point",
        "x": 1.2,
        "y": 2.4
      }
    )";
  },
                    &point);

  std::cout << (int)res << std::endl;
  std::cout << point.name << std::endl;
  std::cout << point.x << std::endl;
  std::cout << point.y << std::endl;

  return 0;
}