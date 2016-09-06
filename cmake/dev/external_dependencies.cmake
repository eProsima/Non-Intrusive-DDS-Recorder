macro (find_pcap)
    find_path( PCAP_INCLUDE_DIR
        NAMES
        pcap.h
        PATHS
        "/usr/include/"
        "${WINPCAP_ROOT}/Include"
    )
if(WIN32)
    if(WINPCAP_ROOT)
        if(CMAKE_CL_64)
            set(WINPCAP_LIBRARY_ROOT "${WINPCAP_ROOT}/Lib/x64")
        else()
            set(WINPCAP_LIBRARY_ROOT "${WINPCAP_ROOT}/Lib")
        endif()
        find_library( PCAP_PACKET_LIBRARY Packet
            PATHS
            "${WINPCAP_LIBRARY_ROOT}"
            )
        find_library( PCAP_WPCAP_LIBRARY wpcap
            PATHS
            "${WINPCAP_LIBRARY_ROOT}"
            )
        if(PCAP_PACKET_LIBRARY AND PCAP_WPCAP_LIBRARY)
            set(PCAP_LIBRARY ${PCAP_PACKET_LIBRARY} ${PCAP_WPCAP_LIBRARY})
        endif()
    endif()
else()
    find_library( PCAP_LIBRARY
        NAMES
        pcap
        PATHS
        "/usr/lib/"
        "${WINPCAP_ROOT}"
    )
endif()
    if(NOT PCAP_INCLUDE_DIR)
        set(PCAP_FOUND FALSE)
        message(STATUS "pcap not found!")
    else()
        set(PCAP_FOUND TRUE)
        message(STATUS "Found pcap @ ${PCAP_INCLUDE_DIR}, libs ${PCAP_LIBRARY}")
    endif()
endmacro(find_pcap)

macro (find_sqlite3)
    find_path( SQLITE3_INCLUDE_DIR
        NAMES
        sqlite3.h
        PATHS
            "/usr/include/"
    )
    find_library( SQLITE3_LIBRARY
        NAMES
        sqlite3
        PATHS
            "/usr/lib/"
    )
    if(NOT SQLITE3_INCLUDE_DIR)
        set(SQLITE3_FOUND FALSE)
        message(STATUS "sqlite3 not found!")
    else()
        set(SQLITE3_FOUND TRUE)
        message(STATUS "Found sqlite3 @ ${SQLITE3_INCLUDE_DIR}, libs ${SQLITE3_LIBRARY}")
    endif()
endmacro(find_sqlite3)
