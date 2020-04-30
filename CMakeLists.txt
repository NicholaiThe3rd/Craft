cmake_minimum_required(VERSION 2.8)

project(craft)

FILE(GLOB SOURCE_FILES src/*.c)

add_executable(
    craft
    ${SOURCE_FILES}
    deps/glew/src/glew.c
    deps/lodepng/lodepng.c
    deps/noise/noise.c
    deps/sqlite/sqlite3.c
    deps/tinycthread/tinycthread.c)


    add_executable(handleMouseClick tests/handleMouseClick.c)
    add_library(MyLib src/mainMenu.c src/mainMenu.h src/loadSaveMenu.h src/loadSaveMenu.c ) 
    add_executable(initializeMainMenu tests/initializeMainMenu.c)
    add_executable(processNormalKeys tests/processNormalKeys.c)
    add_executable(renderButtonBackground tests/renderButtonBackground.c)
    add_executable(renderLoadButtonBackground tests/renderLoadButtonBackground.c)
    add_executable(renderLoadSaveMenu tests/renderLoadSaveMenu.c)
    add_executable(renderMainMenu tests/renderMainMenu.c)



find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLDUE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(craft ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
add_definitions(-std=c99 -O3)

target_link_libraries(handleMouseClick MyLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(initializeMainMenu MyLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(processNormalKeys MyLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(renderButtonBackground MyLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(renderLoadButtonBackground MyLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(renderLoadSaveMenu MyLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(renderMainMenu MyLib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

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
