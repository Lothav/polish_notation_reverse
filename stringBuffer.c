//
// Created by luizorv on 4/15/17.
//

#include "stringBuffer.h"


void recoverString(char* str, int length){
    int k = 0;
    while( k < length ){
        if( str[k] == '\0' ){
            str[k] = ' ';
        }
        k++;
    }
}

void setStringBufferWithCustomChars(int *i, char * line){
    (*i)--;
    int j = 2;
    while( j && (*i) >= 0 ){
        if( line[ *i ] != ' ' && line[ *i ] != EMPTY_CHAR ){
            if( line[ (*i)+1 ] == ' ' ) j--;
            int t = *i;
            while( line[t] != ' ' && t >= 0 ){
                line[t] = EMPTY_CHAR;
                t--;
            }
        }
        (*i)--;
    }
    (*i) = 0;
}