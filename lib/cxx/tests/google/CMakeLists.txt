#--------------------------------------------------------------------------------
# CMake version
#--------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

#--------------------------------------------------------------------------------
# Enable testing
#--------------------------------------------------------------------------------

enable_testing()

#--------------------------------------------------------------------------------
# Set dependency paths
#--------------------------------------------------------------------------------

set(GTEST_ROOT "${GLOB_GTEST_ROOT_DIR}")
set(GTEST_INC_DIR "${GTEST_ROOT}/include")
set(GTEST_SRC_DIR "${GTEST_ROOT}/src")

set(GMOCK_ROOT "${GLOB_GMOCK_ROOT_DIR}")
set(GMOCK_INC_DIR "${GMOCK_ROOT}/include")

#--------------------------------------------------------------------------------
# Include dependency headers
#--------------------------------------------------------------------------------

include_directories("${GTEST_INC_DIR}")
include_directories("${GMOCK_INC_DIR}")
include_directories("${GLOB_FT2_ROOT_DIR}/include/freetype2")
include_directories("${MODULE_UI_LIST_DIR}/lib/cxx/include")

#--------------------------------------------------------------------------------
# Find project test files
#--------------------------------------------------------------------------------

file(GLOB MODULE_UI_TEST_SOURCES "${MODULE_UI_ROOT_DIR}/lib/cxx/tests/*/*.spec.cpp")

#--------------------------------------------------------------------------------
# Build tests
#--------------------------------------------------------------------------------

add_executable(${MODULE_UI_TEST_TARGET} ${MODULE_UI_TEST_SOURCES} "${GTEST_SRC_DIR}/gtest_main.cc")
target_link_libraries(${MODULE_UI_TEST_TARGET} 
  module_ui_obj module_render_obj module_rms_obj module_core_obj 
  pthread 
  -L${GLOB_FT2_ROOT_DIR}/lib -lfreetype 
  -L${GLOB_LIBPNG_ROOT_DIR}/lib -lpng16 
  ${GLOB_GTEST_LIB_DIR}/libgtest.a 
  ${GLOB_GMOCK_LIB_DIR}/libgmock.a)
enable_cxx17(${MODULE_UI_TEST_TARGET})

add_test(NAME ${MODULE_UI_TEST_TARGET} COMMAND ${MODULE_UI_TEST_TARGET})
