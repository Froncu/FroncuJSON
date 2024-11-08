#include "value_implementation_jsoncpp.hpp"

namespace jsn
{
   Json::Value& value::implementation::get_native_value()
   {
      if (std::holds_alternative<Json::Value>(native_value))
         return std::get<Json::Value>(native_value);

      return *std::get<Json::Value*>(native_value);
   }
}