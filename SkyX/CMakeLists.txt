project(SkyX)
set(LIBRARY_OUTPUT_PATH lib/)
include_directories(Include)

file(
	GLOB_RECURSE
	source_files
	Source/*
	Include/*
)
file(
	GLOB_RECURSE
	headers_files
	Include/*
	)
file(
		GLOB_RECURSE
		cloud
		Include/VClouds/*
	)
add_library(
SkyX
STATIC
${source_files}
)
install (TARGETS SkyX DESTINATION lib)
install (FILES ${headers_files} DESTINATION include/SkyX)
install (FILES ${cloud} DESTINATION include/SkyX/VClouds)
