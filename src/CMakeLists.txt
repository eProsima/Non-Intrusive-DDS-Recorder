include(${PROJECT_SOURCE_DIR}/cmake/dev/set_sources.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/dev/generate_msvc/libraries.cmake)

set_sources(
	main.cpp
	DDSRecorder.cpp
	RTPSPacketAnalyzer.cpp
	version.cpp
	cdr/ArrayTypeCode.cpp
	cdr/ContentTypeCode.cpp
	cdr/EnumTypeCode.cpp
	cdr/MemberedTypeCode.cpp
	cdr/PrimitiveTypeCode.cpp
	cdr/SequenceTypeCode.cpp
	cdr/StringTypeCode.cpp
	cdr/StructTypeCode.cpp
	cdr/TypeCode.cpp
	cdr/TypeCodeCopy.cpp
	cdr/UnionTypeCode.cpp
	database/DynamicDataDB.cpp
	database/EntitiesDB.cpp
	database/TypeCodeDB.cpp
	idlparser/IDLParser.cc
	idlparser/IDLScanner.cc
	idlparser/UserTypeCodeProvider.cpp
	log/eProsimaLog.cpp
	reader/ipDefragmenter.cpp
	reader/pcapReader.cpp
	util/IDLPrinter.cpp
	)

#Set version


configure_file(${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/config.h.in
	${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}/config.h)

#Definitions
add_definitions(-D${PROJECT_NAME}_SOURCE)
if(WIN32)
	add_definitions(-D_WIN32_WINNT=0x0501)
endif()

#Include Boost header files
include_directories(${Boost_INCLUDE_DIR})

#Create Libraries
if(MSVC OR MSVC_IDE)
	if(EPROSIMA_INSTALLER)
		generate_msvc_libraries(i86Win32VS2013)
		generate_msvc_libraries(x64Win64VS2013)
		generate_msvc_libraries(i86Win32VS2015)
		generate_msvc_libraries(x64Win64VS2015)
	else()
		add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SOURCES})
		add_library(${PROJECT_NAME}_static STATIC ${${PROJECT_NAME}_SOURCES})
		set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME lib${PROJECT_NAME})
else()
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		add_definitions(-D__DEBUG)
	endif()
	#Create libraries
	add_library(${PROJECT_NAME} SHARED ${{PROJECT_NAME}_SOURCES})
	#Define public headers
	target_include_directories(${PROJECT_NAME} PUBLIC
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}>
		$<INSTALL_INTERFACE:include>
		)
	#Link Library to external libraries
	target_link_libraries(${PROJECT_NAME}
		${Boost_LIBRARIES}
		)
endif()

#Packaging

#Public Headers
set_public_headers_directory(${PROJECT_SOURCE_DIR}/include ${PROJECT_NAME}
	DESTINATION ${INCLUDE_INSTALL_DIR}
	COMPONENT headers
	)
#config.h headers
set_public_header(${PROJECT_BINARY_DIR}/include ${PROJECT_NAME} config.h
	DESTINATION ${INCLUDE_INSTALL_DIR}/${PROJECT_NAME}
	component headers
	)

set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ Headers" PARENT_SCOPE)
set(CPACK_COMPONENT_HEADERS_DESCRIPTION "eProsima ${PROJECT_NAME} C++ Headers" PARENT_SCOPE)

#Install sources
if(UNIX AND EPROSIMA_INSTALLER)
	install(DIRECTORY ${PROJECT_SOURCE_DIR}/src
		DESTINATION src
		COMPONENT sources
		FILES_MATCHING
		PATTERN "*.c"
		PATTERN "*.cpp"
		PATTERN "*.h"
		PATTERN "*.hpp"
		)
	install(DIRECTORY ${PROJECT_BINARY_DIR}/autotools/
		DESTINATION .
		USE_SOURCE_PERMISSIONS
		OPTIONAL
		COMPONENT sources
		)
endif()

#install libraries
install(TARGETS ${PROJECT_NAME}
	EXPORT ${PROJECT_NAME}Targets
	RUNTIME DESTINATION ${BIN_INSTALL_DIR}
	LIBRARY DESTINATION ${BIN_INSTALL_DIR}
	ARCHIVE DESTINATION ${BIN_INSTALL_DIR}
	COMPONENT libraries
	)

export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_BINARY_DIR}/cmake/config/${PROJECT_NAME}Targets.cmake)
install(EXPPORT ${PROJECT_NAME}Targets
	DESTINATION ${LIB_INSTALL_DIR}/${PROJECT_NAME}/cmake
	COMPONENT cmake
	)

set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries" PARENT_SCOPE)
set(CPACK_COMPONENT_LIBRARIES_DESCRIPTION "ePRosima ${PROJECT_NAME} Libraries" PARENT_SCORE)





