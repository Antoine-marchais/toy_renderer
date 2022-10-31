set(MODULE_NAME renderer)

# Configure module dependencies

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

FetchContent_Declare(
  pngpp
  URL http://download.savannah.nongnu.org/releases/pngpp/png++-0.2.9.tar.gz
)

FetchContent_GetProperties(pngpp)
if(NOT pngpp_POPULATED)
  FetchContent_Populate(pngpp)
  message(STATUS "moving png++ headers to build include directory")
  execute_process(COMMAND make --directory=${pngpp_SOURCE_DIR} install-headers PREFIX=${CMAKE_BINARY_DIR})
endif()


# Configure module libraries and executables

file(GLOB SOURCES src/*.cpp include/*.hpp)

add_library(${MODULE_NAME} ${SOURCES})
target_include_directories(${MODULE_NAME} PUBLIC include)
target_link_libraries(${MODULE_NAME} PUBLIC geometry ${PNG_LIBRARY})

add_executable(${MODULE_NAME}_bin ${SOURCES})
target_include_directories(${MODULE_NAME}_bin PUBLIC include)
target_link_libraries(${MODULE_NAME}_bin PUBLIC geometry ${PNG_LIBRARY})


# Configure module tests

set(TEST_BINARY ${MODULE_NAME}_test)

file(GLOB TEST_SOURCES tests/*.cpp)

add_executable(${TEST_BINARY} ${TEST_SOURCES})
target_link_libraries(${TEST_BINARY} PUBLIC ${MODULE_NAME} gtest geometry)

gtest_discover_tests(${TEST_BINARY})
