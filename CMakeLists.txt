cmake_minimum_required(VERSION 3.28)
project(todo)

set(CMAKE_CXX_STANDARD 23)

find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS serialization)

add_executable(todo src/main.cpp
        src/note/notestore.cpp include/note/notestore.h
        src/note/note.cpp include/note/note.h
        src/core/application.cpp include/core/application.h
        src/ui/Component.cpp include/ui/Component.h
        src/ui/noteviewcontroller.cpp include/ui/noteviewcontroller.h
        src/ui/noteviewmodel.cpp include/ui/noteviewmodel.h
        include/ui/uihelpers.h
        include/ui/uiconstants.h)

target_include_directories(todo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(WIN32)
    set_target_properties(todo PROPERTIES WIN32_EXECUTABLE True)
endif()

target_link_libraries(todo
        PRIVATE
        imgui::imgui
        glfw

        ${Boost_LIBRARIES}
)

# Useful for debugging
#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()