/**
 * @file basec_types.h
 * @brief Types for basec
 */

#ifndef BASEC_TYPES_H
#define BASEC_TYPES_H

#include <stdint.h>
#include <stdbool.h>

// Unsigned integers
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// Signed integers
typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// Floating point numbers
typedef float  f32;
typedef double f64;

// Characters
typedef char c8;

// Strings
typedef char* c_str;

#define U8_MIN  UINT8_MIN
#define U8_MAX  UINT8_MAX

#define U16_MIN UINT16_MIN
#define U16_MAX UINT16_MAX

#define U32_MIN UINT32_MIN
#define U32_MAX UINT32_MAX

#define U64_MIN UINT64_MIN
#define U64_MAX UINT64_MAX

#define I8_MIN  INT8_MIN
#define I8_MAX  INT8_MAX

#define I16_MIN INT16_MIN
#define I16_MAX INT16_MAX

#define I32_MIN INT32_MIN
#define I32_MAX INT32_MAX

#define I64_MIN INT64_MIN
#define I64_MAX INT64_MAX

#define F32_MIN FLT_MIN
#define F32_MAX FLT_MAX

#define F64_MIN DBL_MIN
#define F64_MAX DBL_MAX

#define C8_MIN  CHAR_MIN
#define C8_MAX  CHAR_MAX

#endif
