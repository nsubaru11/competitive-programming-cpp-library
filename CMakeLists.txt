cmake_minimum_required(VERSION 4.0)
project(competitive-programming-cpp-library LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

if (UNIX AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	execute_process(COMMAND "${CMAKE_CXX_COMPILER}" -print-file-name=libstdc++.so
		OUTPUT_VARIABLE gcc_runtime OUTPUT_STRIP_TRAILING_WHITESPACE COMMAND_ERROR_IS_FATAL ANY)
	if (IS_ABSOLUTE "${gcc_runtime}" AND EXISTS "${gcc_runtime}")
		get_filename_component(gcc_runtime "${gcc_runtime}" REALPATH)
		get_filename_component(gcc_runtime_dir "${gcc_runtime}" DIRECTORY)
	endif ()
endif ()

# test/example 配下の .cpp を実行ファイルとして登録する（例: test/example/ds/tree/Treap.cpp → ds_tree_Treap）。
file(GLOB_RECURSE EXAMPLES CONFIGURE_DEPENDS test/example/*.cpp)
foreach (source ${EXAMPLES})
	file(RELATIVE_PATH relative "${CMAKE_CURRENT_SOURCE_DIR}/test/example" "${source}")
	string(REGEX REPLACE "\\.cpp$" "" target ${relative})
	string(REPLACE "/" "_" target ${target})
	add_executable(${target} ${source})
	target_include_directories(${target} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
	if (gcc_runtime_dir)
		set_property(TARGET ${target} PROPERTY BUILD_RPATH "${gcc_runtime_dir}")
	endif ()
endforeach ()
