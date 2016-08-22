cmake_minimum_required(VERSION 3.5)

project(NativeClient)

if (WIN32)
	add_definitions(-DWIN32)
endif()

find_package(Boost 1.58.0 COMPONENTS system filesystem REQUIRED)

if (WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -U__STRICT_ANSI__ -std=c++0x")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

include_directories(include/ include/packets include/tools thirdparty/ ${Boost_INCLUDE_DIRS})
link_directories (lib/)

file(GLOB SOURCE_FILES src/*.cpp src/client_packets/*.cpp src/server_packets/*.cpp src/tools/*.cpp)
list(REMOVE_ITEM SOURCE_FILES config.h) # Dont include cryptopp config file

add_executable(NativeClient ${SOURCE_FILES})
if (UNIX)
	target_link_libraries(NativeClient cryptopp ${Boost_LIBRARIES} -lm -pthread)
elseif (WIN32)
	target_link_libraries(NativeClient cryptopp ws2_32 psapi wininet ${Boost_LIBRARIES})
endif()
