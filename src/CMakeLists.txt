include(FetchContent)

file(GLOB SOURCES
    "*.cpp"
)

set(SOURCES ${SOURCES})

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

add_executable(${CMAKE_PROJECT_NAME}
  ${SOURCES}
)


target_link_libraries(${CMAKE_PROJECT_NAME} 
  PUBLIC ${PNG_LIBRARY}
)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME}_lib
  PUBLIC ${PNG_LIBRARY}
)

