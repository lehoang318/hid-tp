#include "hid_stub.h"

#include <mutex>

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

static std::mutex hid_mtx;

static int hid_s_fd = -1;
static char hid_peer_addr[128] = {0};
static uint16_t hid_local_port = 0U;
static uint16_t hid_peer_port = 0U;

extern "C" int hid_init(uint16_t local_port, uint16_t peer_port, const char * peer_addr) {
    std::lock_guard<std::mutex> guard(hid_mtx);

    //create a UDP socket
    int ret = socket(AF_INET, SOCK_DGRAM, 0);
    if (0 >= ret) {
        fprintf(stderr, "Failed to create UDP Socket (%d)!\n", errno);
        return -1;
    }

    hid_s_fd = ret;
    hid_local_port = local_port;
    strcpy(hid_peer_addr, peer_addr);
    hid_peer_port = peer_port;

    // Bind socket to `local_port`
    struct sockaddr_in sa;
    memset((char *) &sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(local_port);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    ret = bind(hid_s_fd , (struct sockaddr*)&sa, sizeof(sa) );
    if (0 != ret) {
        fprintf(stderr, "Failed to bind UDP Socket to port %u (%d)!\n", local_port, errno);
        return -1;
    }

    return 0;
}

extern "C" int hid_deinit() {
    std::lock_guard<std::mutex> guard(hid_mtx);
    if (0 < hid_s_fd) {
        close(hid_s_fd);
        hid_s_fd = -1;
    }

    return 0;
}

extern "C" int hid_send(const uint8_t * pbuf, const int len) {
    if (0 >= hid_s_fd) {
        fprintf(stderr, "HID Stub has not been initialized successfully!\n");
        return -1;
    }

    struct sockaddr_in peer_sa;
    memset(&peer_sa, 0, sizeof(peer_sa));
    peer_sa.sin_family = AF_INET;
    peer_sa.sin_addr.s_addr = inet_addr(hid_peer_addr);
    peer_sa.sin_port = htons(hid_peer_port);

    std::lock_guard<std::mutex> guard(hid_mtx);
    int ret = sendto(hid_s_fd, pbuf, len, 0, (struct sockaddr*)&peer_sa, sizeof(peer_sa));
    if (0 >= ret) {
        fprintf(stderr, "Failed to send data to `%s`/%u over UDP (%d)\n",
            hid_peer_addr, hid_peer_port, errno);
        return -1;
    }

    return ret;
}

extern "C" int hid_recv(uint8_t * const pbuf) {
    if (0 >= hid_s_fd) {
        fprintf(stderr, "HID Stub has not been initialized successfully!\n");
        return -1;
    }

    std::lock_guard<std::mutex> guard(hid_mtx);
    int ret = recv(hid_s_fd, pbuf, HID_REPORT_LEN, 0);

    if (0 > ret) {
        fprintf(stderr, "Failed to receive data at UDP Port %d (%d)\n", hid_local_port, errno);
        return -1;
    }

    return ret;
}
