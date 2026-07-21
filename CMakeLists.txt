cmake_minimum_required(VERSION 3.20.0)

# ============================================================================
# micro-LF POSIX Template
# ============================================================================
# Build micro-LF applications for POSIX platforms (Linux, macOS).
#
# Usage: cmake -Bbuild [-DLF_MAIN=HelloPosix]
# ============================================================================

project(reactor-uc-posix)
set(PLATFORM
    "POSIX"
    CACHE STRING "Platform to target")

if(NOT DEFINED LF_MAIN)
  set(LF_MAIN "HelloPosix")
endif()

if(NOT DEFINED LOG_LEVEL)
  set(LOG_LEVEL "LF_LOG_LEVEL_WARN")
endif()

# ============================================================================
# micro-LF Configuration
# ============================================================================

if(NOT DEFINED FEDERATE)
  set(LF_MAIN_TARGET ${LF_MAIN})
else()
  set(LF_MAIN_TARGET ${LF_MAIN}_${FEDERATE})
endif()
add_executable(${LF_MAIN_TARGET})

if(${LF_MAIN_TARGET} EQUAL "MyMujocoFed")
  find_package(mujoco 2.3.7 REQUIRED PATHS ${MUJOCO_FOLDER} NO_DEFAULT_PATH)
  target_link_libraries(${LF_MAIN_TARGET} PUBLIC mujoco::mujoco)
endif()

# Check for Reactor-UC path
if(NOT DEFINED ENV{REACTOR_UC_PATH})
  message(FATAL_ERROR "REACTOR_UC_PATH environment variable not set.\n"
                      "Please set it to the path of the reactor-uc repository.")
endif()

include($ENV{REACTOR_UC_PATH}/cmake/ulfc.cmake)

# micro-LF setup
lf_setup()
lf_run_lfc(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ FILES
           ${CMAKE_CURRENT_SOURCE_DIR}/src/${LF_MAIN}.ulf)

if(NOT DEFINED FEDERATE)
  lf_build_generated_code(${LF_MAIN_TARGET}
                          ${CMAKE_CURRENT_SOURCE_DIR}/src-gen/${LF_MAIN})
else()
  lf_build_generated_code(
    ${LF_MAIN_TARGET}
    ${CMAKE_CURRENT_SOURCE_DIR}/src-gen/${LF_MAIN}/${FEDERATE})
endif()
