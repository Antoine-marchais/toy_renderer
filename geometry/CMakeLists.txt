set(MODULE_NAME geometry)

# Configure module libraries and executables

file(GLOB SOURCES src/*.cpp include/*.hpp)

add_library(${MODULE_NAME} ${SOURCES})
target_include_directories(${MODULE_NAME} PUBLIC include)
target_link_libraries(${MODULE_NAME} PUBLIC gtest)


# Configure module tests

set(TEST_BINARY ${MODULE_NAME}_test)

file(GLOB TEST_SOURCES tests/*.cpp)

add_executable(${TEST_BINARY} ${TEST_SOURCES})
target_link_libraries(${TEST_BINARY} PUBLIC ${MODULE_NAME} gtest)

gtest_discover_tests(${TEST_BINARY})
