cmake_minimum_required(VERSION 4.0)
project(ActivityRegister1_0)

set(CMAKE_CXX_STANDARD 20)

add_executable(ActivityRegister1_0 main.cpp
        Activity.cpp
        Activity.h
        Register.cpp
        Register.h
        TimeFormat.cpp
        TimeFormat.h
)
target_link_libraries(ActivityRegister1_0 ncurses)

add_executable(tests
        tests.cpp
        Activity.cpp
        Register.cpp
        TimeFormat.cpp
        libs/catch2/catch_amalgamated.cpp
)
target_include_directories(tests PRIVATE libs/catch2)
target_link_libraries(tests ncurses)
enable_testing()
add_test(NAME MyTests COMMAND tests)

