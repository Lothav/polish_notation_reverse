#include "stringBuffer.h"


void recoverString(char* str){
    // find \0 and set with ' '
    int k = 0;
    while( k < MAX_CHAR ){
        if( str[k] == '\0' ){
            str[k] = ' ';
        }
        k++;
    }
}

void setStringBufferWithCustomChars(int *i, char * line){
    // set actual '?' character to 'G'
    line[*i] = GROUP_CHAR;
    (*i)--;

    // now, we need to set last two valid charactes with 'E'
    // they were grouped in new 'G'
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