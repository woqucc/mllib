include_all_hearers()
FILE(GLOB_RECURSE HEADER "*.h" "*.hpp" "*.hh")
FILE(GLOB_RECURSE SOURCE "*.c" "*.cpp" "*.cc")

ADD_EXECUTABLE(demo ${HEADER} ${SOURCE})
ADD_DEPENDENCIES(demo mllib)
TARGET_LINK_LIBRARIES(demo mllib)