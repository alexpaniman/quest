add_library(quest-lib STATIC
  src/player.cpp
  src/cell.cpp
  src/game.cpp
  src/game-map.cpp)

target_include_directories(quest-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(quest-lib PUBLIC fmt axp)
