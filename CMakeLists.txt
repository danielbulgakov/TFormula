cmake_minimum_required(VERSION 3.21)
project(TFormula)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(TFormula
        Source.cpp
        TFormula.cpp
        TFormula.h
        Translator.cpp
        Translator.h
        TStack.h
        TTable.h
        Validator.cpp
        Validator.h)
