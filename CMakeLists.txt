###
#
#	CMAKE Build rules for ni_ddsrecorder
#
####
cmake_minimum_required(VERSION 3.20)

#set CMAKE_BUILD_TYPE to Release as default
if(DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose Type of build, options are> None Debug Release RelWithDebInfo MinSizeRel."
        )
else()
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose Type of build, options are> None Debug Release RelWithDebInfo MinSizeRel."
        )
endif()

project(ni_ddsrecorder VERSION 1.1.0 LANGUAGES C CXX)

set(PROJECT_NAME "NI_DDSRecorder")
set(PROJECT_NAME_LARGE "Non-Intrusive DDSRecorder")
set(PROJECT_NAME_STYLED "Non-Intrusive DDS Recorder")
string(TOUPPER "${PROJECT_NAME}" PROJECT_NAME_UPPER)
set(${PROJECT_NAME}_DESCRIPTION_SUMMARY "Non-intrusive RTPS protocol packet analyzer.")
set(${PROJECT_NAME}_DESCRIPTION "eProsima ${PROJECT_NAME} non-intrusive RTPS protocol packet analyzer.")
message(STATUS "Configuring ${PROJECT_NAME}")

#Test System Configuration
include(${PROJECT_SOURCE_DIR}/cmake/dev/check_configuration.cmake)
check_stdcxx()
check_compile_feature()
check_endianness()

#Check MSVC Architecture
if(MSVC OR MSVC_IDE)
    check_msvc_arch()
endif()

#Installation paths

set(BIN_INSTALL_DIR bin/ CACHE PATH "Installation directory for binaries")
set(INCLUDE_INSTALL_DIR include/ CACHE PATH "Installation directory for C++ Headers")
set(LIB_INSTALL_DIR lib/ CACHE PATH "Installation directory for libraries")
set(DATA_INSTALL_DIR share/ CACHE PATH "Installation directory for data")
if(WIN32)
    set(DOC_DIR "doc")
else()
    set(DOC_DIR "${DATA_INSTALL_DIR}/doc")
endif()
set(DOC_INSTALL_DIR ${DOC_DIR} CACHE PATH "Installation directory for documentation")
if(WIN32)
    set(LICENSE_INSTALL_DIR . CACHE PATH "Installation directory for licenses")
else()
    set(LICENSE_INSTALL_DIR ${DATA_INSTALL_DIR}/${PROJECT_NAME} CACHE PATH "Installation directory for licenses")
endif()

# eProsima build options
option(EPROSIMA_BUILD "Activate internal building" OFF)

if(EPROSIMA_INSTALLER)
    set(EPROSIMA_BUILD ON)
endif()

#Load CMAKE mocules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)

#Check libraries
include(${PROJECT_SOURCE_DIR}/cmake/dev/boost_libraries.cmake)
set(BOOST_LIBRARIES_DEFAULT chrono date_time thread system)
check_boost(${BOOST_LIBRARIES_DEFAULT})

#Load external eProsima projects
option(THIRDPARTY "Activate the use of internal thirdparties" ON)

if(EPROSIMA_BUILD)
    set(THIRDPARTY ON)
endif()

# Fast DDS is used purely as a local type model: it parses the IDL file given with '-idl' and
# decodes the CDR payloads. The recorder never joins a DDS domain. It is not a thirdparty
# submodule like Fast CDR, so it has to be found already installed.
#
# foonathan_memory is probed first because fastdds-config.cmake does
# 'find_dependency(foonathan_memory REQUIRED)'. A prefix path that reaches Fast DDS but not
# foonathan_memory therefore fails deep inside that file, with an error naming a package this
# project never asks for; checking here turns that into something actionable.
find_package(foonathan_memory QUIET)

if(NOT foonathan_memory_FOUND)
    message(FATAL_ERROR
        "Could not find foonathan_memory, a required dependency of Fast DDS. Add its "
        "installation prefix to CMAKE_PREFIX_PATH. In a colcon workspace it is installed by "
        "the foonathan_memory_vendor package, and sourcing the workspace puts it on the path.")
endif()

find_package(fastcdr)

find_package(fastdds REQUIRED)
include(${PROJECT_SOURCE_DIR}/cmake/dev/external_dependencies.cmake)
#Remind the user the need to give the directories to sqlite and winpcap
if(WIN32)
    if(DEFINED WINPCAP_ROOT)
        #set(PCAP_INCLUDE_DIR ${WINPCAP_ROOT}/Include CACHE STRING "Include directory of the WinPCAP developer pack")
        #set(PCAP_LIBRARY ${WINPCAP_ROOT}/Lib/wpcap.lib ${WINPCAP_ROOT}/Lib/Packet.lib CACHE STRING "Library directory of the WinPCAP developer pack")
        find_pcap()
        if(NOT PCAP_FOUND)
            message(FATAL_ERROR "Could not find required libraries in the system. Please install pcap and run cmake again")
        endif()
    else()
        message(FATAL_ERROR "WinPCAP developer pack is needed on this project. You need to set -DWINPCAP_ROOT")
    endif()
else()
    find_pcap()
    find_sqlite3()
    if(NOT PCAP_FOUND)
        message(FATAL_ERROR "Could not find required libraries in the system. Please install pcap and run cmake again")
    endif()
    if(NOT SQLITE3_FOUND)
        message(FATAL_ERROR "Could not find required libraries in the system. Please install sqlite3 and run cmake again")
    endif()
endif()

# C++17 is what Fast DDS needs. The project was pinned to C++11 by the flex 2.5.35 scanner in
# src/idlparser, which used the 'register' keyword C++17 removed; that parser is gone.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Compile library
add_subdirectory(src)

###############################################################################
# Documentation
###############################################################################
# Add an option to toggle the generation of the API documentation.
option(BUILD_DOCUMENTATION "Use doxygen and libreoffice to create product documentation" OFF)

if(EPROSIMA_INSTALLER)
    set(BUILD_DOCUMENTATION ON)
endif()

if(BUILD_DOCUMENTATION)
    add_subdirectory(doc/user_manual)
endif()
# Packaging
# Install external eprosima libraries
install_boost(${BOOST_LIBRARIES_DEFAULT})

# Install licenses
#install(FILES ${PROJECT_SOURCE_DIR}/doc/licencias/${PROJECT_NAME}_LIBRARY_LICENSE.txt
#    ${PROJECT_SOURCE_DIR}/doc/licencias/LGPLv3_LICENSE.txt
#    DESTINATION ${LICENSE_INSTALL_DIR}
#    COMPONENT licenses
#    )
set(CPACK_COMPONENT_LICENSES_HIDDEN 1)

# Install examples
install(DIRECTORY ${PROJECT_SOURCE_DIR}/examples
    DESTINATION .
    COMPONENT examples
    )

set(CPACK_COMPONENT_EXAMPLES_DISPLAY_NAME "Examples")
set(CPACK_COMPONENT_EXAMPLES_DESCRIPTION "eProsima ${PROJECT_NAME} examples")

set(CPACK_COMPONENTS_ALL licenses examples)

if(EPROSIMA_INSTALLER)
    ## Download reditributables
    file(DOWNLOAD "https://aka.ms/vs/16/release/vc_redist.x64.exe" "${PROJECT_BINARY_DIR}/vc_redist.x64.exe")
    file(DOWNLOAD "https://aka.ms/vs/16/release/vc_redist.x86.exe" "${PROJECT_BINARY_DIR}/vc_redist.x86.exe")
endif()

set(CPACK_COMPONENTS_ALL ${CPACK_COMPONENTS_ALL} binaries)

include(${PROJECT_SOURCE_DIR}/cmake/packaging/eProsimaPackaging.cmake)
