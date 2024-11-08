cmake_minimum_required(VERSION 3.20)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project(FroncuJSON)

add_library(${PROJECT_NAME} STATIC)

set_target_properties(${PROJECT_NAME} PROPERTIES
   CXX_STANDARD 20
   CXX_STANDARD_REQUIRED TRUE)

target_compile_options(${PROJECT_NAME} PRIVATE
   $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Werror>
   $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>)

target_include_directories(${PROJECT_NAME} PRIVATE source)
target_include_directories(${PROJECT_NAME} PUBLIC include)

set(FRO_NATIVE_LIBRARY "nlohmannjson" CACHE STRING "Choose which native library to use")
set(FRO_AVAILABLE_NATIVE_LIBRARIES "jsoncpp" "nlohmannjson")
set_property(CACHE FRO_NATIVE_LIBRARY PROPERTY STRINGS ${FRO_AVAILABLE_NATIVE_LIBRARIES})

if(NOT FRO_NATIVE_LIBRARY IN_LIST FRO_AVAILABLE_NATIVE_LIBRARIES)
   message(FATAL_ERROR
      "Invalid native library specified (${FRO_NATIVE_LIBRARY}); must be one of the following:
      ${FRO_AVAILABLE_NATIVE_LIBRARIES}")
endif()
include(${FRO_NATIVE_LIBRARY})