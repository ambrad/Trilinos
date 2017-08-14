# Helper function
MACRO(TRIL_SET_BOOL_CACHE_VAR_FOR_CI  VAR_NAME  VAR_VALUE)
  IF ("${${VAR_NAME}}" STREQUAL "")
    MESSAGE("-- " "Setting ${VAR_NAME}='${VAR_VALUE}' by default for CI testing")
    SET(${VAR_NAME} ${VAR_VALUE} CACHE BOOL
      "Set in BasicCiTestingSettings.cmake")
  ENDIF()
ENDMACRO()

# Ignore warnings coming from TPL headers (see #1458)
TRIL_SET_BOOL_CACHE_VAR_FOR_CI(${PROJECT_NAME}_TPL_SYSTEM_INCLUDE_DIRS TRUE)

# Disable a bunch of TPLs that are not to be enabled in CI testing (since
# the SEMS env does not have them).
TRIL_SET_BOOL_CACHE_VAR_FOR_CI(TPL_ENABLE_GLM OFF)
TRIL_SET_BOOL_CACHE_VAR_FOR_CI(TPL_ENABLE_Matio OFF)
TRIL_SET_BOOL_CACHE_VAR_FOR_CI(TPL_ENABLE_X11 OFF)

# Default enable the TPLs that SEMS provides
TRIL_SET_BOOL_CACHE_VAR_FOR_CI(TPL_ENABLE_yaml-cpp ON)
TRIL_SET_BOOL_CACHE_VAR_FOR_CI(TPL_ENABLE_Pthread ON)
TRIL_SET_BOOL_CACHE_VAR_FOR_CI(TPL_ENABLE_BLAS ON)
TRIL_SET_BOOL_CACHE_VAR_FOR_CI(TPL_ENABLE_LAPACK ON)
TRIL_SET_BOOL_CACHE_VAR_FOR_CI(TPL_ENABLE_Boost ON)
TRIL_SET_BOOL_CACHE_VAR_FOR_CI(TPL_ENABLE_BoostLib ON)
IF (TPL_ENABLE_MPI)
  TRIL_SET_BOOL_CACHE_VAR_FOR_CI(TPL_ENABLE_ParMETIS ON)
ENDIF()
TRIL_SET_BOOL_CACHE_VAR_FOR_CI(TPL_ENABLE_Zlib ON)
TRIL_SET_BOOL_CACHE_VAR_FOR_CI(TPL_ENABLE_HDF5 ON)
TRIL_SET_BOOL_CACHE_VAR_FOR_CI(TPL_ENABLE_Netcdf ON)
TRIL_SET_BOOL_CACHE_VAR_FOR_CI(TPL_ENABLE_SuperLU ON)

# We want to see tracing of added tests to help in debugging
# problems.
TRIL_SET_BOOL_CACHE_VAR_FOR_CI(Trilinos_TRACE_ADD_TEST ON)

# Disable long-failing Pir test until it can be fixed (#826)
TRIL_SET_BOOL_CACHE_VAR_FOR_CI(Piro_EpetraSolver_MPI_4_DISABLE ON)

# Disable failing ROL test until it can be fixed (see #1596)
TRIL_SET_BOOL_CACHE_VAR_FOR_PT_BUILD(
  ROL_test_sol_checkAlmostSureConstraint_MPI_1_DISABLE ON)

# Disable Intrepid2 test that fails to build (see #1600)
TRIL_SET_BOOL_CACHE_VAR_FOR_PT_BUILD(
  Intrepid2_refactor_unit-test_Orientation_Serial_Test_OrientationToolsCoeffMatrix_EXE_DISABLE
  ON )
TRIL_SET_BOOL_CACHE_VAR_FOR_PT_BUILD(
  Intrepid2_refactor_unit-test_Orientation_Serial_Test_OrientationToolsCoeffMatrix_MPI_1_DISABLE
  ON )
