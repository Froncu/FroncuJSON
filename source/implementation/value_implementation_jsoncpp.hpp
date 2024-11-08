#ifndef VALUE_IMPLEMENTATION_JSONCPP_HPP
#define VALUE_IMPLEMENTATION_JSONCPP_HPP

#include "FroncuJSON/value.hpp"

#include <json/json.h>

#include <variant>

namespace jsn
{
   struct value::implementation final
   {
      std::variant<Json::Value, Json::Value*> native_value;

      [[nodiscard]] Json::Value& get_native_value();
   };
}

#endif