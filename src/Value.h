
#ifndef TLISP_VALUE_H
#define TLISP_VALUE_H

#include <stdint.h>

typedef int8_t   byte_t;
typedef uint8_t  ubyte_t;
typedef int16_t  short_t;
typedef uint16_t ushort_t;
typedef int32_t  int_t;
typedef uint32_t uint_t;
typedef int64_t  long_t;
typedef uint64_t ulong_t;

typedef float float_t;
typedef double double_t;

/* Logic types */
typedef uint8_t bool_t;

/* Character types */
typedef uint8_t  char_t;   /*< ASCII characters, utf-8 */

enum ValueType {
    VALUE_NIL = 0,
    VALUE_BYTE,
    VALUE_UBYTE,
    VALUE_SHORT,
    VALUE_USHORT,
    VALUE_INT,
    VALUE_UINT,
    VALUE_LONG,
    VALUE_ULONG,
    VALUE_FLOAT,
    VALUE_DOUBLE,
    VALUE_BOOL
};
union ValueData {
    byte_t   s_byte;
    ubyte_t  u_byte;
    short_t  s_short;
    ushort_t u_short;
    int_t    s_int;
    uint_t   u_int;
    long_t   s_long;
    ulong_t  u_long;
    float_t  t_float;
    double_t t_double;
    bool_t   t_bool;
};
struct Value {
    enum ValueType type;
    union ValueData value;
};

#define NIL {VALUE_NIL, { 0 } }

#endif
