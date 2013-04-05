default_target : all

define TM77-PC
abc
endef

#PC_ID=TM77-PC
PC_ID=TM77_PC_i7

TM77_PC=TM77_PC
TM77_PC_i7=TM77_PC_i7


ifeq ($(PC_ID), $(TM77_PC))

CPP_COMPILER=D:\MinGW\bin\mingw32-g++.exe
CPP_SOURCE_FILES=cpp.cpp
CPP_INCLUDE_DIR_RUNTIME=D:\MinGW\lib\gcc\mingw32\4.5.2\include\c++ 

CPP_DEFAULT_TARGET_NAME=cpp

BOOST_HOME=D:\TDDOWNLOAD\Software\DevelopTools\boost_1_47_0
BOOST_INCLUDE_DIR=$(BOOST_HOME)
BOOST_LIB_DIR=$(BOOST_HOME)\stage\lib
endif


ifeq ($(PC_ID), $(TM77_PC_i7))

CPP_COMPILER=D:\Program Files (x86)\MinGW\bin\mingw32-g++.exe
CPP_SOURCE_FILES=cpp.cpp
CPP_INCLUDE_DIR_RUNTIME=D:\Program Files (x86)\MinGW\lib\gcc\mingw32\4.5.2\include\c++ 

CPP_DEFAULT_TARGET_NAME=cpp

BOOST_HOME=D:\Source\boost_1_47_0
BOOST_INCLUDE_DIR=$(BOOST_HOME)
BOOST_LIB_DIR=$(BOOST_HOME)\stage\lib
endif

BOOST_LIB_NAMES=


all : TARGET_CPP


TARGET_CPP :
	$(CPP_COMPILER) $(CPP_SOURCE_FILES) -I$(CPP_INCLUDE_DIR_RUNTIME) -I$(BOOST_INCLUDE_DIR) -o ${CPP_DEFAULT_TARGET_NAME}	
