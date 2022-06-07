cmake_minimum_required(VERSION 3.1)
project(NeoZibix CXX ASM-ATT)

set(CMAKE_VERBOSE_MAKEFILE ON)

#enable asm lang
ENABLE_LANGUAGE(ASM-ATT)

file(GLOB_RECURSE CPP_FILES "src/*.cpp")
file(GLOB_RECURSE ASM_FILES "src/*.s" "src/*.asm")
file(GLOB_RECURSE HPP_FILES "include/*.hpp")

set(CMAKE_CXX_COMPILER "i686-elf-g++")
set(CMAKE_ASM-ATT_COMPILER "i686-elf-as")
set(CMAKE_CXX_FLAGS "-c -g -m32 -ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti -fpermissive")
#set(CMAKE_CXX_LINK_EXECUTABLE "i686-elf-ld -T linker.ld -m elf_i386 <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_CXX_LINK_EXECUTABLE "i686-elf-gcc -T linker.ld -o <TARGET> -ffreestanding -O2 -nostdlib <OBJECTS> -lgcc")
#set(CMAKE_ASM_FLAGS "")
set(CMAKE_ASM-ATT_FLAGS "--32 -g")
#set(CMAKE_ASM-ATT_COMPILE_OBJECT "")
#todo set linker and ld flags

set(SRCS ${CPP_FILES} ${ASM_FILES})
set(HDRS ${HPP_FILES})



set(kbin_name kernel.kim)

MESSAGE(STATUS "SOURCES ARE ${SRCS}")
add_executable(${kbin_name} ${SRCS})
set_target_properties(${kbin_name} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${kbin_name} PRIVATE include)
