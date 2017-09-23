CMAKE_MINIMUM_REQUIRED(VERSION 3.3)
SET(CMAKE_CXX_STANDARD 11)
#自动加入将带有CMakeLists.txt的子目录
MACRO(add_subdirs_have_cmakelists curdir)
	#列出所有目录
	FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
	SET(dirlist "")
	#遍历目录
	FOREACH(child ${children})
		#如果目录中存在CmakeLists.txt，则将其加入子目录列表
		IF(IS_DIRECTORY ${curdir}/${child} AND EXISTS "${curdir}/${child}/CMakeLists.txt")
			ADD_SUBDIRECTORY(${child})
		ENDIF()
	ENDFOREACH()
ENDMACRO()

#自动引入子目录中所有的.h文件
MACRO(include_all_hearers)
	FILE(GLOB_RECURSE new_list *.h)
	SET(dirlist "")
	FOREACH(file_path ${new_list})
		#获取文件目录
		GET_FILENAME_COMPONENT(dir_path ${file_path} DIRECTORY)
		IF(NOT ${dir_path} IN_LIST dirlist)
			LIST(APPEND dirlist ${dir_path})
			INCLUDE_DIRECTORIES(${dir_path})
		ENDIF()		
	ENDFOREACH()
ENDMACRO()

#filter生成
MACRO(generate_filters_by_dir HEADER SOURCE)
    IF(MSVC)
		#所有头文件文件放入Hearder Files过滤器中
		FOREACH(sgbd_file ${${HEADER}})
			STRING(REGEX REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
			STRING(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
			STRING(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
			STRING(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
			IF(sgbd_nogroup)
				set(sgbd_group_name "\\")
			ENDIF(sgbd_nogroup)
			SOURCE_GROUP("Hearder Files\\${sgbd_group_name}" FILES ${sgbd_file})
		ENDFOREACH(sgbd_file)
		#所有源文件文件放入Source Files过滤器中
		FOREACH(sgbd_file ${${SOURCE}})
			STRING(REGEX REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
			STRING(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
			STRING(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
			STRING(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
			IF(sgbd_nogroup)
				SET(sgbd_group_name "\\")
			ENDIF(sgbd_nogroup)
			SOURCE_GROUP("Source Files\\${sgbd_group_name}" FILES ${sgbd_file})
		ENDFOREACH(sgbd_file)
    ENDIF(MSVC)
ENDMACRO()

#项目名称
PROJECT(mllib)
FIND_PACKAGE(CUDA)
#加入所有包含CMakeLists.txt的子目录
add_subdirs_have_cmakelists(${CMAKE_CURRENT_SOURCE_DIR})
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
#复制测试用例文件
FILE(COPY test_data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
