cmake_minimum_required(VERSION 4.0)
project(competitive-programming-cpp-library)

set(CMAKE_CXX_STANDARD 23)
include_directories(src)

# test/example 配下の .cpp を実行ファイルとして登録する（例: test/example/ds/tree/Treap.cpp → ds_tree_Treap）。
file(GLOB_RECURSE EXAMPLES CONFIGURE_DEPENDS test/example/*.cpp)
foreach (source ${EXAMPLES})
	file(RELATIVE_PATH relative ${CMAKE_SOURCE_DIR}/test/example ${source})
	string(REGEX REPLACE "\\.cpp$" "" target ${relative})
	string(REPLACE "/" "_" target ${target})
	add_executable(${target} ${source})
endforeach ()
