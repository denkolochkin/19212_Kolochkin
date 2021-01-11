cmake_minimum_required(VERSION 3.17)
project(lab2b_new)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab2b_new main.cpp
                BaseStrategy.cpp HardStrategy.cpp
                NeatStrategy.cpp StupidStrategy.cpp
                NotSoStupidStrategy.cpp TrivialStrategy.cpp
                Factory.h Strategy.h StupidStrategy.h
                NotSoStupidStrategy.h TrivialStrategy.h
                BaseStrategy.h HardStrategy.h NeatStrategy.h
                BlackJackTests.cpp BlackJack.h BlackJack.cpp
                Printer.cpp Printer.h)

ADD_SUBDIRECTORY (googletest)
include_directories(googletest/googletest/include)

target_link_libraries(lab2b_new gtest gtest_main)

add_library(${PROJECT_NAME}_lib SHARED
        BaseStrategy.cpp BlackJack.cpp HardStrategy.cpp NeatStrategy.cpp
        NotSoStupidStrategy.cpp Printer.cpp StupidStrategy.cpp
        TrivialStrategy.cpp
        )

target_include_directories(${PROJECT_NAME}_lib
        PUBLIC
        ${PROJECT_SOURCE_DIR}
        )



