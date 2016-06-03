include(${PROJECT_SOURCE_DIR}/cmake/dev/set_sources.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/dev/generate_msvc_libraries.cmake)


set( SOURCES
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



#Definitions
add_definitions(-D${PROJECT_NAME}_SOURCE)
if(WIN32)
	add_definitions(-D_WIN32_WINNT=0x0501)
endif()

#Create executable
	add_executable(dds_recorder ${SOURCES})	
	target_include_directories(dds_recorder PRIVATE ${Boost_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/thirdparty/eprosima-common-code ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src)
	target_link_libraries(dds_recorder fastcdr sqlite3 pcap ${Boost_LIBRARIES} -lpcap -lsqlite3)
	install(TARGETS dds_recorder RUNTIME DESTINATION bin/)


#Packaging

#Public Headers
set_public_headers_directory(${PROJECT_SOURCE_DIR}/include ${PROJECT_NAME}
	DESTINATION ${INCLUDE_INSTALL_DIR}
	COMPONENT headers
	)
#config.h headers
set_public_header(${PROJECT_BINARY_DIR}/include ${PROJECT_NAME} config.h
	DESTINATION ${INCLUDE_INSTALL_DIR}/${PROJECT_NAME}
	COMPONENT headers
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



