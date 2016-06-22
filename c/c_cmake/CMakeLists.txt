cmake_minimum_required(VERSION 2.6)
set(MY_PROJECT_NAME mytest)
project(${MY_PROJECT_NAME})

set(SRC test.c)
# The version number
set(${MY_PROJECT_NAME}_VERSION_MAJOR 0)
set(${MY_PROJECT_NAME}_VERSION_MINOR 1)
#set(C_FLAGS ${CXX_FLAGS} "-m32")   

add_executable(${MY_PROJECT_NAME} ${SRC})
#set_target_properties(${MY_PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-m32")
#set_target_properties(${MY_PROJECT_NAME} PROPERTIES LINK_FLAGS "-m32")
target_link_libraries(${MY_PROJECT_NAME} pthread)


# add the install targets
set(CMAKE_INSTALL_PREFIX "/usr/local")
install(TARGETS ${MY_PROJECT_NAME} DESTINATION bin)
install(FILES "test.h" DESTINATION include) 


# add the test will use command `ctest` 
include(CTest)
add_test(testRuns ${MY_PROJECT_NAME})


# build a CPack driven installer package will run command `cpack --config CPackConfig.cmake`
# or To create a source distribution you would type `cpack --config CPackSourceConfig.cmake`

include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE  
     "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${${MY_PROJECT_NAME}_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${${MY_PROJECT_NAME}_VERSION_MINOR}")
include (CPack)
