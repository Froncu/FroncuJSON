#ifndef VALUE_HPP
#define VALUE_HPP

#include <format>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace jsn
{
   class value final
   {
      struct implementation;

      public:
         explicit value(std::string_view json_path);
         value(value const&) = delete;
         value(value&&) noexcept = default;

         ~value();

         [[nodiscard]] value& operator=(value const&) = delete;
         [[nodiscard]] value& operator=(value&&) noexcept = default;
         [[nodiscard]] value const& operator[](std::string_view key) const;
         [[nodiscard]] value const& operator[](std::size_t index) const;
         friend std::ostream& operator<<(std::ostream& output_stream, value const& value);

         [[nodiscard]] value const& front() const;
         [[nodiscard]] value const& back() const;
         [[nodiscard]] std::vector<value>::const_iterator begin() const;
         [[nodiscard]] std::vector<value>::const_iterator end() const;
         [[nodiscard]] std::size_t size() const;

         [[nodiscard]] int as_int() const;
         [[nodiscard]] std::string_view as_string_view() const;
         [[nodiscard]] std::string as_string() const;

      private:
         explicit value(std::unique_ptr<implementation> implementation);

         [[nodiscard]] std::vector<value> construct_children() const;

         std::unique_ptr<implementation> implementation_;
         std::vector<value> children_;
   };
}

template<>
struct std::formatter<jsn::value> : private std::formatter<std::string>
{
   static constexpr auto parse(std::format_parse_context const& context)
   {
      return context.begin();
   }

   auto format(jsn::value const& value, std::format_context& context) const
   {
      std::ostringstream string_stream{};
      string_stream << value;
      return std::formatter<std::string>::format(string_stream.str(), context);
   }
};

#endif