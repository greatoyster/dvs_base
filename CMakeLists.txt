cmake_minimum_required(VERSION 3.0.2)
project(dvs_base)

add_compile_options(-std=c++11)
set(${CMAKE_BUILD_TYPE} RELEASE)
include_directories(include)
find_package(catkin REQUIRED)
find_package(catkin_simple REQUIRED)

catkin_simple(ALL_DEPS_REQUIRED)

set(HEADERS 
    include/dvs_base/dvs_base_event_packet.hpp
    include/dvs_base/dvs_base_event.hpp
    include/dvs_base/dvs_base_io.hpp
    )
set(SOURCES 
    src/test.cpp
)

cs_add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

cs_install()
cs_export()