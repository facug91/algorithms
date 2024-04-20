cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(cp_main)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp")
  configure_file(${CMAKE_SOURCE_DIR}/Main.cpp.template ${CMAKE_SOURCE_DIR}/Main.cpp COPYONLY)
endif()

add_executable(cp_main Main.cpp)
target_compile_features(cp_main PRIVATE cxx_std_17)
target_compile_definitions(cp_main PUBLIC DEBUG=1)

file(GLOB_RECURSE APP_SOURCES algorithms/**.cpp)
foreach(sourcefile ${APP_SOURCES})
  # Cut off the file extension and directory path
  get_filename_component(testname ${sourcefile} NAME_WE)
  add_executable(${testname} ${sourcefile})
  target_compile_features(${testname} PRIVATE cxx_std_17)
  target_compile_definitions(${testname} PUBLIC DEBUG=1)
endforeach(sourcefile ${APP_SOURCES})
