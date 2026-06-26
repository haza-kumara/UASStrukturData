# ==============================================================
# CMakeLists.txt — Contact Manager dengan Dear ImGui GUI
# Platform : Windows (MinGW/MSVC), Linux (GCC), macOS (Clang)
# Library  : Dear ImGui + GLFW diunduh otomatis via FetchContent
#            OpenGL sudah tersedia di semua OS, tidak perlu install
# ==============================================================

cmake_minimum_required(VERSION 3.16)

project(ContactManager
    VERSION     1.0.0
    DESCRIPTION "Sistem Manajemen Kontak — GUI dengan Dear ImGui"
    LANGUAGES   CXX
)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

# --------------------------------------------------------------
# FetchContent: unduh dependency secara otomatis saat cmake
# dijalankan. Tidak perlu install apa pun secara manual.
# --------------------------------------------------------------
include(FetchContent)

# --- GLFW (windowing + input, lintas OS) ----------------------
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4          # versi stabil
    GIT_SHALLOW    TRUE         # hanya ambil commit terbaru (lebih cepat)
)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# --- Dear ImGui -----------------------------------------------
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.91.1      # versi stabil terbaru
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(imgui)

# ImGui tidak punya CMakeLists.txt sendiri — kita buat library
# manual dari source-nya. Sertakan backend GLFW + OpenGL3.
add_library(imgui_lib STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui_lib PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui_lib PUBLIC glfw)

# --------------------------------------------------------------
# OpenGL — sudah tersedia di OS, tinggal cari pakai CMake
# --------------------------------------------------------------
find_package(OpenGL REQUIRED)

# ==============================================================
# LIBRARY: contact_lib (struktur data proyek)
# Tidak ada perubahan dari versi sebelumnya.
# ==============================================================
add_library(contact_lib STATIC
    src/Contact.cpp
    src/LinkedList.cpp
    src/BST.cpp
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

target_link_libraries(contact_manager PRIVATE
    contact_lib       # struktur data kita
    imgui_lib         # Dear ImGui + backend GLFW/OpenGL3
    OpenGL::GL        # OpenGL sistem
)

# --------------------------------------------------------------
# Warning flags lintas kompiler
# --------------------------------------------------------------
if(MSVC)
    target_compile_options(contact_manager PRIVATE /W4)
    target_compile_options(contact_lib     PRIVATE /W4)
else()
    target_compile_options(contact_manager PRIVATE -Wall -Wextra)
    target_compile_options(contact_lib     PRIVATE -Wall -Wextra)
endif()

# --------------------------------------------------------------
# macOS: perlu link framework tambahan untuk OpenGL + Cocoa
# --------------------------------------------------------------
if(APPLE)
    target_link_libraries(contact_manager PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
endif()

# --------------------------------------------------------------
# Default build type
# --------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Build type : ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler   : ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "System     : ${CMAKE_SYSTEM_NAME}")