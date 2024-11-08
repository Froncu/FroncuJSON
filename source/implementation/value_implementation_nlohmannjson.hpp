#ifndef VALUE_IMPLEMENTATION_NLOHMANNJSON_HPP
#define VALUE_IMPLEMENTATION_NLOHMANNJSON_HPP

#include "FroncuJSON/value.hpp"

#include <nlohmann/json.hpp>

#include <variant>

namespace jsn
{
   struct value::implementation final
   {
      std::variant<nlohmann::json, nlohmann::json*> native_value;

      [[nodiscard]] nlohmann::json& get_native_value();
   };
}

#endif