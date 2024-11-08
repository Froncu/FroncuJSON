include(FetchContent)

fetchcontent_declare(nlohmannjson
   GIT_REPOSITORY https://github.com/nlohmann/json
   GIT_TAG v3.11.3)
fetchcontent_makeavailable(nlohmannjson)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

target_sources(${PROJECT_NAME} PRIVATE
   source/value_nlohmannjson.cpp
   source/implementation/value_implementation_nlohmannjson.cpp)