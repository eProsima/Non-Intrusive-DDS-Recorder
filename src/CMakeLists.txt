include(${PROJECT_SOURCE_DIR}/cmake/dev/set_sources.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/dev/generate_msvc_libraries.cmake)

find_package(Threads REQUIRED)

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

if(WIN32)
    set( SOURCES ${SOURCES}
        sqlite3/sqlite3.c
        sqlite3/shell.c
    )
endif()

#Definitions
add_definitions(-D${PROJECT_NAME}_SOURCE)
if(WIN32)
	add_definitions(-D_WIN32_WINNT=0x0501)
   	add_definitions(-D_XKEYCHECK_H)
endif()

#Create executable

if(THIRDPARTY)
    set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR})
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

add_executable(dds_recorder ${SOURCES})	
target_compile_definitions(dds_recorder PRIVATE SQLITE_PREPARE_V2)
if(WIN32)
    target_compile_definitions(dds_recorder PUBLIC BOOST_ALL_DYN_LINK)
endif()
target_include_directories(dds_recorder PRIVATE ${Boost_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src ${SQLITE3_INCLUDE_DIR} ${PCAP_INCLUDE_DIR})
if(WIN32)
    target_link_libraries(dds_recorder fastcdr ${Boost_LIBRARIES} ${PCAP_LIBRARY} Ws2_32)
else()
    target_link_libraries(dds_recorder fastcdr ${Boost_LIBRARIES} ${PCAP_LIBRARY} ${SQLITE3_LIBRARY})
endif()


#INSTALL STEP

install(TARGETS dds_recorder RUNTIME DESTINATION bin/)
