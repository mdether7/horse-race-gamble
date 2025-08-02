cmake_minimum_required(VERSION 3.16)
project(HorseBet)

add_executable(${PROJECT_NAME} src/main.cpp
                               src/core.cpp
                               src/horse.cpp
                               src/bet_pool.cpp
                               src/display.cpp
                               src/player.cpp
                               src/input.cpp
                               src/rand_utils.cpp
                               src/bets.cpp )