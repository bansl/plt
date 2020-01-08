
set(lib_shared_target shared_static)

# Generate header files from dia UML files
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../state.dia")
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../engine.dia")
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../ai.dia")

# Find all source files to compile into a library
file(GLOB_RECURSE shared_sources *.cpp)

# Build the "shared" library and add required includes
add_library(${lib_shared_target} STATIC ${shared_sources} ${jsoncpp_sources})
add_dependencies(${lib_shared_target} generate-headers)
<<<<<<< HEAD
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../client/
    ${jsoncpp_include_dir}

)
target_include_directories(${lib_shared_target} INTERFACE
=======
target_include_directories(${lib_shared_target} PUBLIC
>>>>>>> 827d39cd5a33d664c29a580ed33af91563d34193
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../client/
  )

# vim: set sw=2 sts=2 et:
