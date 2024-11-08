#include "value_implementation_nlohmannjson.hpp"

namespace jsn
{
   nlohmann::json& value::implementation::get_native_value()
   {
      if (std::holds_alternative<nlohmann::json>(native_value))
         return std::get<nlohmann::json>(native_value);

      return *std::get<nlohmann::json*>(native_value);
   }
}