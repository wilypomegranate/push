cmake_minimum_required(VERSION 3.7)

project(push C)

set(CMAKE_C_FLAGS "-std=c99 -Werror -Wall -pedantic -Wextra")

include_directories(include)

file(GLOB SOURCES src/*.c)

add_executable(
  push
  ${SOURCES}
  )
