cmake_minimum_required(VERSION 3.0.0)
project(scrabble-game-sfml VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cpp CollinsScrabbleWords_2019.txt)

ADD_LIBRARY(LibsModule 
word.h word.cpp 
utilities.h utilities.cpp 
objects.h box.h slot.h button.h objects.cpp
construction.h construction.cpp
)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system LibsModule)

install(TARGETS ${PROJECT_NAME} LibsModule)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
