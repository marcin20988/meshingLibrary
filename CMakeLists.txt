cmake_minimum_required (VERSION 2.6)
project (meshingLib)


set(CMAKE_CXX_FLAGS "-m64 -Dlinux64 -DWM_DP") 

if (CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-local-typedefs")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast -Wnon-virtual-dtor")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")
else ()
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd327,654,819,1125,1476,1505,1572 -xSSE3 -O2 -no-prec-div  -DNoRepository")
endif()
enable_testing()

#General includes required by all code
include_directories ("${PROJECT_SOURCE_DIR}/src")
include_directories ("${PROJECT_SOURCE_DIR}/src/derived")

#We need to tell CMake to use use C files as CXX (OpenFOAM standard)
set_source_files_properties(filename.c PROPERTIES LANGUAGE CXX )

#Library
add_subdirectory(src)
add_subdirectory(testing)
add_subdirectory(examples)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        )
endif(DOXYGEN_FOUND)

