//
// Created by luizorv on 4/15/17.
//

#include "utils.h"

void intToBin(int num, char *str, int op_count) {
    int mask = 0x2 << op_count - 1;
    while(mask >>= 1) *(str++) = (char) (!!(mask & num) + '0');
}

void convertBinToOperators(char* str, int length){
    int i;
    for(i = 0; i < length; i++){
        *(str+i) = (char) (*(str+i) == '0' ? '+' : '*');
    }
}
