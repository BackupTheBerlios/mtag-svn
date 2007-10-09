
PROJECT(mtag)

#if you don't want the full compiler output, remove the following line
SET(CMAKE_VERBOSE_MAKEFILE ON)

#add definitions, compiler switches, etc.
ADD_DEFINITIONS(-Wall -O2)

#list all source files here
ADD_EXECUTABLE(mtag main.cpp)

TARGET_LINK_LIBRARIES(mtag tag)

INCLUDE_DIRECTORIES(/usr/include /usr/include/taglib)
