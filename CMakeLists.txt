# Find Pangolin (https://github.com/stevenlovegrove/Pangolin)
#find_package(uWebSockets REQUIRED)
set(LibZip_DIR cmake)

find_package(ZLIB REQUIRED)
#find_package(SuiteParse REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Boost COMPONENTS system thread)
find_package(LibZip REQUIRED)
#find_package(Pangolin 0.2 REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(dso/src dso/thirdparty/Sophus)
include_directories(${EIGEN3_INCLUDE_DIR})
#include_directories(dso/src)
#link_directories (/mnt/c/Users/konno/Documents/GitKraken/DSOdemo/dso/build/lib/libdso.a)
include_directories(/usr/include/uWS)
include_directories( ${ZLIB_INCLUDE_DIRS})
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${LIBZIP_INCLUDE_DIR_ZIP} ${LIBZIP_INCLUDE_DIR_ZIPCONF} )

add_definitions(-DHAS_ZIPLIB=1)

set(CMAKE_CXX_FLAGS
   "${SSE_FLAGS} -O3 -g -std=c++0x -march=native -pthread"
#   "${SSE_FLAGS} -O3 -g -std=c++0x -fno-omit-frame-pointer"
)

add_executable(demo opencv_main.cpp WebOutputWrapper.cpp)
target_link_libraries(demo /mnt/c/Users/konno/Documents/GitKraken/DSOdemo/dso/build/lib/libdso.a /usr/lib/libuWS.so ${LIBZIP_LIBRARY} boost_system ${OpenCV_LIBS} boost_thread -lssl -lcrypt ${ZLIB_LIBRARIES})
