cmake_minimum_required(VERSION 3.1)
project(Stealth)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)

include_directories(lib)
add_library(tinyxml2 STATIC lib/tinyxml2/tinyxml2.cpp)

# Boom executable
set(SOURCE_FILES src/Stealth.cpp src/Stealth.hpp src/Enemy.cpp src/Enemy.hpp src/GameObject.hpp src/SeekStrategy.cpp src/SeekStrategy.hpp src/Strategy.hpp src/Game.cpp src/Game.hpp src/MainMenu.cpp src/MainMenu.hpp src/GameState.cpp src/GameState.hpp src/LoadScreen.cpp src/LoadScreen.hpp)
add_executable(Stealth src/main.cpp ${SOURCE_FILES})

target_link_libraries(Stealth sfml-system sfml-window sfml-graphics sfml-audio GLX tinyxml2)

# Catch2 Unit Test
set(CATCH_INCLUDE_DIR tests)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

set(TEST_SOURCES ${SOURCE_FILES} tests/tests.cpp )
add_executable(Tests ${TEST_SOURCES})
target_link_libraries(Tests sfml-system sfml-window sfml-graphics sfml-audio GLX tinyxml2)