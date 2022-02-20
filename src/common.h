#ifndef HVM_COMMON_H
#define HVM_COMMON_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define _4btoi(buf) *buf++ + (*buf++ << 8) + (*buf++ << 16) + (*buf++ << 24)
#define _a_4btoi(buf, i) buf[i] + (buf[i + 1] << 8) + (buf[i + 2] << 16) + (buf[i + 3] << 24)
#define _2btos(buf) *buf++ + (*buf++ << 8)
#define _a_2btos(buf, i) buf[i] + (buf[i + 1] << 8)

#define u8 uint8_t

#endif
