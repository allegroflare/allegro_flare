cmake_minimum_required(VERSION 3.9)

set(LIBNAME "allegro_flare")
set(LIBVERSION 0.9.0)

project(${LIBNAME} VERSION ${LIBVERSION} DESCRIPTION "allegro but for C++")

include(GNUInstallDirs)

file(GLOB SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/allegro_flare/*.cpp
    ${PROJECT_SOURCE_DIR}/src/AllegroFlare/*.cpp
    ${PROJECT_SOURCE_DIR}/src/NcursesArt/*.cpp
    ${PROJECT_SOURCE_DIR}/include/allegro_flare/*.h
    ${PROJECT_SOURCE_DIR}/include/AllegroFlare/*.h
    ${PROJECT_SOURCE_DIR}/include/NcursesArt/*.h)
    
set(UNSUPPORTED_OS true)

IF(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(UNSUPPORTED_OS false)
    file(GLOB LINUX_SRC_FILES
         ${PROJECT_SOURCE_DIR}/src/allegro_flare/platform/linux/*.cpp)
    list (APPEND SRC_FILES ${LINUX_SRC_FILES})
ENDIF(CMAKE_SYSTEM_NAME STREQUAL "Linux")

IF(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(UNSUPPORTED_OS false)
    file(GLOB MACOS_SRC_FILES
        ${PROJECT_SOURCE_DIR}/src/allegro_flare/platform/mac_os/*.cpp)
    list (APPEND SRC_FILES ${MACOS_SRC_FILES})
ENDIF(CMAKE_SYSTEM_NAME STREQUAL "Darwin")

IF(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(UNSUPPORTED_OS false)
    file(GLOB WIN_SRC_FILES
        ${PROJECT_SOURCE_DIR}/src/allegro_flare/platform/win/*.cpp)
    list (APPEND SRC_FILES ${WIN_SRC_FILES})
ENDIF(CMAKE_SYSTEM_NAME STREQUAL "Windows")

IF(UNSUPPORTED_OS)
   file(GLOB UNSUPPORTED_SRC_FILES
        ${PROJECT_SOURCE_DIR}/src/allegro_flare/platform/generic/*.cpp)
    list (APPEND SRC_FILES ${UNSUPPORTED_SRC_FILES})
ENDIF(UNSUPPORTED_OS)
        
add_library(${LIBNAME} SHARED ${SRC_FILES})

set_target_properties(${LIBNAME} PROPERTIES
    VERSION ${LIBVERSION}
    SOVERSION 1
    PUBLIC_HEADER include/allegro_flare.h)
    
target_include_directories(${LIBNAME} PRIVATE include src)

install(TARGETS ${LIBNAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})