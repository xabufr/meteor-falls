#-------------------------------------------------------------------
# This file is part of the CMake build system for Scol
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# Locate Xavy's SkyX Ogre plugin
# This module defines
#  SkyX_FOUND        - True when the SkyX include directory is found.
#  SkyX_INCLUDE_DIRS - the SkyX include files.
#  SkyX_LIBRARIES    - the SkyX library files.
#
# SKYX_ROOT is an environment variable that would be set for windows users.
#
# Created by Jean-François VERDON. This was influenced by the FindBoost.cmake module.

# If SKYX_ROOT was defined in the environment, use it. Else, search in default dependency dir.
IF(NOT SKYX_ROOT)
  IF("$ENV{SKYX_ROOT}" STREQUAL "")
    SET(SKYX_ROOT "$ENV{SCOL_DEPENDENCIES_PATH}/Skyx/sdk/static")
  ELSE()
    SET(SKYX_ROOT $ENV{SKYX_ROOT})
  ENDIF()
ENDIF()

SET(SKYX_INCLUDE_DIR_SEARCH /usr/include
	/usr/local/include
	${SKYX_ROOT}/include)
SET(SKYX_LIBRARY_SEARCH_DEBUG_DIRS
    ${SKYX_ROOT}/lib/Debug)
SET(SKYX_LIBRARY_SEARCH_RELEASE_DIRS
	${SKYX_ROOT}/lib/Release)

# Look for include files.
FIND_PATH(SkyX_INCLUDE_DIR NAMES SkyX.h PATH_SUFFIXES SkyX PATHS ${SKYX_INCLUDE_DIR_SEARCH} DOC "The directory should contain SkyX includes")
SET(SkyX_INCLUDE_DIRS ${SkyX_INCLUDE_DIR})

# Search for libraries files (debug mode)
FIND_LIBRARY(SkyX_LIBRARY_DEBUG SkyX PATHS ${SKYX_LIBRARY_SEARCH_DEBUG_DIRS})

# Search for libraries files (release mode)
FIND_LIBRARY(SkyX_LIBRARY_RELEASE SkyX PATHS ${SKYX_LIBRARY_SEARCH_RELEASE_DIRS})

# Combine debug/release libs in one variable
SET(SkyX_LIBRARIES debug ${SkyX_LIBRARY_DEBUG} optimized ${SkyX_LIBRARY_RELEASE})

# Set CMake return value
set (SkyX_FOUND "FALSE")
if(SkyX_INCLUDE_DIRS AND SkyX_LIBRARY_DEBUG AND SkyX_LIBRARY_RELEASE)
   set (SkyX_FOUND "TRUE")
endif()


