include(${PROJECT_SOURCE_DIR}/cmake/dev/set_sources.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/dev/generate_msvc_libraries.cmake)

find_package(Threads REQUIRED)

set(SOURCES
    main.cpp
    DDSRecorder.cpp
    RTPSPacketAnalyzer.cpp
    TypeStore.cpp
    version.cpp
    database/CaptureDB.cpp
    database/Endpoint.cpp
    database/MonitorDB.cpp
    database/TopicDataDB.cpp
    database/TopicsDB.cpp
    log/eProsimaLog.cpp
    reader/ipDefragmenter.cpp
    reader/pcapReader.cpp
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

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE SQLITE_PREPARE_V2)
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC BOOST_ALL_DYN_LINK)
endif()
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src ${SQLITE3_INCLUDE_DIR} ${PCAP_INCLUDE_DIR})
if(WIN32)
    target_link_libraries(${PROJECT_NAME} fastdds fastcdr ${Boost_LIBRARIES} ${PCAP_LIBRARY} Ws2_32)
else()
    target_link_libraries(${PROJECT_NAME} fastdds fastcdr ${Boost_LIBRARIES} ${PCAP_LIBRARY} ${SQLITE3_LIBRARY})
endif()


#INSTALL STEP

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${BIN_INSTALL_DIR}
    COMPONENT binaries
    )

string(TOUPPER "${MSVC_ARCH}" MSVC_ARCH_UPPER)
set(CPACK_COMPONENT_BINARIES_DISPLAY_NAME "Binaries" PARENT_SCOPE)
set(CPACK_COMPONENT_BINARIES_DESCRIPTION "eProsima ${PROJECT_NAME_LARGE} binaries for platform ${MSVC_ARCH}" PARENT_SCOPE)
