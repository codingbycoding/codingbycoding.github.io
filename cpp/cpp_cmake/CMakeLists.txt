cmake_minimum_required(VERSION 2.6) 
project(hello)

set(SRC hello.cpp)

set(hello_VERSION_MAJOR 0)
set(hello_VERSION_MINOR 1)

#set(CXX_FLAGS ${CXX_FLAGS} "-m32")   

add_executable(hello ${SRC})
#set_target_properties(hello PROPERTIES COMPILE_FLAGS "-m32")
#set_target_properties(hello PROPERTIES LINK_FLAGS "-m32")



# add the install targets `make install`
set(CMAKE_INSTALL_PREFIX "/usr/local")
install(FILES "${PROJECT_SOURCE_DIR}/hello.h" DESTINATION include) 
install(TARGETS hello DESTINATION bin)


# add the test will use command `ctest` 
include(CTest)
add_test(helloRuns hello)


# build a CPack driven installer package will run command `cpack --config CPackConfig.cmake`
# or To create a source distribution you would type `cpack --config CPackSourceConfig.cmake`

include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE  
     "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${hello_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${hello_VERSION_MINOR}")
include (CPack)