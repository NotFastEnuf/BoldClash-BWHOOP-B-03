#include "qfplib/qfplib.h"

///////////////////////////////////////////////////////////////////////////////
//  Table 3, single precision floating-point comparison helper functions

//  qfp_fcmp(r0, r1):
//  equal? return 0
//  r0 > r1? return +1
//  r0 < r1: return -1

//  result (1, 0) denotes (=, ?<>) [2], use for C == and !=
int __wrap___aeabi_fcmpeq(float x, float y) {
    return (qfp_fcmp(x, y) == 0)  //  x == y
        ? 1 : 0;
}
//  Unit Tests:
//  aeabi_fcmpeq(2205.196, 2205.196) = 1
//  aeabi_fcmpeq(2205.196, 2205.195) = 0
//  aeabi_fcmpeq(2205.196, 2205.197) = 0
//  aeabi_fcmpeq(2205.196, 0) = 0
//  aeabi_fcmpeq(-2205.196, -2205.196) = 1
//  aeabi_fcmpeq(-2205.196, -2205.195) = 0
//  aeabi_fcmpeq(-2205.196, -2205.197) = 0
//  aeabi_fcmpeq(-2205.196, 0) = 0

//  result (1, 0) denotes (<, ?>=) [2], use for C <
int __wrap___aeabi_fcmplt(float x, float y) {
    return (qfp_fcmp(x, y) < 0)  //  x < y
        ? 1 : 0;
}
//  Unit Tests:
//  aeabi_fcmplt(2205.196, 2205.196) = 0
//  aeabi_fcmplt(2205.196, 2205.195) = 0
//  aeabi_fcmplt(2205.196, 2205.197) = 1
//  aeabi_fcmplt(2205.196, 0) = 0
//  aeabi_fcmplt(-2205.196, -2205.196) = 0
//  aeabi_fcmplt(-2205.196, -2205.195) = 1
//  aeabi_fcmplt(-2205.196, -2205.197) = 0
//  aeabi_fcmplt(-2205.196, 0) = 1

//  result (1, 0) denotes (<=, ?>) [2], use for C <=
int __wrap___aeabi_fcmple(float x, float y) { 
    return (qfp_fcmp(x, y) > 0)  //  x > y
        ? 0 : 1; 
}
//  Unit Tests:
//  aeabi_fcmple(2205.196, 2205.196) = 1
//  aeabi_fcmple(2205.196, 2205.195) = 0
//  aeabi_fcmple(2205.196, 2205.197) = 1
//  aeabi_fcmple(2205.196, 0) = 0
//  aeabi_fcmple(-2205.196, -2205.196) = 1
//  aeabi_fcmple(-2205.196, -2205.195) = 1
//  aeabi_fcmple(-2205.196, -2205.197) = 0
//  aeabi_fcmple(-2205.196, 0) = 1

//  result (1, 0) denotes (>=, ?<) [2], use for C >=
int __wrap___aeabi_fcmpge(float x, float y) { 
    return (qfp_fcmp(x, y) < 0)  //  x < y
        ? 0 : 1; 
}
//  Unit Tests:
//  aeabi_fcmpge(2205.196, 2205.196) = 1
//  aeabi_fcmpge(2205.196, 2205.195) = 1
//  aeabi_fcmpge(2205.196, 2205.197) = 0
//  aeabi_fcmpge(2205.196, 0) = 1
//  aeabi_fcmpge(-2205.196, -2205.196) = 1
//  aeabi_fcmpge(-2205.196, -2205.195) = 0
//  aeabi_fcmpge(-2205.196, -2205.197) = 1
//  aeabi_fcmpge(-2205.196, 0) = 0

//  result (1, 0) denotes (>, ?<=) [2], use for C >
int __wrap___aeabi_fcmpgt(float x, float y) { 
    return (qfp_fcmp(x, y) > 0)  //  x > y
        ? 1 : 0; 
}
//  Unit Tests:
//  aeabi_fcmpgt(2205.196, 2205.196) = 0
//  aeabi_fcmpgt(2205.196, 2205.195) = 1
//  aeabi_fcmpgt(2205.196, 2205.197) = 0
//  aeabi_fcmpgt(2205.196, 0) = 1
//  aeabi_fcmpgt(-2205.196, -2205.196) = 0
//  aeabi_fcmpgt(-2205.196, -2205.195) = 0
//  aeabi_fcmpgt(-2205.196, -2205.197) = 1
//  aeabi_fcmpgt(-2205.196, 0) = 0

//  result (1, 0) denotes (?, <=>) [2], use for C99 isunordered()
int __wrap___aeabi_fcmpun(float x, float y) { 
    return (qfp_fcmp(x, y) == 0)  //  x == y
        ? 0 : 1;
}
//  Unit Tests:
//  aeabi_fcmpun(2205.196, 2205.196) = 0
//  aeabi_fcmpun(2205.196, 2205.195) = 1
//  aeabi_fcmpun(2205.196, 2205.197) = 1
//  aeabi_fcmpun(2205.196, 0) = 1
//  aeabi_fcmpun(-2205.196, -2205.196) = 0
//  aeabi_fcmpun(-2205.196, -2205.195) = 1
//  aeabi_fcmpun(-2205.196, -2205.197) = 1
//  aeabi_fcmpun(-2205.196, 0) = 1

///////////////////////////////////////////////////////////////////////////////
//  Table 4, Standard single precision floating-point arithmetic helper functions

//  single-precision division, n / d
float  __wrap___aeabi_fdiv(float  n, float d)  { 
    return qfp_fdiv_fast( n , d ); 
}
//  Unit Tests:
//  aeabi_fdiv(2205.1969, 270.8886) = 8.140604292687105
//  aeabi_fdiv(-2205.1969, 270.8886) = -8.140604292687105
//  aeabi_fdiv(2205.1969, -270.8886) = -8.140604292687105
//  aeabi_fdiv(-2205.1969, -270.8886) = 8.140604292687105

float __wrap___aeabi_fadd(float a, float b) {
    return qfp_fadd( a , b );
}
//  Unit Tests:
//  aeabi_fadd(2205.1969, 270.8886) = 2476.0855
//  aeabi_fadd(-2205.1969, 270.8886) = -1934.3083
//  aeabi_fadd(2205.1969, -270.8886) = 1934.3083
//  aeabi_fadd(-2205.1969, -270.8886) = -2476.0855

float __wrap___aeabi_fsub(float a, float b) {
    return qfp_fsub( a , b );
}
//  Unit Tests:
//  aeabi_fsub(2205.1969, 270.8886) = 1934.3083
//  aeabi_fsub(-2205.1969, 270.8886) = -2476.0855
//  aeabi_fsub(2205.1969, -270.8886) = 2476.0855
//  aeabi_fsub(-2205.1969, -270.8886) = -1934.3083

float __wrap___aeabi_fmul(float a, float b) {
    return qfp_fmul( a , b );
}
//  Unit Tests:
//  aeabi_fmul(2205.1969, 270.8886) = 597362.70096534
//  aeabi_fmul(-2205.1969, 270.8886) = -597362.70096534
//  aeabi_fmul(2205.1969, -270.8886) = -597362.70096534
//  aeabi_fmul(-2205.1969, -270.8886) = 597362.70096534

///////////////////////////////////////////////////////////////////////////////
//  Table 5, Standard integer to floating-point conversions


//  integer to float C-style conversion.
float __wrap___aeabi_i2f(int x) { 
    return qfp_int2float(x);
}

float __wrap___aeabi_ui2f(unsigned int x) { 
    return qfp_uint2float(x);
}

///////////////////////////////////////////////////////////////////////////////
//  Table 6, Standard floating-point to integer conversions

//  float to integer C-style conversion. "z" means round towards 0.
int __wrap___aeabi_f2iz(float x) { 
    if (qfp_fcmp(x, 0) == 0) { return 0; }
    //  qfp_float2int() works like floor().  If x is negative, we add 1 to the result.
    int xfloored = qfp_float2int(x);
    if (xfloored < 0) { return xfloored + 1; }
    return xfloored; 
}
//  Unit Tests:
//  aeabi_f2iz(0) = 0
//  aeabi_f2iz(2205.1969) = 2205
//  aeabi_f2iz(-2205.1969) = -2205

//  float to unsigned C-style conversion. "z" means round towards 0.
unsigned __wrap___aeabi_f2uiz(float x) { 
    if (qfp_fcmp(x, 0) == 0) { return 0; }
    if (qfp_fcmp(x, 0) < 0) { return 0; }
    return qfp_float2uint(x); 
}
//  Unit Tests:
//  aeabi_f2iz(0) = 0
//  aeabi_f2uiz(2205.1969) = 2205
//  aeabi_f2uiz(-2205.1969) = 0
