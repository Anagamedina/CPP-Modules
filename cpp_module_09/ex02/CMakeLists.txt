# =============================================================================
# ex02 — PmergeMe (programa principal + tests opcionales)
#
# CLion / CMake:
#   cmake -S cpp_module_09/ex02 -B build
#   cmake --build build
#   ctest --test-dir build
#
# Tests need GoogleTest:
#   make -C tests setup     (Makefile, clones into extern/googletest)
#   or let CMake download it automatically (FetchContent in tests/CMakeLists.txt)
# =============================================================================

cmake_minimum_required(VERSION 3.14)

project(cpp09_ex02 LANGUAGES CXX)

# --- Programa principal (subject: C++98) -------------------------------------
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(PmergeMe
	main.cpp
	PmergeMe.cpp
)

target_include_directories(PmergeMe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(PmergeMe PRIVATE
	-Wall
	-Wextra
	-Werror
)

# --- Tests unitarios (C++17 + GoogleTest local) ----------------------------
option(BUILD_TESTS "Build GoogleTest suite in tests/" ON)

if(BUILD_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()
