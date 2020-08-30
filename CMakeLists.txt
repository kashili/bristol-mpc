cmake_minimum_required(VERSION 3.12.0)
project(bristolfashion)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost)

if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	add_executable(bristolfashion
			${PROJECT_SOURCE_DIR}/src/bristol.cpp
			${PROJECT_SOURCE_DIR}/src/parser.cpp
			${PROJECT_SOURCE_DIR}/include/bristol.h
			${PROJECT_SOURCE_DIR}/include/parser.h
			${PROJECT_SOURCE_DIR}/main.cpp)
	
	target_link_libraries(bristolfashion ${Boost_LIBRARIES})

endif()
