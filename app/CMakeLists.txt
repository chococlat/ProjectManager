# CMakeList.txt : CMake project for cmake_app, include source and define
# project specific logic here.
#


# Add source to this project's executable.
set(SRC_FILES_APP
    "main.cpp"
    "src/cli.cpp"
    "src/flib.cpp"
    "src/globals.cpp"
    "src/directory.cpp"
    )

add_executable (${PROJECT_NAME} ${SRC_FILES_APP})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()



