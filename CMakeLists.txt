cmake_minimum_required(VERSION 3.18)
project(CityBuilder)


set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_PROFILING "Enable Tracy Profiling" OFF)

enable_testing()

if(ENABLE_PROFILING)
  find_package(Tracy CONFIG REQUIRED)
endif(ENABLE_PROFILING)
find_package(GTest CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

add_subdirectory(core/)
add_subdirectory(api/)

add_executable(main main.cc)



target_link_libraries(main PRIVATE core api sfml-system sfml-network sfml-graphics sfml-window sfml-audio)

set(RESOURCE_FILES ressources/*.ttf)
file(COPY ${CMAKE_SOURCE_DIR}/ressources DESTINATION ${CMAKE_BINARY_DIR})

