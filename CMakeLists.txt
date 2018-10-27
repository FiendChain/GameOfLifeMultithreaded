cmake_minimum_required(VERSION 3.0)

project("Game of Life - Multithreaded")

set(SRC_DIR ${CMAKE_SOURCE_DIR}/source)
set(APP_DIR ${SRC_DIR}/App)
set(GOL_DIR ${SRC_DIR}/GOL)

include_directories(${SRC_DIR} ${APP_DIR} ${GOL_DIR})


set(GOL_FILES 
    ${GOL_DIR}/GOL.cpp
    ${GOL_DIR}/GOLGrid.cpp
    ${GOL_DIR}/ThreadPool.cpp
    ${GOL_DIR}/Rules/GOLNormal.cpp)

add_library(GOL ${GOL_FILES})
target_compile_options(GOL PUBLIC -std=c++17 -O3 -pthread)
target_link_libraries(GOL sfml-graphics sfml-audio sfml-window sfml-system)

set(APP_FILES
    ${APP_DIR}/App.cpp
    ${APP_DIR}/Camera.cpp
    ${APP_DIR}/ControllableCamera.cpp)

add_library(App ${APP_FILES})
target_compile_options(App PUBLIC -std=c++17 -O3 -pthread)
target_link_libraries(App GOL sfml-graphics sfml-audio sfml-window sfml-system)

add_executable(main ${SRC_DIR}/main.cpp)
target_link_libraries(main App)