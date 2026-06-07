# =============================================================================
# PmergeMe — unit tests (GoogleTest vendored en el proyecto)
#
# Origen de GTest (en este orden):
#   1) ../extern/googletest  — si ya hiciste: make -C tests setup
#   2) FetchContent          — CMake lo descarga en el primer configure/build
#
# Ejecutar tests:
#   ctest --test-dir <build-dir> -V
#   o:  ./<build-dir>/tests/pmergeme_tests
# =============================================================================

cmake_minimum_required(VERSION 3.14)

set(GTEST_VERSION v1.14.0)
set(GTEST_LOCAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../extern/googletest")

# --- Obtener GoogleTest (local o descarga automática) ------------------------
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

if(EXISTS "${GTEST_LOCAL_DIR}/CMakeLists.txt")
	message(STATUS "PmergeMe tests: using local GoogleTest at ${GTEST_LOCAL_DIR}")
	add_subdirectory(
		"${GTEST_LOCAL_DIR}"
		"${CMAKE_CURRENT_BINARY_DIR}/googletest-build"
		EXCLUDE_FROM_ALL
	)
else()
	message(STATUS "PmergeMe tests: downloading GoogleTest ${GTEST_VERSION} (FetchContent)")
	include(FetchContent)
	FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG        ${GTEST_VERSION}
		GIT_SHALLOW    TRUE
	)
	FetchContent_MakeAvailable(googletest)
endif()

find_package(Threads REQUIRED)

# --- Ejecutable de tests -----------------------------------------------------
add_executable(pmergeme_tests
	pmergeme_test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../PmergeMe.cpp
)

target_include_directories(pmergeme_tests PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/..
)

set_target_properties(pmergeme_tests PROPERTIES
	CXX_STANDARD          17
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS        OFF
)

target_compile_options(pmergeme_tests PRIVATE
	-Wall
	-Wextra
	-Werror
)

# gtest_main no: pmergeme_test.cpp define su propio main()
target_link_libraries(pmergeme_tests
	PRIVATE
		GTest::gtest
		Threads::Threads
)

# --- CTest / CLion -----------------------------------------------------------
include(GoogleTest)
gtest_discover_tests(pmergeme_tests)
