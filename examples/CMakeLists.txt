add_executable(restriction restriction.C)
add_executable(pig pig.C)

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}")

target_link_libraries(restriction meshingLib)
target_link_libraries(pig meshingLib)

set_target_properties (restriction PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_SOURCE_DIR}/bin")

set_target_properties (pig PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_SOURCE_DIR}/bin")

