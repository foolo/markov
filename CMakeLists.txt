cmake_minimum_required ( VERSION 2.8.12 )

set ( MainOut markov.out )

add_compile_options(-std=c++0x) #CMake 2.8.12 or newer

project ( Markov )

file ( GLOB_RECURSE AppSrc src/*.cpp )

include_directories (
	src
)

add_executable ( ${MainOut} ${AppSrc} )

