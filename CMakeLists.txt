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

#Version information

#If not set, copy over product version from configure.ac
if(NOT PROJECT_MAJOR_VERSION)
    file(STRINGS
        ${PROJECT_SOURCE_DIR}/configure.ac
        PROJECT_MAJOR_VERSION_TMP
        REGEX "^m4_define\\(\\[?version_major\\]?, *\\[?[0-9]+\\]?\\)"
        )
    file(STRINGS
        ${PROJECT_SOURCE_DIR}/configure.ac
        PROJECT_MINOR_VERSION_TMP
        REGEX "^m4_define\\(\\[?version_minor\\]?, *\\[?[0-9]+\\]?\\)"
        )
    file(STRINGS
        ${PROJECT_SOURCE_DIR}/configure.ac
        PROJECT_MICRO_VERSION_TMP
        REGEX "^m4_define\\(\\[?version_micro\\]?, *\\[?[0-9]+\\]?\\)"
        )

    string(REGEX REPLACE "m4_define\\(\\[?version_major\\]?, *\\[?([0-9]+)\\]?\\)"
        "\\1"
        PROJECT_MAJOR_VERSION
        ${PROJECT_MAJOR_VERSION_TMP}
        )
    string(REGEX REPLACE "m4_define\\(\\[?version_minor\\]?, *\\[?([0-9]+)\\]?\\)"
        "\\1"
        PROJECT_MINOR_VERSION
        ${PROJECT_MINOR_VERSION_TMP}
        )
    string(REGEX REPLACE "m4_define\\(\\[?version_micro\\]?, *\\[?([0-9]+)\\]?\\)"
        "\\1"
        PROJECT_MICRO_VERSION
        ${PROJECT_MICRO_VERSION_TMP}
        )
endif()

set(PROJECT_VERSION ${PROJECT_MAJOR_VERSION}.${PROJECT_MINOR_VERSION}.${PROJECT_MICRO_VERSION})

message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "To change de version modify the file configure.ac")



#Generation of windows installer
if(WIN32)
	option(EPROSIMA_INSTALLER "Activate the creation of a build to create windows installers" OFF)
	option(EPROSIMA_INSTALLER_MINION "Informs this is part of an installer" OFF)
endif()

#Warning level
if(MSVC OR MSVC_IDE)
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Wno-unknown-pragmas")
endif()

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

# Windows installer pending task

#Documentation

if(EPROSIMA_INSTALLER)
	set(BUILD_DOCUMENTATION ON)
endif()

if(BUILD_DOCUMENTATION)
	find_program(LIBREOFFICE_EXE soffice)
	if(LIBREOFFICE_EXE)
		message(STATUS "Found Libreoffice: ${LIBREOFFICE_EXE}")
		message(STATUS "Recall you need to have installed eProsima macros for Libreoffice")
	else()
		message(FATAL_ERROR "Libreoffice is needed to build the documentation")
	endif()

	#Target to create documentation directories
	add_custom_target(docdirs
		COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/doc
		COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}doc/pdf
		COMMENT "Creating documentation directory" VERBATIM)
	#Libreoffice
	if(WIN32)
		set(LIBREOFFICE_CONVERT_README_MACRO "macro//eProsima.documentation.changeHyperlinksAndVersionToHTML(${PROJECT_SOURCE_DIR}/doc/README.odt,${PROJECT_VERSION},./,/doc/)")
		set(README_LOCATION "${PROJECT_BINARY_DIR}/")
		set(README_INSTALL_LOCATION ".")
	else()
		set(LIBREOFFICE_CONVERT_README_MACRO "macro://eProsima.documentation.changeVersionToHTML(${PROJECT_SOURCE_DIR}/doc/README.odt,${PROJECT_VERSION})")
		set(README_LOCATION "${PROJECT_BINARY_DIR}/doc/")
		set(README_INSTALL_LOCATION "${DOC_INSTALL_DIR}")
	endif()
	add_custom_target(libreoffice
        COMMAND "${LIBREOFFICE_EXE}" --headless
        "macro:///eProsima.documentation.changeVersion(${PROJECT_SOURCE_DIR}/doc/pdf/${PROJECT_NAME} - Installation Manual.odt,${PROJECT_VERSION})"
        COMMAND ${CMAKE_COMMAND} -E rename "${PROJECT_SOURCE_DIR}/doc/pdf/${PROJECT_NAME} - Installation Manual.pdf" "${PROJECT_BINARY_DIR}/doc/pdf/${PROJECT_NAME_LARGE} - Installation Manual.pdf"
        COMMAND "${LIBREOFFICE_EXE}" --headless
        "macro:///eProsima.documentation.changeVersion(${PROJECT_SOURCE_DIR}/doc/pdf/${PROJECT_NAME} - User Manual.odt,${PROJECT_VERSION})"
        COMMAND ${CMAKE_COMMAND} -E rename "${PROJECT_SOURCE_DIR}/doc/pdf/${PROJECT_NAME_LARGE} - User Manual.pdf" "${PROJECT_BINARY_DIR}/doc/pdf/${PROJECT_NAME_LARGE} - User Manual.pdf"
        COMMAND "${LIBREOFFICE_EXE}" --headless ${LIBREOFFICE_CONVERT_README_MACRO} 
        COMMAND ${CMAKE_COMMAND} -E rename "${PROJECT_SOURCE_DIR}/doc/README.html" "${README_LOCATION}/README.html"
        DEPENDS
        "${PROJECT_SOURCE_DIR}/doc/pdf/${PROJECT_NAME} - Installation Manual.odt"
        "${PROJECT_SOURCE_DIR}/doc/pdf/${PROJECT_NAME} - User Manual.odt"
        "${PROJECT_SOURCE_DIR}/doc/README.odt"
        COMMENT "Generating documentation with libreoffice" VERBATIM)

    add_dependencies(libreoffice docdirs)

    add_custom_target(doc ALL
        COMMENT "Generated project documentation" VERBATIM)

endif()
# Packaging
# Install external eprosima libraries
install_eprosima_libraries()
install_boost(ALL thread system date_time chrono regex atomic)

# Install licenses
install(FILES ${PROJECT_SOURCE_DIR}/doc/licencias/${PROJECT_NAME}_LIBRARY_LICENSE.txt
    ${PROJECT_SOURCE_DIR}/doc/licencias/LGPLv3_LICENSE.txt
    DESTINATION ${LICENSE_INSTALL_DIR}
    COMPONENT licenses
    )
set(CPACK_COMPONENT_LICENSES_HIDDEN 1)

# Install examples
install(DIRECTORY ${PROJECT_SOURCE_DIR}/examples
    DESTINATION .
    COMPONENT examples
    )

set(CPACK_COMPONENT_EXAMPLES_DISPLAY_NAME "Examples")
set(CPACK_COMPONENT_EXAMPLES_DESCRIPTION "eProsima ${PROJECT_NAME} examples")

set(CPACK_COMPONENTS_ALL headers licenses examples)

if(BUILD_DOCUMENTATION)
    # Instalation of pdf files
    install(FILES 
        "${PROJECT_BINARY_DIR}/doc/pdf/${PROJECT_NAME} - Installation Manual.pdf"
        "${PROJECT_BINARY_DIR}/doc/pdf/${PROJECT_NAME} - User Manual.pdf"
        DESTINATION ${DOC_INSTALL_DIR}/pdf
        COMPONENT documentation
        )

    install(FILES 
        "${README_LOCATION}/README.html"
        DESTINATION ${README_INSTALL_LOCATION}
        COMPONENT documentation
        )

    ### Documentation component
    set(CPACK_COMPONENT_DOCUMENTATION_DISPLAY_NAME "Documentation")
    set(CPACK_COMPONENT_DOCUMENTATION_DESCRIPTION "eProsima ${PROJECT_NAME} documentation")

    set(CPACK_COMPONENTS_ALL ${CPACK_COMPONENTS_ALL} documentation)
endif()


#include(${PROJECT_SOURCE_DIR}/cmake/packaging/eProsimaPackaging.cmake)
