cmake_minimum_required(VERSION 3.0.2)
project(dvs_base)

add_compile_options(-std=c++17 -O3)
set(${CMAKE_BUILD_TYPE} RELEASE)
include_directories(include)
find_package(catkin REQUIRED)
find_package(catkin_simple REQUIRED)

catkin_simple(ALL_DEPS_REQUIRED)

set(HEADERS 
    include/dvs_base/dvs_base_event_packet.hpp
    include/dvs_base/dvs_base_event.hpp
    include/dvs_base/dvs_base_exp_sys.hpp
    include/dvs_base/dvs_base_io.hpp
    include/dvs_base/dvs_base_visualization.hpp
    include/dvs_base/dvs_base.hpp

    include/rpg_dvs/rpg_dvs_event.hpp
    )

set(SOURCES 
    src/test.cpp
)

find_package(OpenCV 3 REQUIRED)

cs_add_library(${PROJECT_NAME} ${HEADERS} src/useless.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

cs_add_executable(test01  ${SOURCES})
target_link_libraries(test01 ${PROJECT_NAME})

cs_install()
cs_export()