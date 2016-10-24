cmake_minimum_required(VERSION 3.3)
project(lab4var3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp func_init.h AnaliticalConstEquation.cpp AnaliticalConstEquation.h types.h NumericalConstEquation.cpp NumericalConstEquation.h NumericalVariableEquation.cpp NumericalVariableEquation.h)
add_executable(lab4var3 ${SOURCE_FILES})