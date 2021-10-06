file(GLOB SOURCES
    "*.cpp"
)

set(SOURCES ${SOURCES})

add_executable(${CMAKE_PROJECT_NAME}
  ${SOURCES}
)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIRS})
target_link_libraries(${CMAKE_PROJECT_NAME} 
  PUBLIC ${PNG_LIBRARY}
)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME}_lib
  PUBLIC ${PNG_LIBRARY}
)

