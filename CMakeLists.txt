cmake_minimum_required(VERSION 2.8)

project(interval_capture)

set(src_interval_capture main.cpp ImagePost.cpp )

set( CMAKE_CXX_FLAGS "-g" )
set( CMAKE_C_FLAGS "-g"  )

find_package( OpenCV REQUIRED )
find_package( SDL REQUIRED )
find_package( Boost REQUIRED COMPONENTS system-mt filesystem-mt thread-mt program_options-mt)

find_library( CURL_LIBRARY NAMES curl curllib libcurl_imp curllib_static)

add_executable( interval_capture ${src_interval_capture} )
include_directories( /usr/local/include ${SDL_INCLUDE_DIR} ${Boost_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIR} )
target_link_libraries( interval_capture ${CURL_LIBRARY} ${SDL_LIBRARY} ${Boost_LIBRARIES} ${OpenCV_LIBS} )



