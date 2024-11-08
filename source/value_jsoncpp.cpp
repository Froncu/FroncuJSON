#include "implementation/value_implementation_jsoncpp.hpp"

#include <format>
#include <fstream>

namespace fro
{
   Json::Value parse(std::string_view const json_path)
   {
      Json::Value value;
      if (std::ifstream input{ json_path.data() }; input.is_open())
      {
         Json::CharReaderBuilder parser{};
         parser.settings_["rejectDupKeys"] = true;
         if (std::string errors; not parseFromStream(parser, input, &value, &errors))
            throw std::runtime_error(std::format("parsing failed; {}\n", errors));
      } else
         throw std::runtime_error(std::format("failed to open \"{}\"\n", json_path));

      return value;
   }

   value::value(std::string_view const json_path)
      : implementation_{ std::make_unique<implementation>(parse(json_path)) }
      , children_{ construct_children() }
   {
   }

   value::value(std::unique_ptr<implementation> implementation)
      : implementation_{ std::move(implementation) }
      , children_{ construct_children() }
   {
   }

   value::~value() = default;

   // TODO: not ideal to loop over all the member names
   value const& value::operator[](std::string_view const key) const
   {
      std::size_t index{};
      for (std::string_view const child_key : implementation_->get_native_value().getMemberNames())
      {
         if (child_key == key)
            return children_[index];
         ++index;
      }

      throw std::runtime_error("key not found");
   }

   value const& value::operator[](std::size_t const index) const
   {
      return children_[index];
   }

   value const& value::front() const
   {
      return children_.front();
   }

   value const& value::back() const
   {
      return children_.back();
   }

   std::ostream& operator<<(std::ostream& output_stream, const value& value)
   {
      return output_stream << value.implementation_->get_native_value();
   }

   std::vector<value>::const_iterator value::begin() const
   {
      return children_.cbegin();
   }

   std::vector<value>::const_iterator value::end() const
   {
      return children_.cend();
   }

   std::size_t value::size() const
   {
      return children_.size();
   }

   int value::as_int() const
   {
      return implementation_->get_native_value().asInt();
   }

   float value::as_float() const
   {
      return implementation_->get_native_value().asFloat();
   }

   double value::as_double() const
   {
      return implementation_->get_native_value().asDouble();
   }

   bool value::as_bool() const
   {
      // NOTE: nlohmann throws an exception when the value retrieved as bool is not a bool
      Json::Value const& value{ implementation_->get_native_value() };
      if (not value.isBool())
         throw std::runtime_error("value requested as bool, but is of a different type.");

      return implementation_->get_native_value().asBool();
   }

   std::string_view value::as_string_view() const
   {
      return implementation_->get_native_value().asCString();
   }

   std::string value::as_string() const
   {
      return as_string_view().data();
   }

   std::vector<value> value::construct_children() const
   {
      Json::Value& value{ implementation_->get_native_value() };

      // NOTE: the for loop below will not be entered if value empty;
      // this is here to prevent the unnecessary creation of members.
      if (value.empty())
         return {};

      std::vector<fro::value> children;
      children.reserve(value.size());

      for (Json::Value& native_child : value)
      {
         // NOTE: explicitly not using emplace_back; that would force the interface to make
         // the constructor that takes a std::unique_ptr<implementation> to be public,
         // what I don't want.

         fro::value member{ std::make_unique<implementation>(&native_child) };
         children.push_back(std::move(member));
      }

      return children;
   }
}