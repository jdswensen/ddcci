cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(ddcci)

set(ENUM_SRC src/ddcci_win.c)
add_executable(enum-monitors ${ENUM_SRC})
target_include_directories(enum-monitors PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src
)