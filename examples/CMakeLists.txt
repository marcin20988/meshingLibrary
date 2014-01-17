add_executable(restriction restriction.C)
add_executable(pig pig.C)
add_executable(restriction2D restriction2D.C)

include_directories("${PROJECT_SOURCE_DIR}/library")
include_directories("${PROJECT_SOURCE_DIR}")

target_link_libraries(restriction meshingLib)
target_link_libraries(pig meshingLib)
target_link_libraries(restriction2D meshingLib)

set_target_properties (restriction PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_SOURCE_DIR}/execs")

set_target_properties (pig PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_SOURCE_DIR}/execs")

set_target_properties (restriction2D PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_SOURCE_DIR}/execs")

