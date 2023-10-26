#ifndef __CTRL_PHY_HPP__
#define __CTRL_PHY_HPP__

#ifdef __cplusplus
extern "C" {
#endif

#include "hid_stub.h"
#include <stdint.h>

#define CTRL_PHY_HID_RID        (0UL)
#define CTRL_PHY_FRAME_SIZE     (HID_REPORT_LEN - 1)
#define CTRL_PHY_PADDING_VAL    (0xCCUL)

int ctrl_phy_send(const uint8_t * pbuf, const int len);
int ctrl_phy_recv(uint8_t * const pbuf);

#ifdef __cplusplus
}
#endif

#endif // __CTRL_PHY_HPP__
