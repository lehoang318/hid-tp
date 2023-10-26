cmake_minimum_required(VERSION 3.16)

project(hid-tp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(CTRL_PHY OBJECT
    ctrl_phy.c
    util.c
    hid_stub.cpp
)

add_subdirectory(phy-ut)
