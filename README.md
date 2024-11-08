# FroncuJSON

## Overview

**FroncuJSON** is a C++ library designed to simplify JSON file parsing and data extraction. It provides a straightforward interface for reading and processing JSON data in C++ with a single class. It relies on external libraries to handle JSON parsing and uses [pimpl](https://en.cppreference.com/w/cpp/language/pimpl), allowing developers to choose the native library based on their preference without exposing them to the used library.

## Libraries Used

- [nlohmann::json](https://github.com/nlohmann/json): A modern JSON library for C++.
- [jsoncpp](https://github.com/open-source-parsers/jsoncpp): A lightweight and fast JSON parser written in C++.

### Fetching External Libraries

FroncuJSON uses CMake's `FetchContent` module to download and manage the selected JSON library as part of the build process. When you specify the `FRO_NATIVE_LIBRARY` variable, CMake automatically fetches the appropriate dependency. There is no need to manually install or link these dependencies, as CMake handles everything required to integrate the selected JSON library with FroncuJSON.

## Configuration and Usage

### Prerequisites

- CMake 3.20 or higher
- C++20 compatible compiler

### Choosing the Native Library

You can select the JSON parsing library that FroncuJSON will use by setting the `FRO_NATIVE_LIBRARY` CMake variable:

- `FRO_NATIVE_LIBRARY=nlohmannjson` (default): Uses nlohmann::json.
- `FRO_NATIVE_LIBRARY=jsoncpp`: Uses jsoncpp.

Set this variable when configuring the project. If an invalid library is specified, CMake will raise an error and list the valid options.

### Using FroncuJSON in Your Project

1. Add FroncuJSON to your project. You can achieve this in multiple ways. In the example below, we will be using `FetchContent`:
   
   ```cmake
   include(FetchContent)
   
   fetchcontent_declare(FroncuJSON
      GIT_REPOSITORY https://github.com/Froncu/FroncuJSON
      GIT_TAG main)
   fetchcontent_makeavailable(FroncuJSON)
   ```

2. Link your executable to the library using `target_link_libraries`:
   
   ```cmake
   add_executable(${PROJECT_NAME} main.cpp)
   target_link_libraries(${PROJECT_NAME} PRIVATE FroncuJSON)
   ```

3. Use the library:
   
   ```cpp
   #include <FroncuJSON/value.hpp>
   
   #include <format>
   #include <iostream>
   
   int main()
   {
      jsn::value const root{ "./content/pokedex.json" };
   
      for (jsn::value const& pokemon : root["pokemon"])
         std::cout << std::format(
            "{}. {}\n",
            pokemon["id"],
            pokemon["name"]);
   
      return 0;
   }
   ```

The syntax is very simmilar to known JSON libraries. Take a look at `value.hpp` to find all the functionalities. For a complete example, take a look at [Pokedex](https://github.com/Froncu/Pokedex).
