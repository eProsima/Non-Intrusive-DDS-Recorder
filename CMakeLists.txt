###
#
#	CMAKE Build rules for DDSRecorder
#
####
cmake_minimum_required(VERSION 2.8.12)

#set CMAKE_BUILD_TYPE to Release as default
if(DEFINED CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose Type of build, options are> None Debug Release RelWithDebInfo MinSizeRel."
	   )
else()
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose Type of build, options are> None Debug Release RelWithDebInfo MinSizeRel."
	   )
endif()

project("DDSRecorder")
set(PROJECT_NAME "DDSRecorder")
set(PROJECT_NAME_LARGE "DDSRecorder")
set(PROJECT_NAME_STYLED "DDSRecorder")
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

#Load CMAKE mocules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)

#Check libraries
include(${PROJECT_SOURCE_DIR}/cmake/dev/boost_libraries.cmake)
set(BOOST_LIBRARIES_DEFAULT thread system date_time chrono regex atomic)
check_boost(${BOOST_LIBRARIES_DEFAULT})

#Load external eProsima projects
option(THIRDPARTY "Activate the use of internal thirdparties" OFF)


include(${PROJECT_SOURCE_DIR}/cmake/dev/eprosima_libraries.cmake)

if(THIRDPARTY)
    find_eprosima_package(fastcdr)
endif()

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

add_compile_options(--std=c++0x)

#Compile 
add_subdirectory(src)

###
# INSTALL
###

# Install external eprosima libraries and boost
if(THIRDPARTY)
    # Install includes
            install(DIRECTORY ${PROJECT_BINARY_DIR}/external/install/${INCLUDE_INSTALL_DIR}/
                DESTINATION ${INCLUDE_INSTALL_DIR}
                COMPONENT headers
                OPTIONAL
                )

            # Install libraries
            install(DIRECTORY ${PROJECT_BINARY_DIR}/external/install/${LIB_INSTALL_DIR}/
                DESTINATION ${LIB_INSTALL_DIR}
                USE_SOURCE_PERMISSIONS
                COMPONENT libraries
                )


endif()
install_boost(ALL thread system date_time chrono regex atomic)


#include(${PROJECT_SOURCE_DIR}/cmake/packaging/eProsimaPackaging.cmake)
