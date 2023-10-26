#ifndef __CTRL_TP_HPP__
#define __CTRL_TP_HPP__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define TP_PACKET_SIZE_LIMIT    (256UL)

int tp_send(const uint8_t * pbuf, const int len);
int tp_recv(uint8_t * const pbuf);
int tp_rx_available(void);
void tp_task();

#ifdef __cplusplus
}
#endif

#endif // __CTRL_TP_HPP__
