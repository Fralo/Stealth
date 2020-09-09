cmake_minimum_required(VERSION 3.2)
project(Stealth)

set(CMAKE_CXX_STANDARD 20)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    #Disable optimizations for Perf
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

    # Coverage flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)

include_directories(third_party/)
add_library(tinyxml2 STATIC third_party/tinyxml2/tinyxml2.cpp)

include_directories(third_party/Catch2/single_include/)

# Pack resources into zip
set(RES_ARCHIVE stealth.dat)
file(GLOB RES_FILES "${CMAKE_CURRENT_SOURCE_DIR}/res/*")
add_custom_command(
    COMMAND ${CMAKE_COMMAND} -E tar "cf" "${CMAKE_CURRENT_BINARY_DIR}/${RES_ARCHIVE}" --format=zip -- ${RES_FILES}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/res"
    OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/${RES_ARCHIVE}"
    DEPENDS ${RES_FILES}
    COMMENT "Zipping to ${CMAKE_CURRENT_BINARY_DIR}/${RES_ARCHIVE}"
)

add_custom_target("pack-data" ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${RES_ARCHIVE}")


set(SOURCE_FILES src/Stealth.cpp src/Stealth.hpp src/Enemy.cpp src/Enemy.hpp src/GameObject.hpp src/SeekStrategy.cpp src/SeekStrategy.hpp src/HunterStrategy.cpp src/HunterStrategy.hpp src/Strategy.hpp src/Game.cpp src/Game.hpp src/MainMenu.cpp src/MainMenu.hpp src/GameState.cpp src/GameState.hpp src/LoadScreen.cpp src/LoadScreen.hpp src/TiledMap.cpp src/TiledMap.hpp src/Player.cpp src/Player.hpp src/Weapon.h src/Object.cpp src/Object.hpp src/TiledLayer.cpp src/TiledLayer.hpp src/macro.h src/GameCursor.cpp src/GameCursor.hpp src/Tile.cpp src/Tile.hpp src/Astar.cpp src/Astar.hpp src/Inventory.cpp src/Inventory.hpp src/cfg.hpp src/Animation.cpp src/Animation.hpp src/GameObject.cpp src/Direction.hpp src/BackgroundObject.hpp src/MathHelper.cpp src/MathHelper.hpp src/AdvancementManagerObserver.hpp src/KilledEnemyObserver.cpp src/KilledEnemyObserver.hpp src/StealthStatusObserver.cpp src/StealthStatusObserver.hpp src/WonGameOverScreen.cpp src/WonGameOverScreen.hpp src/GameTest.cpp src/GameTest.hpp)


add_executable(Stealth src/main.cpp ${SOURCE_FILES})
target_link_libraries(Stealth sfml-system sfml-window sfml-graphics sfml-audio GLX tinyxml2)
add_dependencies(Stealth pack-data)

# Catch2 Unit Test
set(CATCH_INCLUDE_DIR tests)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

set(TEST_SOURCES ${SOURCE_FILES} tests/tests.cpp tests/AStar_test.cpp tests/MathHelper_test.cpp tests/Game_test.cpp)
add_executable(Tests ${TEST_SOURCES})
target_link_libraries(Tests sfml-system sfml-window sfml-graphics sfml-audio GLX tinyxml2)