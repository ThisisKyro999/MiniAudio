cmake_minimum_required(VERSION 3.16)

project(MiniAudio
    VERSION 1.0.0
    DESCRIPTION "MiniAudio C++ Library"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(MINIAUDIO_BUILD_SHARED "Build shared library" OFF)
option(MINIAUDIO_BUILD_EXAMPLES "Build examples" OFF)
option(MINIAUDIO_BUILD_TESTS "Build tests" OFF)

if(MINIAUDIO_BUILD_SHARED)
    set(BUILD_SHARED_LIBS ON)
else()
    set(BUILD_SHARED_LIBS OFF)
endif()

file(GLOB_RECURSE MINIAUDIO_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

if(MINIAUDIO_SOURCES)
    add_library(MiniAudio ${MINIAUDIO_SOURCES})

    add_library(MiniAudio::MiniAudio ALIAS MiniAudio)

    target_include_directories(MiniAudio PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
    )

    target_compile_features(MiniAudio PUBLIC cxx_std_17)
endif()
