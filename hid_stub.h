#ifndef __HID_STUB_HPP__
#define __HID_STUB_HPP__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define HID_REPORT_LEN  (64UL)

int hid_init(uint16_t local_port, uint16_t peer_port, const char * peer_addr);
int hid_deinit(void);

int hid_send(const uint8_t * pbuf, const int len);
int hid_recv(uint8_t * const pbuf);

#ifdef __cplusplus
}
#endif

#endif // __HID_STUB_HPP__
