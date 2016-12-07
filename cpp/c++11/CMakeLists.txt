cmake_minimum_required(VERSION 2.6) 

set(PROJECT_NAME cpp11)
project(${PROJECT_NAME})

set(SRC c++11.cpp)

set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 1)

#set(CXX_FLAGS ${CXX_FLAGS} "-m32")   

add_executable(${PROJECT_NAME} ${SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-std=c++11")
add_definitions(-Wall)
target_link_libraries(${PROJECT_NAME} pthread)

#add_definitions(-fdiagnostics-color=always)
#set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-m32")
#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-m32")



# add the install targets `make install`
set(CMAKE_INSTALL_PREFIX "/usr/local")
#install(FILES "${PROJECT_SOURCE_DIR}/hello.h" DESTINATION include) 
install(TARGETS ${PROJECT_NAME} DESTINATION bin)


# add the test will use command `ctest` 
include(CTest)
#dd_test(helloRuns hello)


# build a CPack driven installer package will run command `cpack --config CPackConfig.cmake`
# or To create a source distribution you would type `cpack --config CPackSourceConfig.cmake`

include (InstallRequiredSystemLibraries)
#set (CPACK_RESOURCE_FILE_LICENSE  "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
include (CPack)