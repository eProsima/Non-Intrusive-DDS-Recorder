cmake_minimum_required(VERSION 2.8.12)

#set CMAKE_BUILD_TYPE to Release as default


project("DDSRecorder")
set(PROJECT_NAME "DDSRecorder")
message(STATUS "Configuring ${PROJECT_NAME}")

#Version information


#Generation of windows installer
if(WIN32)
	option(EPROSIMA_INSTALLER "Activate the creation of a build to create windows installers" OFF)
	option(EPROSIMA_INSTALLER_MINION "Informs this is part of an installer" OFF)
endif()

#Warning level

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

# eProsima build options
option(EPROSIMA_BUILD "Activate internal building" OFF)
option(MINION "Tells if this is a subproject of a superproject" OFF)

if(EPROSIMA_INSTALLER)
	set(EPROSIMA_BUILD ON)
endif()

#Load CMAKE mocules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)

#Check libraries
include(${PROJECT_SOURCE_DIR}/cmake/dev/boost_libraries.cmake)
set(BOOST_LIBRARIES_DEFAULT thread system date_time chrono regex atomic)
check_boost(${BOOST_LIBRARIES_DEFAULT})

#Load external eProsima projects
option(THIRDPARTY "Activate the use of internal thirdparties" ON)

if(EPROSIMA_BUILD)
	set(THIRDPARTY ON)
endif()

include(${PROJECT_SOURCE_DIR}/cmake/dev/eprosima_libraries.cmake)

find_eprosima_package(fastcdr)

#Compile library
add_subdirectory(src)

#Packaging

install_eprosima_libraries()
install_boost(ALL thread system date_time chrono regex atomic)

if(MSVC OR MSVC_IDE)
	if(EPROSIMA_INSTALLER)
		set(CPACK_COMPONENTS_ALL ${CPACK_COMPONENTS_ALL}
			libraries_i86Win32VS2013
			libraries_x64Win64VS2013
			libraries_i86Win32VS2015
			libraries_x64Win64VS2015
			)
	else()
		set(CPACK_COMPONENTS_ALL ${CPACK_COMPONENTS_ALL} libraries_${MSVC_ARCH})
	endif()
else()
	set(CPACK_COMPONENTS_ALL ${CPACK_COMPONENTS_ALL} libraries)
endif()

include(${PROJECT_SOURCE_DIR}/cmake/packaging/eProsimaPackaging.cmake)

