cmake_minimum_required(VERSION 3.27)
project(Proyecto_Parcial4)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/Users/crist/.vcpkg-clion/vcpkg/installed/x64-windows/share/sfml")

add_executable(Proyecto_Parcial4 main.cpp Pong.cpp
        Pong.cpp
        Pong.cpp)

find_package(SFML 2.5 COMPONENTS graphics system window CONFIG REQUIRED)

target_link_libraries(Proyecto_Parcial4 sfml-graphics sfml-system sfml-window)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/OpenSans-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})