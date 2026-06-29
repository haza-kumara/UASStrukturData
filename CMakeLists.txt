# ==============================================================
# CMakeLists.txt — Contact Manager CLI
# Platform    : Windows (MinGW/MSVC), Linux (GCC), macOS (Clang)
# Deskripsi   : Project CLI sederhana, tidak ada dependensi GUI.
# ==============================================================

cmake_minimum_required(VERSION 3.16)

project(ContactManager
    VERSION     1.0.0
    DESCRIPTION "Sistem Manajemen Kontak — CLI Struktur Data"
    LANGUAGES   CXX
)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

# ==============================================================
# LIBRARY: contact_lib
# Berisi implementasi struct Contact dan Linked List.
# ==============================================================
add_library(contact_lib STATIC
    src/Contact.cpp
    src/LinkedList.cpp
)
target_include_directories(contact_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ==============================================================
# EXECUTABLE: contact_manager
# ==============================================================
add_executable(contact_manager
    main.cpp
)
target_link_libraries(contact_manager PRIVATE contact_lib)

# --------------------------------------------------------------
# Warning flags
# --------------------------------------------------------------
if(MSVC)
    target_compile_options(contact_manager PRIVATE /W4)
    target_compile_options(contact_lib     PRIVATE /W4)
else()
    target_compile_options(contact_manager PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(contact_lib     PRIVATE -Wall -Wextra -Wpedantic)
endif()

# --------------------------------------------------------------
# Default build type
# --------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Build type : ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler   : ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "System     : ${CMAKE_SYSTEM_NAME}")