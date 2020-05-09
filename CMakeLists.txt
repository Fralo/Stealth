cmake_minimum_required(VERSION 3.1)
project(Stealth)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)

include_directories(lib)

# Boom executable
set(SOURCE_FILES )
add_executable(Boom src/main.cpp ${SOURCE_FILES})

target_link_libraries(Boom sfml-system sfml-window sfml-graphics GLX)

# Catch2 Unit Test
set(CATCH_INCLUDE_DIR tests)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

set(TEST_SOURCES ${SOURCE_FILES} tests/tests.cpp )
add_executable(Tests ${TEST_SOURCES})
target_link_libraries(Tests sfml-system sfml-window sfml-graphics GLX)