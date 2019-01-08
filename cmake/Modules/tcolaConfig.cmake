INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_TCOLA tcola)

FIND_PATH(
    TCOLA_INCLUDE_DIRS
    NAMES tcola/api.h
    HINTS $ENV{TCOLA_DIR}/include
        ${PC_TCOLA_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    TCOLA_LIBRARIES
    NAMES gnuradio-tcola
    HINTS $ENV{TCOLA_DIR}/lib
        ${PC_TCOLA_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TCOLA DEFAULT_MSG TCOLA_LIBRARIES TCOLA_INCLUDE_DIRS)
MARK_AS_ADVANCED(TCOLA_LIBRARIES TCOLA_INCLUDE_DIRS)

