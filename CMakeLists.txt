cmake_minimum_required(VERSION 2.8)

## Use the variable PROJECT_NAME for changing the target name
set( PROJECT_NAME "Meat_Starto_Mod" )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

## Set our project name
project(${PROJECT_NAME})

include_directories("src" "src/Mapa" "src/physicsEngine", "src/renderEngine" )

#include_directories("lib/")
#include_directories("lib/tinyxml2")


## Use all the *.cpp files we found under this folder for the project
FILE(GLOB_RECURSE SRCS "src/*.cpp" "src/Mapa/*.cpp"  "src/physicsEngine/*.cpp" "src/renderEngine/*.cpp")

## Define the executable
add_executable(${PROJECT_NAME} ${SRCS})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})


#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions

find_package(Threads)
find_package(SFML 2 REQUIRED network audio graphics window system)
find_package(tinyxml2 REQUIRED )
find_package(Box2D REQUIRED)


## this if only check sfml is found
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
  target_link_libraries(${PROJECT_NAME} tinyxml2)
  target_link_libraries(${PROJECT_NAME} ${BOX2D_LIBRARY})
endif()

