#pragma once

#include "stdint.h"

#ifndef C_WORL_UTILS_H
#define C_WORL_UTILS_H

#define ZERO 0

#define ONE 1

#define TRUE 1

#define FALSE 0

typedef uint8_t  u8_t;
typedef uint8_t  byte_t;
typedef uint32_t u32_t;
typedef uint16_t u16_t;
typedef uint64_t u64_t;

void *check_mem_alloc(void *mem_to_check, const char *error_type);
void *throw_error(const char *error_type);

#endif // C_WORL_UTILS_H
