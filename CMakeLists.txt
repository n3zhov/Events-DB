cmake_minimum_required(VERSION 3.20)
project(YellowBeltFinal)

set(CMAKE_CXX_STANDARD 17)

add_executable(YellowBeltFinal main.cpp condition_parser.cpp condition_parser_test.cpp node.cpp token.cpp date.cpp database.cpp test_db.h)
