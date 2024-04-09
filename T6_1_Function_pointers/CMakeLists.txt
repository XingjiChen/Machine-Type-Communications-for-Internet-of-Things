# Copyright (c) 2024 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.19.0)

option(VERBOSE_BUILD "Have a verbose build process")
if(VERBOSE_BUILD)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()

option(CMAKE_JSON_OUT "Have JSON output format on")
if(CMAKE_JSON_OUT)
    set(CMAKE_JSON_OUT ON)
endif()

set(MBED_PATH ${CMAKE_CURRENT_SOURCE_DIR}/mbed-os CACHE INTERNAL "")
set(MBED_CONFIG_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")
set(APP_TARGET submission)
set(CMAKE_BUILD_TYPE debug CACHE INTERNAL "")


include(${MBED_PATH}/tools/cmake/app.cmake)

project(${APP_TARGET})



add_subdirectory(${MBED_PATH})

message(DEBUG "BUILD directory is ${CMAKE_BINARY_DIR}")
message(DEBUG "SRC directory is ${CMAKE_SOURCE_DIR}")

# Add all .c, - files under src/ directory
file(GLOB SOURCES_C "src/*.c")
# Add all .cpp, - files under src/ directory
file(GLOB SOURCES_CPP "src/*.cpp")
# Add all .hpp, - files under src/ directory
file(GLOB SOURCES_HPP "src/*.hpp")
# Add all .h, - files under src/ directory
file(GLOB SOURCES_H "src/*.h")
set(SOURCES ${SOURCES_C} ${SOURCES_CPP} ${SOURCES_H} ${SOURCES_HPP})
message(TRACE "SRC directory source code files: \n\t-- HEADERS: ${SOURCES_H}${SOURCES_HPP}\n\t-- C SOURCES: ${SOURCES_C}\n\t-- CPP SOURCES:${SOURCES_CPP}\n\t-- ALL:${SOURCES}")
# add the executable target
add_executable(${APP_TARGET})

target_sources(${APP_TARGET} PUBLIC ${SOURCES})
target_include_directories(${APP_TARGET} PUBLIC "src")

if(CMAKE_JSON_OUT)
    target_compile_options(${APP_TARGET}
        PRIVATE
            $<$<COMPILE_LANGUAGE:C>:-fdiagnostics-format=json>
    )
    target_compile_options(${APP_TARGET}
        PRIVATE
            $<$<COMPILE_LANGUAGE:CXX>:-fdiagnostics-format=json>
    )
endif()
# target_link_options(${APP_TARGET}
#     PUBLIC
#         "-fdiagnostics-format=json"
# )

get_target_property(CONF_COMPILE_FLAGS ${APP_TARGET} COMPILE_OPTIONS)
# also see: COMPILE_DEFINITIONS INCLUDE_DIRECTORIES
message(TRACE "-- Target compiler flags are: ${CONF_COMPILE_FLAGS}")

target_link_libraries(${APP_TARGET} mbed-os)

mbed_set_post_build(${APP_TARGET})