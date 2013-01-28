project(GlobalServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++0x")

include_directories(/usr/include/mysql/ ../meteor-falls-src/src/ src/)
file(
		GLOB_RECURSE
		source_files
		src/*
		../meteor-falls-src/src/Engine/NetworkEngine/SslConnection.h
		../meteor-falls-src/src/Engine/NetworkEngine/SslConnection.cpp
		../meteor-falls-src/src/Engine/NetworkEngine/Connection.h
		../meteor-falls-src/src/Engine/NetworkEngine/Connection.cpp
)

add_executable(
		GlobalServer
		${source_files}
		)
target_link_libraries(
		GlobalServer
		boost_system
		mysqlclient
		boost_serialization
		boost_thread
		pthread
		rt
		z
		crypt
		crypto
		ssl
		)
