# Find Pangolin (https://github.com/stevenlovegrove/Pangolin)
#find_package(uWebSockets REQUIRED)
find_package(ZLIB REQUIRED)
message("--- found ziplib (${ZLIB_VERSION_STRING}), compiling with zip capability.")

include_directories(/usr/include/uWS)
include_directories( ${ZLIB_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS
   "${SSE_FLAGS} -O3 -g -std=c++0x -march=native"
#   "${SSE_FLAGS} -O3 -g -std=c++0x -fno-omit-frame-pointer"
)

add_executable(demo main.cpp)
target_link_libraries(demo /usr/lib/libuWS.so -lssl -lcrypt ${ZLIB_LIBRARIES})
