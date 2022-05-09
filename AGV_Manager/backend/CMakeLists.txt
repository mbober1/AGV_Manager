cmake_minimum_required(VERSION 2.8)
project(AGVs)

add_compile_options(-c
                    -Wall
                    -Wextra
                    -Winit-self
                    -Wold-style-cast
                    -Woverloaded-virtual
                    -Wuninitialized
                    -pedantic
                    -pedantic-errors
                    -std=c++17
                    -g
)

set(SRC
    src/main.cpp
    src/Warehouse.cpp
    src/Stage.cpp
    src/AGV.cpp
)


add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(AGVs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)