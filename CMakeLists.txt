cmake_minimum_required( VERSION 3.1 )

project(glfwW)

option(GLFWW_BUILD_TEST_APP "Build test application for glfw wrapper code" true)

set (CMAKE_CXX_STANDARD 17)

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

add_subdirectory(${PROJECT_SOURCE_DIR}/glfw)

file(GLOB GLFWW_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB GLFWW_HEADERS ${PROJECT_SOURCE_DIR}/*.h)

if(${GLFWW_BUILD_TEST_APP})

find_package( OpenGL REQUIRED )

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

include_directories( ${OPENGL_INCLUDE_DIRS} ${GLFWW_INCLUDE_DIR})

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

file(GLOB GLFWW_TESTAPP_SOURCES ${PROJECT_SOURCE_DIR}/testapp/*.cpp)

add_executable(glfwW-testapp WIN32 ${GLFWW_SOURCES} ${GLFWW_HEADERS} ${GLFWW_TESTAPP_SOURCES})
target_link_libraries(glfwW-testapp ${OPENGL_LIBRARIES} glfw )
if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0") 
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'GLFW-CMake-starter' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT GLFW-CMake-starter )
    endif()
endif()

endif()
