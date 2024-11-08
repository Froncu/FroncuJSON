include(FetchContent)

set(JSONCPP_WITH_TESTS OFF)
set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF)
set(JSONCPP_WITH_EXAMPLE OFF)
set(BUILD_OBJECT_LIBS OFF)
set(BUILD_SHARED_LIBS OFF)
set(BUILD_STATIC_LIBS ON)

fetchcontent_declare(jsoncpp
   GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp
   GIT_TAG 1.9.6)
fetchcontent_makeavailable(jsoncpp)

target_link_libraries(${PROJECT_NAME} PRIVATE jsoncpp_static)

target_sources(${PROJECT_NAME} PRIVATE
   source/value_jsoncpp.cpp
   source/implementation/value_implementation_jsoncpp.cpp)