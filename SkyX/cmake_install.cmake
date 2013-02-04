<<<<<<< HEAD
# Install script for directory: /home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX
=======
# Install script for directory: /home/zequiel/software/c++/meteor-falls/SkyX
>>>>>>> 7bc6f1a4246b5de734f5ede14280fa91d76a3fef

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
<<<<<<< HEAD
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/lib/libSkyX.a")
=======
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/zequiel/software/c++/meteor-falls/SkyX/lib/libSkyX.a")
>>>>>>> 7bc6f1a4246b5de734f5ede14280fa91d76a3fef
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SkyX" TYPE FILE FILES
<<<<<<< HEAD
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/BasicController.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/MeshManager.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/GPUManager.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/Controller.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/CloudsManager.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/ColorGradient.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/VClouds/Ellipsoid.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/VClouds/GeometryBlock.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/VClouds/FastFakeRandom.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/VClouds/VClouds.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/VClouds/GeometryManager.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/VClouds/LightningManager.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/VClouds/Lightning.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/VClouds/DataManager.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/AtmosphereManager.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/Prerequisites.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/VCloudsManager.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/MoonManager.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/SkyX.h"
=======
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/BasicController.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/SkyX.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/GPUManager.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/MoonManager.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/CloudsManager.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/Prerequisites.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/MeshManager.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/VCloudsManager.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/VClouds/DataManager.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/VClouds/LightningManager.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/VClouds/Lightning.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/VClouds/FastFakeRandom.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/VClouds/GeometryBlock.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/VClouds/GeometryManager.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/VClouds/VClouds.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/VClouds/Ellipsoid.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/Controller.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/AtmosphereManager.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/ColorGradient.h"
>>>>>>> 7bc6f1a4246b5de734f5ede14280fa91d76a3fef
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SkyX/VClouds" TYPE FILE FILES
<<<<<<< HEAD
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/VClouds/Ellipsoid.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/VClouds/GeometryBlock.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/VClouds/FastFakeRandom.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/VClouds/VClouds.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/VClouds/GeometryManager.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/VClouds/LightningManager.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/VClouds/Lightning.h"
    "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/Include/VClouds/DataManager.h"
=======
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/VClouds/DataManager.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/VClouds/LightningManager.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/VClouds/Lightning.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/VClouds/FastFakeRandom.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/VClouds/GeometryBlock.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/VClouds/GeometryManager.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/VClouds/VClouds.h"
    "/home/zequiel/software/c++/meteor-falls/SkyX/Include/VClouds/Ellipsoid.h"
>>>>>>> 7bc6f1a4246b5de734f5ede14280fa91d76a3fef
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

<<<<<<< HEAD
FILE(WRITE "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/bastien/Bureau/Projet_CSII1/meteor-falls/SkyX/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
=======
FILE(WRITE "/home/zequiel/software/c++/meteor-falls/SkyX/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/zequiel/software/c++/meteor-falls/SkyX/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
>>>>>>> 7bc6f1a4246b5de734f5ede14280fa91d76a3fef
ENDFOREACH(file)
