#Specify the version being used aswell as the language
cmake_minimum_required(VERSION 2.6)
#Name your project here
project(ASCIIVN)

#Sends the -std=c99 flag to the gcc compiler
add_definitions(-std=c99)
#This tells CMake to main.c and name it asciivn
add_executable(asciivn main.c)
