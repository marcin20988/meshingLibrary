add_executable(restriction restriction.C)

include_directories("${PROJECT_SOURCE_DIR}/library")
include_directories("${PROJECT_SOURCE_DIR}")

target_link_libraries(restriction meshingLib)

set_target_properties (restriction PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_SOURCE_DIR}/execs")

