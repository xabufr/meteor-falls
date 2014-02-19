find_package(PkgConfig)
pkg_check_modules(PC_PAGED_GEOMETRY QUIET PagedGeometry)

set(PAGED_GEOMETRY_DEFINITIONS ${PC_PAGED_GEOMETRY_CFLAGS_OTHER})

find_path(PAGED_GEOMETRY_INCLUDE_DIR PagedGeometry/PagedGeometry.h
          HINTS ${PC_PAGED_GEOMETRY_INCLUDEDIR} ${PC_PAGED_GEOMETRY_INCLUDE_DIRS}
          PATH_SUFFIXES PagedGeometry )

find_library(PAGED_GEOMETRY_LIBRARY NAMES PagedGeometry libPagedGeometry
             HINTS ${PC_PAGED_GEOMETRY_LIBDIR} ${PC_PAGED_GEOMETRY_LIBRARY_DIRS} )

set(PAGED_GEOMETRY_LIBRARIES ${PAGED_GEOMETRY_LIBRARY} )
set(PAGED_GEOMETRY_INCLUDE_DIRS ${PAGED_GEOMETRY_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set PAGED_GEOMETRY_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(PagedGeometry  DEFAULT_MSG
                                  PAGED_GEOMETRY_LIBRARY PAGED_GEOMETRY_INCLUDE_DIR)

mark_as_advanced(PAGED_GEOMETRY_INCLUDE_DIR PAGED_GEOMETRY_LIBRARY )