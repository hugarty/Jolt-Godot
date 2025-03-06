set(BINARY ${CMAKE_PROJECT_NAME}_testdebugger)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
set(SOURCES ${TEST_SOURCES})

include_directories("${PROJECT_SOURCE_DIR}/libs/src/"
    "${PROJECT_SOURCE_DIR}/testdebugger/TestFramework/")

include(TestFramework/TestFramework.cmake)
target_compile_definitions(TestFramework PUBLIC JPH_DEBUG_RENDERER JPH_ENABLE_VULKAN)

add_executable(${BINARY} main.cpp)
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME} TestFramework)