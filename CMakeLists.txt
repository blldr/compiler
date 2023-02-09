cmake_minimum_required(VERSION 3.25)

project(compiler)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(compiler main.c lexer.c lexer.h parser.c parser.h linkedlist.c linkedlist.h)  
