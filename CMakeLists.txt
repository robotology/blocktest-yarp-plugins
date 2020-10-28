################################################################################
#                                                                              #
# Copyright (C) 2019 Fondazione Istitito Italiano di Tecnologia (IIT)          #
# All Rights Reserved.                                                         #
#                                                                              #
################################################################################

# @author Luca Tricerri <luca.tricerri@iit.it>  

cmake_minimum_required(VERSION 3.5)
#Module creation

project(blocktestyarpplugins
        LANGUAGES C CXX
        VERSION 1.1.0)

option(ENABLE_MSVC_WARNINGS "Enable the compilation warnings in windows" ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  if (ENABLE_MSVC_WARNINGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
  add_compile_options(-bigobj)
else ()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
  set(CMAKE_EXE_LINKER_FLAGS  "-rdynamic")
endif ()

# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE.
# See https://cmake.org/cmake/help/v3.4/variable/CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS.html
# See https://blog.kitware.com/create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

#Thrift for clock
set(YARP_MINIMUM_REQUIRED_VERSION 3.0.102)

find_package(YARP 3.3.0 REQUIRED COMPONENTS os conf dev sig math rosmsg name idl_tools)
find_package(blocktestcore 2.3.0 REQUIRED)
find_package(YCM REQUIRED)

if(${YARP_VERSION} VERSION_LESS ${YARP_MINIMUM_REQUIRED_VERSION})
    message(FATAL_ERROR "YARP version ${YARP_VERSION} not sufficient, at least version ${YARP_MINIMUM_REQUIRED_VERSION} is required.")
endif()

yarp_add_idl(CLOCK_RPC_FILES thrift/clock_rpc.thrift)

# Enable RPATH support for installed binaries and libraries
include(AddInstallRPATHSupport)
add_install_rpath_support(BIN_DIRS "${CMAKE_INSTALL_FULL_BINDIR}"
                          LIB_DIRS "${CMAKE_INSTALL_FULL_LIBDIR}"
                          INSTALL_NAME_DIR "${CMAKE_INSTALL_FULL_LIBDIR}"
                          USE_LINK_PATH)


#include_directories(${Boost_INCLUDE_DIRS})

add_library(ClockRpc STATIC ${CLOCK_RPC_FILES} thrift/clock_rpc.thrift)
set_target_properties(ClockRpc PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(ClockRpc YARP::YARP_os)

# Extract the include directory from the files names
foreach(file ${CLOCK_RPC_FILES})
    STRING(REGEX MATCH ".+\\.h?h$" file ${file})
    if(file)
        get_filename_component(include_dir ${file} DIRECTORY)
        list(APPEND CLOCKRPC_INCLUDE_DIRS ${include_dir})
    endif()
endforeach()

# Setup the include directories
target_include_directories(ClockRpc PUBLIC
    $<BUILD_INTERFACE:${CLOCKRPC_INCLUDE_DIRS}>)

file(GLOB allSrc "src/*.h" "src/*.cpp")

add_library(${PROJECT_NAME} MODULE ${allSrc})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} PRIVATE blocktestcore::blocktestcore
                                              YARP::YARP_os
                                              YARP::YARP_init
                                              YARP::YARP_dev
                                              YARP::YARP_conf
                                              ClockRpc)

#xml template folder
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_LIST_DIR}/xmltemplate
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/$<CONFIG>/xmltemplate)
    else()
    file(COPY ${CMAKE_CURRENT_LIST_DIR}/xmltemplate
            DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
endif()

install(DIRECTORY xmltemplate DESTINATION ${CMAKE_INSTALL_BINDIR})

# Add install target
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/")
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_BINDIR}/${PROJECT_NAME})

# Add uninstall target
include(AddUninstallTarget)
