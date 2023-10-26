#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void display_ba(const uint8_t * pbuf, const int len) {
    const int ALIGNMENT = 16;
    printf("%08X: [", pbuf);
    for (int i = 0; len > i; i++) {
        if (0 == (i % ALIGNMENT)) {
            printf("\n%02X ", pbuf[i]);
        } else {
            printf("%02X ", pbuf[i]);
        }
    }
    printf("\n];\n");
}

void randomize(uint8_t * const pbuf, const int len) {
    for (int i = 0; len > i; i++) {
        pbuf[i] = rand() % 255;
    }
}

#ifdef __cplusplus
}
#endif
