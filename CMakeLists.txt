cmake_minimum_required(VERSION 2.6)
project(VOSKHOD-1)

include_directories(
	src
)	

add_executable(game
	src/game/main.cpp
)

add_library(voskhod-1
	src/Voskhod-1/Core.cpp
)