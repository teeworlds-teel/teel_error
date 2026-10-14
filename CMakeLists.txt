cmake_minimum_required(VERSION 3.12...3.27.4)

project(teel_error
  VERSION 0.1.0
  LANGUAGES C CXX)

include(GNUInstallDirs)

option(DOWNLOAD_GTEST "Download and compile GTest" OFF)

set(BASE_SRC
  src/error.c
)

set(LIB_PUBLIC_HEADERS_BASE
  include/teel_error/error.h
)

add_library(teel_error ${BASE_SRC})
add_library(teel::error ALIAS teel_error)

target_include_directories(teel_error PRIVATE src)
target_include_directories(teel_error
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(teel_error PROPERTIES
  VERSION   ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  POSITION_INDEPENDENT_CODE ON
)

###################################################
# testing
###################################################

if(DOWNLOAD_GTEST)
  enable_testing()
  set(INSTALL_GTEST OFF)
  set(TARGET_TESTRUNNER testrunner)

  file(GLOB TEST_SOURCES test/*.cc)
  add_executable(${TARGET_TESTRUNNER} ${TEST_SOURCES})
  set_target_properties(${TARGET_TESTRUNNER} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON)

  target_link_libraries(${TARGET_TESTRUNNER} teel::error)

  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/b66cffcd5f5d6ee34a4f96d57bf016d9a22cb023.zip
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  target_link_libraries(${TARGET_TESTRUNNER} GTest::gtest_main)

  include(GoogleTest)
  gtest_discover_tests(${TARGET_TESTRUNNER})

  add_custom_target(run_tests
    COMMAND $<TARGET_FILE:${TARGET_TESTRUNNER}> ${TESTRUNNER_ARGS}
    COMMENT "Running unit tests"
    DEPENDS ${TARGET_TESTRUNNER}
    USES_TERMINAL
  )
endif()

###################################################
# install
###################################################

install(TARGETS teel_error
  EXPORT   teel_errorTargets
  LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES ${LIB_PUBLIC_HEADERS_BASE}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/teel_error)

###################################################
# export / package config
###################################################

set(TEEL_ERROR_CMAKE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/teel_error)

install(EXPORT teel_errorTargets
  FILE        teel_errorTargets.cmake
  NAMESPACE   teel::
  DESTINATION ${TEEL_ERROR_CMAKE_DIR}
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/teel_errorConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/teel_errorConfig.cmake
  INSTALL_DESTINATION ${TEEL_ERROR_CMAKE_DIR}
)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/teel_errorConfigVersion.cmake
  VERSION       ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/teel_errorConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/teel_errorConfigVersion.cmake
  DESTINATION ${TEEL_ERROR_CMAKE_DIR}
)

###################################################
# uninstall
###################################################

configure_file(cmake/cmake_uninstall.cmake.in cmake_uninstall.cmake IMMEDIATE @ONLY)

add_custom_target(uninstall
  COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
