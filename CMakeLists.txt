cmake_minimum_required(VERSION 3.16)
project(HorseBet)

add_executable(${PROJECT_NAME} src/main.cpp
                               src/core.cpp
                               src/race.cpp
                               src/horses.cpp
                               src/bets.cpp )