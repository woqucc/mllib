include_all_hearers()
file(GLOB_RECURSE HEADER "*.h" "*.hpp" "*.hh")
file(GLOB_RECURSE SOURCE "*.c" "*.cpp" "*.cc")
add_executable(unit_test ${HEADER} ${SOURCE})
