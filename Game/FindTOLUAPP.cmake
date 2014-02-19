# - Try to find the tolua++
# Once done this will define
#
# TOLUAPP_FOUND - system has tolua++
# TOLUAPP_APP - the tolua++ program
# TOLUAPP_INLUDE_DIR - the tolua++ include directory
# TOLUAPP_LIBRARY - the tolua++ library

# Copyright (c) 2011, Pali Rohár <pali.rohar@gmail.com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if(TOLUAPP_INCLUDE_DIR AND TOLUAPP_LIBRARY AND TOLUAPP_APP)
        set(TOLUAPP_FOUND true)
else()
        find_path(TOLUAPP_INCLUDE_DIR tolua++.h)
        find_library(TOLUAPP_LIBRARY NAMES tolua++ tolua++5.1 toluapp)
        find_program(TOLUAPP_APP NAMES tolua++ tolua++5.1 toluapp)

        if(TOLUAPP_INCLUDE_DIR AND TOLUAPP_LIBRARY AND TOLUAPP_APP)
                set(TOLUAPP_FOUND true)
                message(STATUS "Found program tolua++: ${TOLUAPP_APP}")
                message(STATUS "Found library tolua++: ${TOLUAPP_LIBRARY}")
        else()
                set(TOLUAPP_FOUND false)
                message(FATAL_ERROR "Could not find library or program tolua++")
        endif()

        mark_as_advanced(TOLUAPP_INCLUDE_DIR AND TOLUAPP_LIBRARY AND TOLUAPP_APP)
endif()
