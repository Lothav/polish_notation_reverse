#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY_CHAR 'E'
#define EMPTY_VALUE -1
#define G_VALUE -2
#define OPERATION_MISSING '?'
#define OPERATION_PLUS '+'

typedef struct Operation{
    int id;
    int a;
    int b;
    int grouped;
    int op_a;
    int op_b;
} Operation;

int recu(Operation * operations, int index, char *str){
    if(operations[index].op_b != EMPTY_VALUE && operations[index].op_a != EMPTY_VALUE){
        return str[operations[index].id] == OPERATION_PLUS ?
               (recu(operations, operations[index].op_b, str) + recu(operations, operations[index].op_a, str)) :
               (recu(operations, operations[index].op_b, str) * recu(operations, operations[index].op_a, str));
    }

    if(operations[index].a != EMPTY_VALUE && operations[index].b != EMPTY_VALUE){
        return str[operations[index].id] == OPERATION_PLUS ?
               (operations[index].a + operations[index].b) :
               (operations[index].a * operations[index].b);
    }

    int _not_empty = (operations[index].a == EMPTY_VALUE ? operations[index].b : operations[index].a);

    if(operations[index].op_b != EMPTY_VALUE){
        return str[operations[index].id] == OPERATION_PLUS ?
               (_not_empty + recu(operations, operations[index].op_b, str)) :
               (_not_empty * recu(operations, operations[index].op_b, str));
    }

    if(operations[index].op_a != EMPTY_VALUE){
        return str[operations[index].id] == OPERATION_PLUS ?
               (_not_empty + recu(operations, operations[index].op_a, str)) :
               (_not_empty * recu(operations, operations[index].op_a, str));
    }
}

void intToBin(int num, char *str, int actual_ope) {
    int mask = 0x2 << actual_ope - 1;
    while(mask >>= 1) *(str++) = (char) (!!(mask & num) + '0');
}

void convertBinToOperators(char* str, int length){
    int i;
    for(i = 0; i < length; i++){
        *(str+i) = (char) (*(str+i) == '0' ? '+' : '*');
    }
}

int main(int argc, char** argv) {

    FILE* fb = NULL;
    char* line = NULL;
    size_t len = 0;
    ssize_t line_size = 0;

    char * value = NULL;

    int * operators = (int *) malloc(2 * sizeof(int));

    Operation* operations = NULL;
    int actual_ope = 0;

    fb = fopen(argv[1], "r");
    if ( NULL == fb ) exit(EXIT_FAILURE);

    int i = 0, j = 0, k = 0, id = 0;


    if ( -1 != (line_size = getline(&line, &len, fb))){
        int l = 0;
        while( NULL != (value = strtok(NULL == value ? line : NULL, " \n")) ){

            if( EMPTY_CHAR  == *value ) {
                i += 2;
                continue;
            }

            if( OPERATION_MISSING  == *value ) {

                j = 0, k = 0;
                while( k < line_size ){
                    if( line[k] == '\0' ){
                        line[k] = ' ';
                        j = i;
                    }
                    k++;
                }

                operations = realloc(operations, (1 + actual_ope) * sizeof(Operation));

                operations[actual_ope].id = id++;
                operations[actual_ope].a = EMPTY_VALUE;
                operations[actual_ope].b = EMPTY_VALUE;
                operations[actual_ope].grouped = 0;
                operations[actual_ope].op_a = EMPTY_VALUE;
                operations[actual_ope].op_b = EMPTY_VALUE;

                if( operators[0] == G_VALUE && operators[1] == G_VALUE ) {
                    operations[actual_ope].op_a = actual_ope-1;
                    operations[actual_ope-1].grouped = 1;
                    int test = actual_ope-2;
                    while(operations[test].grouped){
                        test--;
                    }
                    if(!operations[test].grouped){
                        operations[actual_ope].op_b = test;
                        operations[test].grouped = 1;
                    }
                } else {
                    if( operators[0] == G_VALUE ){
                        operations[actual_ope].op_a = actual_ope-1;
                        operations[actual_ope-1].grouped = 1;
                    } else {
                        operations[actual_ope].a = operators[0];
                    }

                    if( operators[1] == G_VALUE ){
                        operations[actual_ope].op_b = actual_ope-1;
                        operations[actual_ope-1].grouped = 1;
                    } else {
                        operations[actual_ope].b = operators[1];
                    }
                }

                actual_ope++;
                line[j] = 'G';

                i--;
                j = 2;
                while( j && i >= 0 ){
                    if( line[ i ] != ' ' && line[ i ] != EMPTY_CHAR ){
                        if(line[ i+1 ] == ' ') j--;
                        int t = i;
                        while(line[t] != ' ' && t >= 0){
                            line[t] = EMPTY_CHAR;
                            t--;
                        }
                    }
                    i--;
                }
                i = 0;
                value = NULL;
            } else {
                operators[l % 2] = * value == 'G' ? G_VALUE : atoi( value );
                i += strlen(value) + 1;
                l++;
            }
        }

        getline( &line, &len, fb );

        int result = atoi(line);
        char *str = (char *) calloc((size_t) (actual_ope + 1), sizeof( char ) );

        for( j = 0; j < (0x2 << (actual_ope - 1)); j++ ){
            intToBin(j, str, actual_ope);
            convertBinToOperators(str, actual_ope);
            if(result == recu(operations, actual_ope-1, str)){
                printf("%s\n", str);
            }
        }
        if(str) free(str);
    }

    if(operators) free(operators);
    fclose(fb);
    if (line) free(line);
    if (operations) free(operations);

    return EXIT_SUCCESS;
}