cmake_minimum_required (VERSION 2.6)
project(economyvisualizer)
set (PROJECT_NAME economyvisualizer)
SET(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# The version number.
set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)

set(CMAKE_CXX_FLAGS "-Wall -Wno-write-strings")
set(CMAKE_CXX_FLAGS_DEBUG "-g -fno-inline")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui QtSql REQUIRED)
INCLUDE(${QT_USE_FILE})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
QT4_WRAP_CPP(SOURCES_MOC 
	"src/MainWindow.h"
	"src/tools/DataImport.h"
	"src/tools/DatabaseManager.h"
)

# Add gtest
#set (GTEST_DIR lib/gtest-1.6.0)
#include_directories( "${GTEST_DIR}/include" 	"${GTEST_DIR}" )	
#ADD_LIBRARY( 
#	gtest
#	${GTEST_DIR}/src/gtest-all.cc
#)


include_directories(
	"src",
	"src/tools"	)

FILE(GLOB_RECURSE SOURCES src/*.cpp)

#set (RUNTIME_OUTPUT_DIRECTORY "..")
#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
 
# add the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${SOURCES_MOC})
target_link_libraries( ${PROJECT_NAME} ${QT_LIBRARIES})
