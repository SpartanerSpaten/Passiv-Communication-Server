cmake_minimum_required(VERSION 3.10.2)

project(C_API)

set(CMAKE_CXX_STANDARD 11)

############################
##      SOURCE FILES      ##
############################
add_executable(${PROJECT_NAME} src/main.cpp src/note.h src/note.cpp src/router.h src/router.cpp)#


#####################################
##      HEADERS SEARCH PATHS       ##
#####################################
set(PROJECT_INCLUDE_DIR ".")
set(PISTACHE_INCLUDE_DIR "/usr/local/include/pistache/")
set(HEADER_SEARCH_PATHS ${PROJECT_INCLUDE_DIR} ${PISTACHE_INCLUDE_DIR})

set(RAPIDJSON_INCLUDE_DIR "/usr/local/include/pistache/")
set(HEADER_SEARCH_PATHS_J ${PROJECT_INCLUDE_DIR} ${RAPIDJSON_INCLUDE_DIR})


#####################################
##      LIBRARY SEARCH PATHS       ##
#####################################
set(PISTACHE_LIBRARY "/usr/local/lib/libpistache.a")
set(EXTRA_LIBRARY "-pthread")#-lssl
set(LIBRARIES_SEARCH_PATHS ${PISTACHE_LIBRARY} ${EXTRA_LIBRARY})


#######################################
##      ADDING HEADERS LIBRARY       ##
#######################################
include_directories(${HEADER_SEARCH_PATHS})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES_SEARCH_PATHS})
