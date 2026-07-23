# ==============================================================================
# initialize_from_file utility for micro-LF
# ==============================================================================
# Include this after lf_build_generated_code() so LF_MAIN_TARGET exists.
#
# Provides: - initialize_from_file.c linked into the application - include path
# for #include "initialize_from_file.h" - LF_SOURCE_DIRECTORY /
# LF_FILE_SEPARATOR for path construction in reactions
# ==============================================================================

get_filename_component(_INIT_FROM_FILE_DIR "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)

if(NOT TARGET ${LF_MAIN_TARGET})
  message(
    FATAL_ERROR
      "initialize_from_file.cmake: target ${LF_MAIN_TARGET} is not defined. "
      "Include this file after lf_build_generated_code().")
endif()

target_sources(${LF_MAIN_TARGET}
               PRIVATE ${_INIT_FROM_FILE_DIR}/initialize_from_file.c)
target_include_directories(${LF_MAIN_TARGET} PRIVATE ${_INIT_FROM_FILE_DIR})

# Directory containing the .ulf sources (and sibling data files such as CSVs).
target_compile_definitions(
  ${LF_MAIN_TARGET}
  PRIVATE "LF_SOURCE_DIRECTORY=\"${CMAKE_CURRENT_SOURCE_DIR}/src\""
          "LF_FILE_SEPARATOR=\"/\"")
