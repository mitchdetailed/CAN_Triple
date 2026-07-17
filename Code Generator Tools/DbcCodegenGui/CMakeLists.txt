cmake_minimum_required(VERSION 3.16)
project(DbcCodegenGui LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(DbcCodegenGui WIN32
    main.cpp
    mainwindow.cpp
    mainwindow.h
    dbcparser.cpp
    dbcparser.h
    codegen.cpp
    codegen.h
    dbc.h
)

target_link_libraries(DbcCodegenGui PRIVATE Qt6::Widgets)
