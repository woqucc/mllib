project  (mllib)

add_subdirs_have_cmakelists(${CMAKE_CURRENT_SOURCE_DIR})
include_all_hearers()
file(GLOB_RECURSE HEADER "*.h" "*.hpp" "*.hh")
file(GLOB_RECURSE SOURCE "*.c" "*.cpp" "*.cc")
generate_filters_by_dir(HEADER SOURCE)

if(CUDA_FOUND)
	cuda_add_executable(Demo ${SOURCE} ${HEADER})
	CUDA_ADD_CUBLAS_TO_TARGET(Demo)
else(CUDA_FOUND)
	add_executable(Demo ${SOURCE} ${HEADER})
endif(CUDA_FOUND)