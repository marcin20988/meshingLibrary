file(GLOB lib_source_files
    *.C
    derived/*.C
)

add_library(meshingLib SHARED ${lib_source_files})
set_target_properties (meshingLib PROPERTIES LIBRARY_OUTPUT_DIRECTORY
    "${PROJECT_SOURCE_DIR}/lib")

