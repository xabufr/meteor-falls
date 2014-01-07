project(MeteorFalls)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(EXECUTABLE_OUTPUT_PATH build/)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++0x -ggdb")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(OGRE REQUIRED COMPONENTS Terrain)
find_package(OIS REQUIRED)
find_package(CEGUI REQUIRED)
find_package(Boost REQUIRED REQUIRED COMPONENTS system filesystem serialization thread regex unit_test_framework )
find_package(Bullet REQUIRED)
find_package(Threads REQUIRED)
find_package(Tolua++ REQUIRED)
find_package(Lua51 REQUIRED)
find_package(SkyX REQUIRED)
find_package(Hydrax REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(SFML REQUIRED COMPONENTS audio system)
find_package(OgrePaged REQUIRED)


include_directories(src/ )
file(
        GLOB_RECURSE
        source_files
        src/*
        )
include_directories(${OGRE_INCLUDE_DIR} "${OGRE_INCLUDE_DIR}/..")
include_directories(${OIS_INCLUDE_DIR})
include_directories(${CEGUI_INCLUDE_DIR}/..)
include_directories(${Boost_INCLUDE_DIR})
include_directories(${BULLET_INCLUDE_DIR})
include_directories(${TOLUA++_INCLUDE_DIR})
include_directories(${LUA_INCLUDE_DIR})
include_directories(${SkyX_INCLUDE_DIR})
include_directories(${Hydrax_INCLUDE_DIR})
include_directories(${OPENSSL_INCLUDE_DIR})
include_directories(${SFML_INCLUDE_DIR})
include_directories(${PAGED_GEOMETRY_INCLUDE_DIR})

file(
        GLOB
        server_files
        ../GlobalServer/src/Admin.cpp
        ../GlobalServer/src/Admin.h
        ../GlobalServer/src/Player.cpp
        ../GlobalServer/src/Player.h
        ../GlobalServer/src/Server.cpp
        ../GlobalServer/src/Server.h
        )
add_executable(
        meteor-falls
        ${source_files}
        ${server_files}
        )
if(UNIX)
    find_package(X11 REQUIRED)
    include_directories(${X11_X11_INCLUDE_PATH})
    target_link_libraries(meteor-falls
        ${X11_X11_LIB})
endif()

target_link_libraries(meteor-falls
    ${OGRE_LIBRARIES}
    ${OGRE_Terrain_LIBRARIES}
    ${OIS_LIBRARIES}
    ${SFML_LIBRARIES}
    ${Hydrax_LIBRARIES}
    ${SkyX_LIBRARIES}
    ${CEGUI_LIBRARIES}
    ${CEGUI_OgreRenderer_LIBRARIES}
    ${CEGUI_LuaScriptModule_LIBRARIES}
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${OPENSSL_LIBRARIES}
    ${PAGED_GEOMETRY_LIBRARIES}
    ${BULLET_LIBRARIES}
    ${LUA_LIBRARIES}
    ${TOLUA++_LIBRARY}
    )

