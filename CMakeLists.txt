cmake_minimum_required(VERSION 2.6)
project(VOSKHOD-1)

if(MSVC)
  include_directories(
    contrib/msvc-windows-x86/glew/include
    contrib/msvc-windows-x86/SDL2/include
  )

  link_directories(
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/lib
  )
endif()

if(MSVC)
  add_definitions(-DSDL_MAIN_HANDLED)
endif()

if(MSVC)
  target_link_libraries(voskhod-1
    SDL2 glew32 opengl32
  )
else()
  target_link_libraries(voskhod-1
    SDL2 GLU GLEW GL
  )
endif()

include_directories(
	src
)	

add_executable(game
	src/game/main.cpp
)

add_library(voskhod-1
	src/Voskhod-1/Core.cpp
)

if(MSVC)
  add_custom_command(TARGET triangle POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/bin/SDL2.dll"
      "$<TARGET_FILE_DIR:triangle>"
  )

  add_custom_command(TARGET triangle POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/bin/glew32.dll"
      "$<TARGET_FILE_DIR:triangle>"
  )
endif()