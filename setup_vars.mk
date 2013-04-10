PC_ID=TM77-PC
TM77-PC=TM77-PC

ifeq ($(PC_ID), $(TM77-PC))
CC=
CXX=
CPP=

CFLAGS=-Wall
CXXFLAGS=-Wall

C_COMPILER=D:\MinGW\bin\mingw32-gcc.exe
C_SOURCE_FILES=testc.c
C_INCLUDE_DIR_RUNTIME=D:\MinGW\include


CPP_COMPILER=D:\MinGW\bin\mingw32-g++.exe
CPP_SOURCE_FILES=testcpp.cpp
CPP_INCLUDE_DIR_RUNTIME=D:\MinGW\lib\gcc\mingw32\4.5.2\include\c++ 


BOOST_HOME=D:\TDDOWNLOAD\Software\DevelopTools\boost_1_47_0
BOOST_INCLUDE_DIR=$(BOOST_HOME)
BOOST_LIB_DIR=$(BOOST_HOME)\stage\lib
endif