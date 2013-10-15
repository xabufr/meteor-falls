project(MeteorFalls)
cmake_minimum_required(VERSION 2.8)
set(EXECUTABLE_OUTPUT_PATH ../build/)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++0x -ggdb -msse")
include_directories(src/
		libs/ozcollidelib_1-1-1/include
		libs/rapidxml
		/usr/include/CEGUI
		/usr/include/bullet
		/usr/include/cegui-0/CEGUI
		/usr/include/cegui-0
		)
file(
		GLOB_RECURSE
		source_files
		src/*
		)
include_directories(/usr/include/OGRE /usr/local/include/ /usr/local/include/OGRE/)
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

target_link_libraries(meteor-falls
	#ogre libraries
		OgreMain
		OgreTerrain
		OIS
		SkyX
		hydrax
		PagedGeometry
		#SFML
		sfml-audio
		sfml-system
		#CEGUI
		CEGUIBase-0
		CEGUILuaScriptModule-0
		CEGUIOgreRenderer-0
		#BOOST
		boost_system
		boost_serialization
		boost_thread
		boost_unit_test_framework
		boost_filesystem
		boost_regex
		pthread
		#SSL
		ssl
		crypto
		tolua++
		#lua5.1
       	lua
		PagedGeometry
		BulletDynamics
		#BtOgre
		#bullet libraries
		#BtOgre
		BulletDynamics
		BulletCollision
		LinearMath
		)

