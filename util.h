#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

extern void display_ba(const uint8_t * pbuf, const int len);
extern void randomize(uint8_t * const pbuf, const int len);

#ifdef __cplusplus
}
#endif

#endif // __UTIL_HPP__
