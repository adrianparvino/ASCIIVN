#Specify the version being used aswell as the language
cmake_minimum_required(VERSION 2.6)
#Name your project here
project(ASCIIVN)

set(HEADERS
  asciibuffer.h
  asciibufferfill.h
  asciibufferssim.h
  testimage.h)
set(SOURCES
  main.c
  asciibuffer.c
  asciibufferfill.c
  asciibufferssim.c
  testimage.c)

#Sends the -std=c99 flag to the gcc compiler
add_definitions(-std=c99 -O0 -g -Wall -lmath)
#This tells CMake to main.c and name it asciivn
add_executable(asciivn main.c ${SOURCES})
