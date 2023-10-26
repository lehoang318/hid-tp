#ifdef __cplusplus
extern "C" {
#endif

#include "ctrl_tp.h"
#include "ctrl_phy.h"

#include <stdint.h>

static uint8_t

int tp_send(const uint8_t * pbuf, const int len);
int tp_recv(uint8_t * const pbuf);
int tp_rx_available(void);
void tp_task();

#ifdef __cplusplus
}
#endif
