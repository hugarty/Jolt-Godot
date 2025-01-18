set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true **.h **.cpp)

set(SOURCES ${SOURCES})

include_directories("${PROJECT_SOURCE_DIR}/src/include/")

add_library(${BINARY} STATIC ${SOURCES})
