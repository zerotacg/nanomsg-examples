cmake_minimum_required( VERSION 2.8 )
project( nanomsg-examples )

find_path( NANOMSG_SDK include/nanomsg/nn.h )
find_path( NANOMSG_INCLUDE_DIRS nanomsg/nn.h HINTS ${NANOMSG_SDK}/include )
find_library( NANOMSG_LIBRARIES nanomsg HINTS ${NANOMSG_SDK}/lib )

set( INCLUDE_DIRS
    ${NANOMSG_INCLUDE_DIRS}
)

set(LIBRARIES
    ${NANOMSG_LIBRARIES}
)

add_subdirectory( reqrep_proxy )
