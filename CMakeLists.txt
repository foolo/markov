cmake_minimum_required ( VERSION 2.8.12 )

set ( MainOut markov.out )
set ( TestOut unittest.out )

add_compile_options(-std=c++0x -g) #CMake 2.8.12 or newer

project ( Markov )

file ( GLOB_RECURSE AppSrc src/applib/*.cpp )
file ( GLOB_RECURSE TestSrc src/unittest/*.cpp )

include_directories (
	src
	src/applib
)

add_library ( app STATIC ${AppSrc} )

add_executable ( ${MainOut} src/main.cpp )
target_link_libraries ( ${MainOut} app )

add_executable ( ${TestOut} ${TestSrc} )
target_link_libraries ( ${TestOut} app )
