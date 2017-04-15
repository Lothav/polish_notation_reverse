#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY_CHAR 'E'
#define EMPTY_VALUE -1
#define G_VALUE -2
#define OPERATION_MISSING '?'
#define OPERATION_PLUS '+'

typedef struct{
    int a;
    int b;
    struct Operation *op_a;
    struct Operation *op_b;
} Operation;

int recu(Operation * operations, char *str, int * actual_ope){
    if(operations->op_b != NULL && operations->op_a != NULL){
        return str[(*actual_ope)--] == OPERATION_PLUS ?
               (recu((Operation *) operations->op_b, str, actual_ope) + recu((Operation *) operations->op_a, str, actual_ope)) :
               (recu((Operation *) operations->op_b, str, actual_ope) * recu((Operation *) operations->op_a, str, actual_ope));
    }

    if(operations->a != EMPTY_VALUE && operations->b != EMPTY_VALUE){
        return str[(*actual_ope)--] == OPERATION_PLUS ?
               (operations->a + operations->b) :
               (operations->a * operations->b);
    }

    int _not_empty = (operations->a == EMPTY_VALUE ? operations->b : operations->a);

    if(operations->op_b != NULL){
        return str[(*actual_ope)--] == OPERATION_PLUS ?
               (_not_empty + recu((Operation *) operations->op_b, str, actual_ope)) :
               (_not_empty * recu((Operation *) operations->op_b, str, actual_ope));
    }

    if(operations->op_a != NULL){
        return str[(*actual_ope)--] == OPERATION_PLUS ?
               (_not_empty + recu((Operation *) operations->op_a, str, actual_ope)) :
               (_not_empty * recu((Operation *) operations->op_a, str, actual_ope));
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

    FILE* fb;
    char* line = NULL;
    size_t len = 0;
    ssize_t line_size;

    char * value = NULL;

    int operators[2];

    Operation* operations = (Operation *) malloc( sizeof(Operation) );
    int actual_ope = 0;
    int group_ope = 0;

    fb = fopen(argv[1], "r");
    if ( NULL == fb ) exit(EXIT_FAILURE);

    int i = 0, j = 0, k = 0;
    while ( -1 != (line_size = getline(&line, &len, fb))){
        int l = 0;
        while( NULL != (value = strtok(NULL == value ? line : NULL, " \n")) ){

            if( EMPTY_CHAR  == *value ) {
                i += strlen(value)+1;
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

                operations[actual_ope].a = EMPTY_VALUE;
                operations[actual_ope].b = EMPTY_VALUE;
                operations[actual_ope].op_a = NULL;
                operations[actual_ope].op_b = NULL;

                if( operators[0] == G_VALUE && operators[1] == G_VALUE ) {
                    operations[actual_ope].op_a = &operations[actual_ope-1];
                    operations[actual_ope].op_b = &operations[(--group_ope)-1];
                } else {
                    group_ope++;

                    if( operators[0] == G_VALUE ){
                        operations[actual_ope].op_a = &operations[actual_ope-1];
                    } else {
                        operations[actual_ope].a = operators[0];
                    }

                    if( operators[1] == G_VALUE ){
                        operations[actual_ope].op_b = &operations[actual_ope-1];
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
                        line[i] = EMPTY_CHAR;
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

        line_size = getline(&line, &len, fb);
        int result = atoi(line);

        char str[actual_ope];
        int re = 0;
        for( j = 0; j < (0x2 << actual_ope); j++ ){
            intToBin(j, str, actual_ope);
            i = actual_ope;
            convertBinToOperators(str, actual_ope);
            re = recu( &operations[ i-1 ], str, &i);
            printf("%s\t%d\n", str, re);
        }
    }

    fclose(fb);
    if (line) free(line);
    if (operations) free(operations);
    exit(EXIT_SUCCESS);

    return EXIT_SUCCESS;
}