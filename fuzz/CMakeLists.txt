cmake_minimum_required (VERSION 2.8)

project (fuzz)

if(DTLS)
    message(FATAL_ERROR "DTLS option is not supported." )
endif()

SET(CMAKE_C_COMPILER afl-clang)
SET(CMAKE_CXX_COMPILER afl-clang++)

include(${CMAKE_CURRENT_LIST_DIR}/../core/wakaama.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../examples/shared/shared.cmake)

add_definitions(-DLWM2M_SERVER_MODE)
add_definitions(${SHARED_DEFINITIONS} ${WAKAAMA_DEFINITIONS})

include_directories (${WAKAAMA_SOURCES_DIR} ${SHARED_INCLUDE_DIRS})

SET(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/coap_fuzz.c
    )

add_executable(${PROJECT_NAME} ${SOURCES} ${WAKAAMA_SOURCES} ${SHARED_SOURCES})

# Add WITH_LOGS to debug variant
set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS $<$<CONFIG:Debug>:WITH_LOGS>)

SOURCE_GROUP(wakaama FILES ${WAKAAMA_SOURCES})
