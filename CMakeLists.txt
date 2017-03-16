# Find Pangolin (https://github.com/stevenlovegrove/Pangolin)
#find_package(uWebSockets REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Boost COMPONENTS system thread)

include_directories(dso/src dso/thirdparty/Sophus)
include_directories(${EIGEN3_INCLUDE_DIR})
#include_directories(dso/src)
#link_directories (/mnt/c/Users/konno/Documents/GitKraken/DSOdemo/dso/build/lib/libdso.a)
include_directories(/usr/include/uWS)
include_directories( ${ZLIB_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS
   "${SSE_FLAGS} -O3 -g -std=c++0x -march=native -pthread"
#   "${SSE_FLAGS} -O3 -g -std=c++0x -fno-omit-frame-pointer"
)

add_executable(demo main.cpp)
target_link_libraries(demo /mnt/c/Users/konno/Documents/GitKraken/DSOdemo/dso/build/lib/libdso.a /usr/lib/libuWS.so boost_system boost_thread -lssl -lcrypt ${ZLIB_LIBRARIES})
