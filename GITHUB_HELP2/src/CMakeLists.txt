set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true **.h **.cpp)
set(SOURCES ${SOURCES})

# file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/src/joltHelloWorld/joltHelloWorld.cpp"
# "${PROJECT_SOURCE_DIR}/src/joltHelloWorld/joltHelloWorld.h")

# add_subdirectory(joltHelloWorld)

include(Jolt.cmake)

# será mesmo que o DETERMINISMO está sendo definido? E se não estiver? acho que não está.
target_compile_definitions(Jolt PUBLIC JPH_CROSS_PLATFORM_DETERMINISTIC JPH_DEBUG_RENDERER)
include_directories("${PROJECT_SOURCE_DIR}/src/include/")

add_library(${BINARY} STATIC ${SOURCES})
target_link_libraries(${BINARY} Jolt)

add_executable(main "${PROJECT_SOURCE_DIR}/src/main.cpp")
target_link_libraries(main ${BINARY})

