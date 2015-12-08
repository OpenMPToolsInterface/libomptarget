# 
# FindOMPT.
#
# - Try to find the OpenMP Tools Interface (OMPT
# Once done this will define
#
#  LIBOMPT_FOUND - system has OMPT
#  LIBOMPT_INCLUDE_DIRS - the OMPT include directory
# 
 

FIND_PATH(OMPT_INCLUDE_DIR ompt.h
  HINTS ${LLVM_ROOT})

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OMPT DEFAULT_MSG
                                  OMPT_INCLUDE_DIR)

#MARK_AS_ADVANCED(OMPT_INCLUDE_DIR)


