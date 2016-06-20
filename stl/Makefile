include ../../setup_vars.mk


CPP_SRC_FILES=*.cpp
DEFAULT_TARGET_NAME=stlmain

.PHONY : all
all :
	$(CXX) $(CPP_SRC_FILES) $(CXXFLAGS) -o $(DEFAULT_TARGET_NAME)


include ../../run_target.mk

.PHONY : RUN_TARGET
RUN_TARGET :
	$(CPP_DEFAULT_TARGET_NAME)
