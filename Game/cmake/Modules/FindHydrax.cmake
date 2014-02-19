#-------------------------------------------------------------------
# This file is part of the CMake build system for Scol
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# Locate Xavy's Hydrax Ogre plugin
# This module defines
#  Hydrax_FOUND        - True when the Hydrax include directory is found.
#  Hydrax_INCLUDE_DIRS - the Hydrax include files.
#  Hydrax_LIBRARIES    - the Hydrax library files.
#
# HYDRAX_ROOT is an environment variable that would be set for windows users.
#
# Created by Jean-François VERDON. This was influenced by the FindBoost.cmake module.

# If HYDRAX_ROOT was defined in the environment, use it. Else, search in default dependency dir.
IF(NOT HYDRAX_ROOT)
  IF("$ENV{HYDRAX_ROOT}" STREQUAL "")
    SET(HYDRAX_ROOT "$ENV{SCOL_DEPENDENCIES_PATH}/hydrax/sdk/static")
  ELSE()
    SET(HYDRAX_ROOT $ENV{HYDRAX_ROOT})
  ENDIF()
ENDIF()

SET(HYDRAX_INCLUDE_DIR_SEARCH /usr/include
	/usr/local/include
	${HYDRAX_ROOT}/include)
SET(HYDRAX_LIBRARY_SEARCH_DEBUG_DIRS
    ${HYDRAX_ROOT}/lib/Debug)
SET(HYDRAX_LIBRARY_SEARCH_RELEASE_DIRS
	${HYDRAX_ROOT}/lib/Release)

# Look for include files.
FIND_PATH(Hydrax_INCLUDE_DIR NAMES Hydrax.h PATH_SUFFIXES Hydrax PATHS ${HYDRAX_INCLUDE_DIR_SEARCH} DOC "The directory should contain Hydrax includes")
SET(Hydrax_INCLUDE_DIRS ${Hydrax_INCLUDE_DIR})

# Search for libraries files (debug mode)
FIND_LIBRARY(Hydrax_LIBRARY_DEBUG hydrax PATHS ${HYDRAX_LIBRARY_SEARCH_DEBUG_DIRS})

# Search for libraries files (release mode)
FIND_LIBRARY(Hydrax_LIBRARY_RELEASE hydrax PATHS ${HYDRAX_LIBRARY_SEARCH_RELEASE_DIRS})

# Combine debug/release libs in one variable
SET(Hydrax_LIBRARIES debug ${Hydrax_LIBRARY_DEBUG} optimized ${Hydrax_LIBRARY_RELEASE})

# Set CMake return value
set (Hydrax_FOUND "FALSE")
if(Hydrax_INCLUDE_DIRS AND Hydrax_LIBRARY_DEBUG AND Hydrax_LIBRARY_RELEASE)
   set (Hydrax_FOUND "TRUE")
endif()

