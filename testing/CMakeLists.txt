add_executable(primitives primitives.C)

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}")

target_link_libraries(primitives meshingLib)

set_target_properties (primitives PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_SOURCE_DIR}/bin")

