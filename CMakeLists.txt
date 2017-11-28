cmake_minimum_required(VERSION 3.7)
set(AssignmentNameHere raytracer)
project(${AssignmentNameHere})

set(CMAKE_CXX_STANDARD 11)
#file(GLOB DEPS_SOURCES ext/glad/src/glad.c)
set(CMAKE_CXX_FLAGS "-Wall -O3")
macro(pre_build TARGET_NAME)
    add_custom_target( ${TARGET_NAME}_PRE_BUILD ALL )
    message("STATUS" "current source dir in macro " ${CMAKE_CURRENT_SOURCE_DIR})
    add_custom_command(
            TARGET ${TARGET_NAME}_PRE_BUILD
            ${ARGN}
            PRE_BUILD
            COMMENT "${TARGET_NAME}_PRE_BUILD ..."
    )

    add_dependencies(${TARGET_NAME} ${TARGET_NAME}_PRE_BUILD)
endmacro()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin)
include_directories("include/glm/")

set(PLATFORM_LINK )
if (UNIX)
    set(PLATFORM_LINK -ldl)
endif (UNIX)



file(GLOB SRC_CPP "src/*.cpp")
file(GLOB SRC_HDR "src/*.h")
set(SOURCE_FILES main.cpp ${SRC_CPP} ${SRC_HDR})

add_executable(${AssignmentNameHere} ${SOURCE_FILES}) 
target_link_libraries(${AssignmentNameHere} ${PLATFORM_LINK})

pre_build(${AssignmentNameHere}
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/bin/Resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory   ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${CMAKE_CURRENT_SOURCE_DIR}/bin/Resources)
