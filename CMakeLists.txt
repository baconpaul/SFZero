cmake_minimum_required(VERSION 3.10)
project(surgeSFZero VERSION 1.0.0 LANGUAGES CXX)
#set(CMAKE_BUILD_TYPE Debug)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

set(SURGE_SFZERO_COMMON_SOURCES
    src/SFZero.cpp
)

set(SURGE_SFZERO_COMMON_INCLUDES
    src
    src/SFZero
)

add_executable(surge-sfzero-main
    ${SURGE_SFZERO_COMMON_SOURCES}
   src/main.cpp
)

target_compile_features(surge-sfzero-main
    PRIVATE
        cxx_std_17
)

target_compile_definitions(surge-sfzero-main
    PRIVATE
)

target_include_directories(surge-sfzero-main
    PRIVATE
        ${SURGE_SFZERO_COMMON_INCLUDES}
)

find_package(LibSndFile ${PACKAGE_OPTION})
if(NOT LIBSNDFILE_FOUND)
    message(WARNING "LibSndFile not installed; building without wav support")
    message(WARNING "You can 'brew install libsndfile' or 'apt-get install libsndfile1-dev'")
else()
    target_compile_definitions(surge-sfzero-main
        PRIVATE
            LIBSNDFILE=1
    )
    target_link_libraries(surge-sfzero-main ${LIBSNDFILE_LIBRARIES})
    include_directories(surge-sfzero-main ${LIBSNDFILE_INCLUDE_DIRS})
endif()

# *NIX
if (UNIX)
    target_compile_options(surge-sfzero-main
        PRIVATE
    )
endif()

# macOS
if (APPLE)
    target_compile_definitions(surge-sfzero-main
        PRIVATE
            MAC=1
    )

    target_include_directories(surge-sfzero-main
        PRIVATE
    )

    target_link_libraries(surge-sfzero-main
        "-framework ApplicationServices"
        "-framework CoreFoundation"
    )
endif()

# Linux
if (UNIX AND NOT APPLE)
    find_package(Threads REQUIRED)

    target_compile_definitions(surge-sfzero-main
        PRIVATE
            LINUX=1
    )

    target_sources(surge-sfzero-main
        PRIVATE
    )

    target_include_directories(surge-sfzero-main
        PRIVATE
    )

    target_link_libraries(surge-sfzero-main
        stdc++fs
        Threads::Threads
    )
endif()

if (WIN32)
    target_compile_definitions(surge-sfzero-main
        PRIVATE
            WINDOWS=1
            NOMINMAX=1
    )

    target_compile_options(surge-sfzero-main
        PRIVATE
            /arch:SSE2
            "/FI precompiled.h"
            /Zc:alignedNew
            /bigobj
    )

    target_link_libraries(surge-sfzero-main winmm.lib)
endif()
