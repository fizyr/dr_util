cmake_minimum_required(VERSION 3.11)
project(dr_util)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)
add_link_options(LINKER:--as-needed)

find_package(Boost REQUIRED COMPONENTS filesystem date_time)

include_directories(
	"include/${PROJECT_NAME}"
	SYSTEM "${Boost_INCLUDE_DIRS}"
)

add_library(${PROJECT_NAME}
	src/environment.cpp
	src/expand.cpp
	src/file_system.cpp
	src/timestamp.cpp
	src/polynomial.cpp
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		Boost::filesystem
		Boost::date_time
)

if (BUILD_TESTING)
	enable_testing()
	find_package(GTest REQUIRED)

	# Environment test
	add_executable(${PROJECT_NAME}_test_environment test/environment.cpp)
	target_link_libraries(${PROJECT_NAME}_test_environment PRIVATE ${PROJECT_NAME} GTest::gtest GTest::gtest_main)
	add_test(NAME ${PROJECT_NAME}_test_environment COMMAND ${PROJECT_NAME}_test_environment)

	# Bitwise test
	add_executable(${PROJECT_NAME}_test_bitwise test/bitwise.cpp)
	target_link_libraries(${PROJECT_NAME}_test_bitwise PRIVATE ${PROJECT_NAME} GTest::gtest GTest::gtest_main)
	add_test(NAME ${PROJECT_NAME}_test_bitwise COMMAND ${PROJECT_NAME}_test_bitwise)

	# Button filter test
	add_executable(${PROJECT_NAME}_test_button_filter test/button_filter.cpp)
	target_link_libraries(${PROJECT_NAME}_test_button_filter PRIVATE ${PROJECT_NAME} GTest::gtest GTest::gtest_main)
	add_test(NAME ${PROJECT_NAME}_test_button_filter COMMAND ${PROJECT_NAME}_test_button_filter)

	# Expand test
	add_executable(${PROJECT_NAME}_test_expand test/expand.cpp)
	target_link_libraries(${PROJECT_NAME}_test_expand PRIVATE ${PROJECT_NAME} GTest::gtest GTest::gtest_main)
	add_test(NAME ${PROJECT_NAME}_test_expand COMMAND ${PROJECT_NAME}_test_expand)

	# Functional test
	add_executable(${PROJECT_NAME}_test_functional test/functional.cpp)
	target_link_libraries(${PROJECT_NAME}_test_functional PRIVATE ${PROJECT_NAME} GTest::gtest GTest::gtest_main)
	add_test(NAME ${PROJECT_NAME}_test_functional COMMAND ${PROJECT_NAME}_test_functional)

	# Geometry test
	add_executable(${PROJECT_NAME}_test_geometry test/geometry.cpp)
	target_link_libraries(${PROJECT_NAME}_test_geometry PRIVATE ${PROJECT_NAME} GTest::gtest GTest::gtest_main)
	add_test(NAME ${PROJECT_NAME}_test_geometry COMMAND ${PROJECT_NAME}_test_geometry)

	# Integer sequence test
	add_executable(${PROJECT_NAME}_test_integer_sequence test/integer_sequence.cpp)
	target_link_libraries(${PROJECT_NAME}_test_integer_sequence PRIVATE ${PROJECT_NAME} GTest::gtest GTest::gtest_main)
	add_test(NAME ${PROJECT_NAME}_test_integer_sequence COMMAND ${PROJECT_NAME}_test_integer_sequence)

	# Polynomial test
	add_executable(${PROJECT_NAME}_test_polynomial test/polynomial.cpp)
	target_link_libraries(${PROJECT_NAME}_test_polynomial PRIVATE ${PROJECT_NAME} GTest::gtest GTest::gtest_main)
	add_test(NAME ${PROJECT_NAME}_test_polynomial COMMAND ${PROJECT_NAME}_test_polynomial)

	# Timestamp test
	add_executable(${PROJECT_NAME}_test_timestamp test/timestamp.cpp)
	target_link_libraries(${PROJECT_NAME}_test_timestamp PRIVATE ${PROJECT_NAME} GTest::gtest GTest::gtest_main)
	add_test(NAME ${PROJECT_NAME}_test_timestamp COMMAND ${PROJECT_NAME}_test_timestamp)

	# Tuple test
	add_executable(${PROJECT_NAME}_test_tuple test/tuple.cpp)
	target_link_libraries(${PROJECT_NAME}_test_tuple PRIVATE ${PROJECT_NAME} GTest::gtest GTest::gtest_main)
	add_test(NAME ${PROJECT_NAME}_test_tuple COMMAND ${PROJECT_NAME}_test_tuple)

	# Void_t test
	add_executable(${PROJECT_NAME}_test_void_t test/void_t.cpp)
	target_link_libraries(${PROJECT_NAME}_test_void_t PRIVATE ${PROJECT_NAME} GTest::gtest GTest::gtest_main)
	add_test(NAME ${PROJECT_NAME}_test_void_t COMMAND ${PROJECT_NAME}_test_void_t)
endif()

install(
	TARGETS ${PROJECT_NAME}
	EXPORT dr_utilTargets
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
	COMPONENT runtime
)

install(
	DIRECTORY "include/${PROJECT_NAME}/"
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
	COMPONENT development
)

install(
	EXPORT dr_utilTargets
	FILE dr_utilTargets.cmake
	NAMESPACE dr_util::
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/dr_util"
)
