macro (find_pcap)
    find_path( PCAP_INCLUDE_DIR
        NAMES
        pcap.h
        PATHS
            "/usr/include/"
    )
    find_library( PCAP_LIBRARY
        NAMES
        pcap
        wpcap
        PATHS
            "/usr/lib/"
    )
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
