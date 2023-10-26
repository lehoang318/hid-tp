#include "ctrl_phy.h"
#include "hid_stub.h"
#include "util.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char ** argv) {
    uint8_t buf[CTRL_PHY_FRAME_SIZE];
    const int xfer_len = 22;

    srand(time(0));

    if ((1 < argc) && ('h' == argv[1][0])) {
        printf("\nHost Side!\n");
        hid_init(1111, 2222, "127.0.0.1");

        printf("Waiting for request from Device ...\n");
        ctrl_phy_recv(buf);
        display_ba(buf, CTRL_PHY_FRAME_SIZE);

        printf("\nSending response to Device ...\n");
        randomize(buf, xfer_len);
        display_ba(buf, xfer_len);
        ctrl_phy_send(buf, xfer_len);

    } else {
        printf("\nDevice Side!\n");
        hid_init(2222, 1111, "127.0.0.1");

        printf("Sending request to Host ...\n");
        randomize(buf, xfer_len);
        display_ba(buf, xfer_len);
        ctrl_phy_send(buf, xfer_len);

        ctrl_phy_recv(buf);
        display_ba(buf, CTRL_PHY_FRAME_SIZE);
    }
}
