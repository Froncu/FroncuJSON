#include "implementation/value_implementation_nlohmannjson.hpp"

#include <format>
#include <fstream>

namespace fro
{
   nlohmann::json parse(std::string_view const json_path)
   {
      if (std::ifstream input{ json_path.data() }; input.is_open())
         return nlohmann::json::parse(input);

      throw std::runtime_error(std::format("failed to open \"{}\"\n", json_path));
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
      for (auto const& [child_key, _] : implementation_->get_native_value().items())
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
      return implementation_->get_native_value().get<int>();
   }

   float value::as_float() const
   {
      return implementation_->get_native_value().get<float>();
   }

   double value::as_double() const
   {
      return implementation_->get_native_value().get<double>();
   }

   bool value::as_bool() const
   {
      return implementation_->get_native_value().get<bool>();
   }

   std::string_view value::as_string_view() const
   {
      return implementation_->get_native_value().get<std::string_view>();
   }

   std::string value::as_string() const
   {
      return as_string_view().data();
   }

   std::vector<value> value::construct_children() const
   {
      nlohmann::json& value{ implementation_->get_native_value() };

      // NOTE: nlohmann::json::size() returns 0 only if the value of the key is not set.
      if (not value.is_array()
         and not value.is_object()
         and value.size() == 1)
         return {};

      std::vector<fro::value> children;
      children.reserve(value.size());

      for (nlohmann::json& native_child : value)
      {
         // NOTE: explicitly not using emplace_back; that would force the interface to make
         // the constructor that takes a std::unique_ptr<implementation> to be public,
         // what I don't want.

         fro::value child{ std::make_unique<implementation>(&native_child) };
         children.push_back(std::move(child));
      }

      return children;
   }
}