# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Create project
project(pp VERSION 0.1.0 LANGUAGES C CXX)

# Add subdirectories
set(SUB_DIRS app)
add_subdirectory (${SUB_DIRS})

# CTest
include(CTest)
enable_testing()

# CPack
include(CPack)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "name")
#set(CPACK_GENERATOR NSIS)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/app/templates
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/app)
