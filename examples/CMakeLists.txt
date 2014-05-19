add_executable(restriction restriction.C)
add_executable(pig pig.C)
add_executable(pig2 pig2.C)
add_executable(restriction2D restriction2D.C)
add_executable(azzopardi azzopardi.C)
add_executable(HuAngeli HuAngeli.C)

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}")

target_link_libraries(restriction meshingLib)
target_link_libraries(pig meshingLib)
target_link_libraries(pig2 meshingLib)
target_link_libraries(restriction2D meshingLib)
target_link_libraries(azzopardi meshingLib)
target_link_libraries(HuAngeli meshingLib)

set_target_properties (restriction PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_SOURCE_DIR}/bin")

set_target_properties (pig PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_SOURCE_DIR}/bin")

set_target_properties (pig2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_SOURCE_DIR}/bin")

set_target_properties (restriction2D PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_SOURCE_DIR}/bin")

set_target_properties (azzopardi PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_SOURCE_DIR}/bin")

  set_target_properties (HuAngeli PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_SOURCE_DIR}/bin")
