cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(cp_main)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp")
  configure_file(${CMAKE_SOURCE_DIR}/Main.cpp.template ${CMAKE_SOURCE_DIR}/Main.cpp COPYONLY)
endif()

set(HEADERS algorithms/ds/sparse_table.hpp algorithms/ds/ufds.hpp)

add_executable(cp_main Main.cpp ${HEADERS})

target_include_directories(cp_main
                           PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/algorithms>
                           )

target_compile_features(cp_main PRIVATE cxx_std_20)
target_compile_definitions(cp_main PUBLIC DEBUG=1)

target_link_libraries(cp_main)


add_custom_command(TARGET cp_main POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Main.cpp ${CMAKE_SOURCE_DIR}/MainFull.cpp)

find_program (SED_TOOL NAMES sed)
if (NOT SED_TOOL)
  message (FATAL_ERROR "Unable to find sed")
endif (NOT SED_TOOL)

file(READ ${CMAKE_SOURCE_DIR}/algorithms/ds/sparse_table.hpp SPARSE_TABLE_CONTENT)
add_custom_command(TARGET cp_main POST_BUILD
                   COMMAND ${SED_TOOL} -i -e '/\\\#include <ds\\/sparse_table\\.hpp>/{r ${CMAKE_SOURCE_DIR}/algorithms/ds/sparse_table.hpp' -e 'd}' ${CMAKE_SOURCE_DIR}/MainFull.cpp)
add_custom_command(TARGET cp_main POST_BUILD
                   COMMAND ${SED_TOOL} -i -e '/\\\#include<ds\\/sparse_table\\.hpp>/{r ${CMAKE_SOURCE_DIR}/algorithms/ds/sparse_table.hpp' -e 'd}' ${CMAKE_SOURCE_DIR}/MainFull.cpp)
add_custom_command(TARGET cp_main POST_BUILD
                   COMMAND ${SED_TOOL} -i -e '/\\\#include \"ds\\/sparse_table\\.hpp\"/{r ${CMAKE_SOURCE_DIR}/algorithms/ds/sparse_table.hpp' -e 'd}' ${CMAKE_SOURCE_DIR}/MainFull.cpp)
add_custom_command(TARGET cp_main POST_BUILD
                   COMMAND ${SED_TOOL} -i -e '/\\\#include\"ds\\/sparse_table\\.hpp\"/{r ${CMAKE_SOURCE_DIR}/algorithms/ds/sparse_table.hpp' -e 'd}' ${CMAKE_SOURCE_DIR}/MainFull.cpp)

add_custom_command(TARGET cp_main POST_BUILD
                   COMMAND ${SED_TOOL} -i -e '/\\\#include <ds\\/min_max_queue\\.hpp>/{r ${CMAKE_SOURCE_DIR}/algorithms/ds/min_max_queue.hpp' -e 'd}' ${CMAKE_SOURCE_DIR}/MainFull.cpp)
add_custom_command(TARGET cp_main POST_BUILD
                   COMMAND ${SED_TOOL} -i -e '/\\\#include<ds\\/min_max_queue\\.hpp>/{r ${CMAKE_SOURCE_DIR}/algorithms/ds/min_max_queue.hpp' -e 'd}' ${CMAKE_SOURCE_DIR}/MainFull.cpp)
add_custom_command(TARGET cp_main POST_BUILD
                   COMMAND ${SED_TOOL} -i -e '/\\\#include \"ds\\/min_max_queue\\.hpp\"/{r ${CMAKE_SOURCE_DIR}/algorithms/ds/min_max_queue.hpp' -e 'd}' ${CMAKE_SOURCE_DIR}/MainFull.cpp)
add_custom_command(TARGET cp_main POST_BUILD
                   COMMAND ${SED_TOOL} -i -e '/\\\#include\"ds\\/min_max_queue\\.hpp\"/{r ${CMAKE_SOURCE_DIR}/algorithms/ds/min_max_queue.hpp' -e 'd}' ${CMAKE_SOURCE_DIR}/MainFull.cpp)

add_custom_command(TARGET cp_main POST_BUILD
                   COMMAND ${SED_TOOL} -i -e '/\\\#include <ds\\/ufds\\.hpp>/{r ${CMAKE_SOURCE_DIR}/algorithms/ds/ufds.hpp' -e 'd}' ${CMAKE_SOURCE_DIR}/MainFull.cpp)
add_custom_command(TARGET cp_main POST_BUILD
                   COMMAND ${SED_TOOL} -i -e '/\\\#include<ds\\/ufds\\.hpp>/{r ${CMAKE_SOURCE_DIR}/algorithms/ds/ufds.hpp' -e 'd}' ${CMAKE_SOURCE_DIR}/MainFull.cpp)
add_custom_command(TARGET cp_main POST_BUILD
                   COMMAND ${SED_TOOL} -i -e '/\\\#include \"ds\\/ufds\\.hpp\"/{r ${CMAKE_SOURCE_DIR}/algorithms/ds/ufds.hpp' -e 'd}' ${CMAKE_SOURCE_DIR}/MainFull.cpp)
add_custom_command(TARGET cp_main POST_BUILD
                   COMMAND ${SED_TOOL} -i -e '/\\\#include\"ds\\/ufds\\.hpp\"/{r ${CMAKE_SOURCE_DIR}/algorithms/ds/ufds.hpp' -e 'd}' ${CMAKE_SOURCE_DIR}/MainFull.cpp)


