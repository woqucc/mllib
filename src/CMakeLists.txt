project  (mllib)

add_subdirs_have_cmakelists(${CMAKE_CURRENT_SOURCE_DIR})
include_all_hearers()
file(GLOB_RECURSE HEADER "*.h" "*.hpp" "*.hh")
file(GLOB_RECURSE SOURCE "*.c" "*.cpp" "*.cc")
generate_filters_by_dir(HEADER SOURCE)
add_executable(Demo ${SOURCE} ${HEADER})