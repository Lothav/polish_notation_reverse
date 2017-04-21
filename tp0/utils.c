#include "utils.h"

void convertNumberToOperator(int num, char *str, int op_count) {
    // make a mask of bits
    // ex.: op_count = 4, so, 2 << 3 = 2^3 = 8
    int mask = 0x2 << (op_count - 1);

    // in each loop, mask = mask/2 (or shifted to right 1)
    // str position will be incrementing and will be set with
    // '+' if (mask & num) == 0 otherwise '*'
    while( mask >>= 1 ) *(str++) = (char) ( ((!!(mask & num) + '0') == '0') ? '+' : '*' );
}