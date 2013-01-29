project(MeteorFalls)
cmake_minimum_required(VERSION 2.8)
set(EXECUTABLE_OUTPUT_PATH ../build/)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++0x")
include_directories(src/
		libs/ozcollidelib_1-1-1/include
		libs/rapidxml
		/usr/include/CEGUI
		)
file(
		GLOB_RECURSE
		source_files
		src/*
		)
include_directories(/usr/include/OGRE /usr/local/include/)
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
		OgreMain
		OgreTerrain
		OIS
		sfml-audio
		sfml-system
		CEGUIBase
		CEGUIOgreRenderer
		boost_system
		boost_serialization
		ssl
		ozcollide
		boost_thread
		boost_unit_test_framework
		boost_filesystem
		boost_regex
		pthread
		crypto
		SkyX
		hydrax
		)

