#ifdef __cplusplus
extern "C" {
#endif

#include "ctrl_phy.h"
#include "hid_stub.h"

#include <stdint.h>
#include <string.h>

#pragma pack(push, 1)
typedef struct {
    uint8_t report_id;
    uint8_t ctrl_phy_buf[CTRL_PHY_FRAME_SIZE];
} ctrl_phy_frame_t;
#pragma pack(pop)

static ctrl_phy_frame_t ctrl_phy_rx_frame;

extern uint8_t hid_channel[];

static inline void ctrl_phy_construct_frame(ctrl_phy_frame_t * const pframe, const uint8_t * pdata, const int len) {
    pframe->report_id = CTRL_PHY_HID_RID;
    memcpy(pframe->ctrl_phy_buf, pdata, len);
    for (int i = len; CTRL_PHY_FRAME_SIZE > i; i++) {
        pframe->ctrl_phy_buf[i] = CTRL_PHY_PADDING_VAL;
    }
}

int ctrl_phy_send(const uint8_t * pbuf, const int len) {
    ctrl_phy_frame_t ctrl_phy_tx_frame;
    ctrl_phy_construct_frame(&ctrl_phy_tx_frame, pbuf, len);

    return hid_send(&ctrl_phy_tx_frame, sizeof(ctrl_phy_tx_frame));
}

int ctrl_phy_recv(uint8_t * const pbuf) {
    int ret = hid_recv(&ctrl_phy_rx_frame);
    if (0 < ret) {
        memcpy(pbuf, ctrl_phy_rx_frame.ctrl_phy_buf, CTRL_PHY_FRAME_SIZE);
        return CTRL_PHY_FRAME_SIZE;
    } else {
        return 0;
    }
}

#ifdef __cplusplus
}
#endif
