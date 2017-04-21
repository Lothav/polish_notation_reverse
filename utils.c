#include "utils.h"

void convertNumberToOperator(int num, char *str, int op_count) {
    int mask = 0x2 << (op_count - 1);
    while( mask >>= 1 ) *(str++) = (char) ( ((!!(mask & num) + '0') == '0') ? '+' : '*' );
}