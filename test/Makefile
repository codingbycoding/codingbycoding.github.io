default_target : all

.PHONY : default_target

define TM77-PC
abc
endef

PC_ID=TM77-PC
TM77-PC=TM77-PC

ifeq ($(PC_ID), $(TM77-PC))
CC=
CXX=
CPP=

CFLAGS=-Wall
CXXFLAGS=-Wall

#C_COMPILER=D:\MinGW\bin\mingw32-gcc.exe
C_COMPILER=D:\msysgit\msysgit\mingw\bin\mingw32-gcc.exe
C_SOURCE_FILES=testc.c
C_INCLUDE_DIR_RUNTIME=D:\MinGW\include

C_DEFAULT_TARGET_NAME=testc


CPP_COMPILER=D:\MinGW\bin\mingw32-g++.exe
CPP_SOURCE_FILES=testcpp.cpp
CPP_INCLUDE_DIR_RUNTIME=D:\MinGW\lib\gcc\mingw32\4.5.2\include\c++ 

CPP_DEFAULT_TARGET_NAME=testcpp

BOOST_HOME=D:\TDDOWNLOAD\Software\DevelopTools\boost_1_47_0
BOOST_INCLUDE_DIR=$(BOOST_HOME)
BOOST_LIB_DIR=$(BOOST_HOME)\stage\lib
endif

BOOST_LIB_NAMES=


all : TARGET_C TARGET_CPP


TARGET_C :
	$(C_COMPILER) $(C_SOURCE_FILES) -I$(C_INCLUDE_DIR_RUNTIME) -o ${C_DEFAULT_TARGET_NAME}	


TARGET_CPP :
	$(CPP_COMPILER) $(CPP_SOURCE_FILES) -I$(CPP_INCLUDE_DIR_RUNTIME) -I$(BOOST_INCLUDE_DIR) -o ${CPP_DEFAULT_TARGET_NAME}	


RUN_TARGET :
	$(CPP_DEFAULT_TARGET_NAME)

