cmake_minimum_required(VERSION 3.30)
project(todo)

set(CMAKE_CXX_STANDARD 23)

add_executable(todo main.cpp
        src/components/todo_item_view.cpp
        src/components/todo_item_view.hpp
        src/components/todo_view.cpp
        src/components/todo_view.hpp
        src/todo.hpp
        src/pages/todo_page.cpp
        src/pages/todo_page.hpp)

target_link_libraries(todo PUBLIC wt wthttp)

add_custom_command(
        TARGET todo PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/config
        ${CMAKE_BINARY_DIR}/config)

add_custom_command(
        TARGET todo PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        ${CMAKE_BINARY_DIR}/resources)