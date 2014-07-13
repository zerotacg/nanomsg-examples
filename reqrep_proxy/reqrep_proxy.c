#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>

#define FRONTEND "tcp://127.0.0.1:12345"
#define BACKEND "tcp://127.0.0.1:12346"

uint32_t nn_getl (const uint8_t *buf)
{
    return (((uint32_t) buf [0]) << 24) |
           (((uint32_t) buf [1]) << 16) |
           (((uint32_t) buf [2]) << 8) |
           ((uint32_t) buf [3]);
}

int main( const int argc, const char **argv )
{
    int frontend = nn_socket( AF_SP_RAW, NN_REP );
    int backend = nn_socket( AF_SP_RAW, NN_REP );

    nn_bind( frontend, FRONTEND );
    nn_bind( backend, BACKEND );

    char *hdr = NULL;
    char *body = NULL;
    struct nn_msghdr msg;
    struct nn_iovec iov;
    iov.iov_base = &body;
    iov.iov_len = NN_MSG;
    memset( &msg, 0, sizeof(msg) );
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = &hdr;
    msg.msg_controllen = NN_MSG;
    int rc = nn_recvmsg( frontend, &msg, 0 );
    printf( "msg_len: %i", rc );
    printf( "msg_body: \"%s\"", body );
    printf( "msg_hdr: %i %i", nn_getl(hdr), nn_getl(hdr + 4) );
    nn_freemsg( hdr );
    nn_freemsg( body );

    nn_shutdown( frontend, 0 );
    nn_shutdown( backend, 0 );

    return 0;
}
