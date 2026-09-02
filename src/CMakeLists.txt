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
    database/MonitorDB.cpp
    writer/McapRecorder.cpp
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
    set(SOURCES ${SOURCES}
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
target_compile_definitions(dds_recorder PRIVATE SQLITE_PREPARE_V2
    DDSRECORDER_VERSION_STRING="${PROJECT_VERSION}")
# writer/McapRecorder.cpp is always compiled; without this definition it provides the same
# class with a disabled implementation, so no other source needs a conditional.
if(MCAP_SUPPORT_ENABLED)
    target_compile_definitions(dds_recorder PRIVATE MCAP_SUPPORT)
endif()
if(WIN32)
    target_compile_definitions(dds_recorder PUBLIC BOOST_ALL_DYN_LINK)
endif()
# src/idlparser holds the vendored FlexLexer.h. The flex-generated scanner includes it with angle
# brackets, so this directory has to be on the include path for the build to work without flex
# installed.
target_include_directories(dds_recorder PRIVATE ${Boost_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/src/idlparser ${SQLITE3_INCLUDE_DIR} ${PCAP_INCLUDE_DIR})
if(MCAP_SUPPORT_ENABLED)
    target_include_directories(dds_recorder PRIVATE ${PROJECT_SOURCE_DIR}/thirdparty/mcap ${LZ4_INCLUDE_DIR} ${ZSTD_INCLUDE_DIR})
endif()
if(WIN32)
    target_link_libraries(dds_recorder fastcdr ${Boost_LIBRARIES} ${PCAP_LIBRARY} Ws2_32)
else()
    target_link_libraries(dds_recorder fastcdr ${Boost_LIBRARIES} ${PCAP_LIBRARY} ${SQLITE3_LIBRARY})
endif()
if(MCAP_SUPPORT_ENABLED)
    target_link_libraries(dds_recorder ${LZ4_LIBRARY} ${ZSTD_LIBRARY})
endif()


#INSTALL STEP

install(TARGETS dds_recorder
    RUNTIME DESTINATION ${BIN_INSTALL_DIR}
    COMPONENT binaries
    )

string(TOUPPER "${MSVC_ARCH}" MSVC_ARCH_UPPER)
set(CPACK_COMPONENT_BINARIES_DISPLAY_NAME "Binaries" PARENT_SCOPE)
set(CPACK_COMPONENT_BINARIES_DESCRIPTION "eProsima ${PROJECT_NAME_LARGE} binaries for platform ${MSVC_ARCH}" PARENT_SCOPE)
