cmake_minimum_required(VERSION 2.8)

project(craft)

FILE(GLOB SOURCE_FILES src/*.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE OFF)

set(OBJECT_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/mainMenuTest.dir/tests)
message("-- Object files will be output to: ${OBJECT_DIR}")

set(SOURCES
    mainMenu.c
    handleMouseClick.c
   )

add_executable(
    craft
    ${SOURCE_FILES}
    deps/glew/src/glew.c
    deps/lodepng/lodepng.c
    deps/noise/noise.c
    deps/sqlite/sqlite3.c
    deps/tinycthread/tinycthread.c)

#creates a library that has the class files I'm testing so I can link later
#adds executables for each method I'm testing so they can be tested seperately
    add_executable(handleMouseClick tests/handleMouseClick.c)
    add_library(MyLib src/mainMenu.c src/mainMenu.h src/loadSaveMenu.h src/loadSaveMenu.c ) 
    add_executable(initializeMainMenu tests/initializeMainMenu.c)
    add_executable(processNormalKeys tests/processNormalKeys.c)
    add_executable(renderButtonBackground tests/renderButtonBackground.c)
    add_executable(renderLoadButtonBackground tests/renderLoadButtonBackground.c)
    add_executable(renderLoadSaveMenu tests/renderLoadSaveMenu.c)
    add_executable(renderMainMenu tests/renderMainMenu.c)
    add_executable(mainMenuTest tests/mainMenuTest.c)

# Create the gcov target. Run coverage tests with 'make gcov'
add_custom_target(gcov
    COMMAND mkdir -p coverage
    COMMAND ${CMAKE_MAKE_PROGRAM} test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
add_custom_command(TARGET gcov
    COMMAND echo "=================== GCOV ===================="
    COMMAND gcov -b ${CMAKE_SOURCE_DIR}/*.c -o ${OBJECT_DIR}
    | grep -A 5 "mainMenu.c" > CoverageSummary.tmp
    COMMAND cat CoverageSummary.tmp
    COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/coverage"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
    )
add_dependencies(gcov handleMouseClick)
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES coverage)

# Create the gcov-clean target. This cleans the build as well as generated 
# .gcda and .gcno files.
add_custom_target(scrub
COMMAND ${CMAKE_MAKE_PROGRAM} clean
COMMAND rm -f ${OBJECT_DIR}/*.gcno
COMMAND rm -f ${OBJECT_DIR}/*.gcda
WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLDUE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(craft ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
add_definitions(-std=c99 -O3)

#necessary to link the files we are testing with the executables won't compile without this
target_link_libraries(handleMouseClick MyLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(initializeMainMenu MyLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(processNormalKeys MyLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(renderButtonBackground MyLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(renderLoadButtonBackground MyLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(renderLoadSaveMenu MyLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(renderMainMenu MyLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(mainMenuTest MyLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

#creates the tests
enable_testing()
add_test( handleClickTest handleMouseClick)
set_tests_properties(handleClickTest PROPERTIES WILL_FAIL TRUE)
add_test( initializeMainMenuTest initializeMainMenu)
add_test( processNormalKeysTest processNormalKeys)
add_test( renderButtonBackgroundTest renderButtonBackground)
add_test( renderLoadButtonBackgroundTest renderLoadButtonBackground)
add_test( renderLoadSaveMenuTest renderLoadSaveMenu)
set_tests_properties(renderLoadSaveMenuTest PROPERTIES WILL_FAIL TRUE)
add_test( renderMainMenuTest renderMainMenu)
set_tests_properties(renderMainMenuTest PROPERTIES WILL_FAIL TRUE)
add_test(mainMenuTest mainMenuTest)
set_tests_properties(mainMenuTest PROPERTIES WILL_FAIL TRUE)


add_subdirectory(deps/glfw)
include_directories(deps/glew/include)
include_directories(deps/glfw/include)
include_directories(deps/lodepng)
include_directories(deps/noise)
include_directories(deps/sqlite)
include_directories(deps/tinycthread)

if(MINGW)
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
        "C:/Program Files/CURL/lib" "C:/Program Files (x86)/CURL/lib")
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH}
        "C:/Program Files/CURL/include" "C:/Program Files (x86)/CURL/include")
endif()

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

if(APPLE)
    target_link_libraries(craft glfw
        ${GLFW_LIBRARIES} ${CURL_LIBRARIES})
endif()

if(UNIX)
    target_link_libraries(craft dl glfw
        ${GLFW_LIBRARIES} ${CURL_LIBRARIES})
endif()

if(MINGW)
    target_link_libraries(craft ws2_32.lib glfw
        ${GLFW_LIBRARIES} ${CURL_LIBRARIES})
endif()
