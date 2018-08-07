project(draw)
cmake_minimum_required(VERSION 2.6)

include_directories(
                    "/home/gordonzu/src/cpp/draw"
                    )

link_directories   (
                    )

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -std=c++17 -g -Wall -O3")

set(sources
  main.cpp
  )

add_executable(draw ${sources})

add_custom_command(TARGET draw
                   POST_BUILD
                   COMMAND "make")

add_custom_command(TARGET draw
                   POST_BUILD
#                  COMMAND valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./draw)
                   COMMAND "draw")

