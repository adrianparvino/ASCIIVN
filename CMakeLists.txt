# lower the required version only if tested to be working
cmake_minimum_required(VERSION 3.1)
project(asciivn LANGUAGES C)

set(HEADERS
  asciibuffer.h
  asciibufferfill.h
  asciibufferssim.h
  xbmutils.h
  charset.h
  imagebuffer.h
  imagemanip.h
  imagemanip_kernel.h
  event.h
  terminal.h
  slides.h
  dialog.h
  kernels.h
  testimage.h)
set(SOURCES
  main.c
  asciibuffer.c
  asciibufferfill.c
  asciibufferssim.c
  xbmutils.c
  charset.c
  imagebuffer.c
  imagemanip.c
  imagemanip_kernel.c
  event.c
  terminal.c
  slides.c
  dialog.c
  kernels.c
  testimage.c)

find_package(PNG REQUIRED)
find_package(ZLIB REQUIRED)

add_executable(asciivn ${SOURCES})
target_include_directories(asciivn PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
set_property(TARGET asciivn PROPERTY C_STANDARD 11)
target_compile_options(asciivn PRIVATE "-O0" "-Wall" "-g3")
target_link_libraries(asciivn PRIVATE PNG::PNG ZLIB::ZLIB m)
