project(UDP_Packt_Bouncer)
cmake_minimum_required(VERSION 2.8.1)

#add cmake module to be able to find glib (liglib2)
set(CMAKE_MODULE_PATH
${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#find glib
FIND_PACKAGE(GLIB REQUIRED)

#definition of common header and source files
set (COMMON_HEADERS
    src/Meteron_Link_Test_Common.h
    src/posix_periodic.h
    src/Sender_Class.h
    src/Receiver_Class.h
)

set (COMMON_SOURCES
    src/posix_periodic.cpp
    src/Sender_Class.cpp
    src/Receiver_Class.cpp
)

#external includes
include_directories(${GLIB_INCLUDE_DIRS})

#executable for the boncer
set (BOUNCER_HEADERS
    ${COMMON_HEADERS}
    src/ASAP_Bouncer_Main.h
)

set (BOUNCER_SOURCES
    ${COMMON_SOURCES}
    src/ASAP_Bouncer_Main.cpp
)

add_executable(Bouncer ${BOUNCER_HEADERS} ${BOUNCER_SOURCES})
target_link_libraries(Bouncer ${GLIB_LIBRARIES} pthread)


#executable for the sender
set (SENDER_HEADERS
    ${COMMON_HEADERS}
    src/Measurement_Sender_Main.h
)

set (SENDER_SOURCES
    ${COMMON_SOURCES}
    src/Measurement_Sender_Main.cpp
)

add_executable(Sender ${SENDER_HEADERS} ${SENDER_SOURCES})
target_link_libraries(Sender ${GLIB_LIBRARIES} pthread)
