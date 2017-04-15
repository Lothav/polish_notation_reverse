#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY_CHAR 'E'
#define EMPTY_VALUE -1
#define G_VALUE -2
#define OPERATION_MISSING '?'

typedef struct{
    int a;
    int b;
    struct Operation *op_a;
    struct Operation *op_b;
} Operation;

int recu(Operation * operations){

    if(operations->op_b != NULL && operations->op_a != NULL){
        return recu((Operation *) operations->op_b) + recu((Operation *) operations->op_a);
    }

    if(operations->a != EMPTY_VALUE && operations->b != EMPTY_VALUE){
        return operations->a + operations->b;
    }

    int _not_empty = (operations->a == EMPTY_VALUE ? operations->b : operations->a);

    if(operations->op_b != NULL){
        return _not_empty + recu((Operation *) operations->op_b);
    }

    if(operations->op_a != NULL){
        return _not_empty + recu((Operation *) operations->op_a);
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

                operations = realloc(operations, (1+actual_ope) * sizeof(Operation));

                operations[actual_ope].a = EMPTY_VALUE;
                operations[actual_ope].b = EMPTY_VALUE;
                operations[actual_ope].op_a = NULL;
                operations[actual_ope].op_b = NULL;

                if( operators[0] == G_VALUE ){
                    operations[actual_ope].op_a = &operations[actual_ope - 1];
                } else {
                    operations[actual_ope].a = operators[0];
                }

                if( operators[1] == G_VALUE ){
                    operations[actual_ope].op_b = operations[actual_ope].op_a != NULL ? &operations[actual_ope - 2] : &operations[actual_ope - 1];
                } else {
                    operations[actual_ope].b = operators[1];
                }

                actual_ope++;

                line[j] = 'G';

                j = 3;
                i--;
                while( j && i >= 0 ){
                    if( line[ i ] == ' ' ){
                        j--;
                        i--;
                        continue;
                    }
                    line[i] = 'E';
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
        int re = recu(&operations[actual_ope-1]);
        printf("%d", re);
    }

    fclose(fb);
    if (line) free(line);
    if (operations) free(operations);
    exit(EXIT_SUCCESS);

    return EXIT_SUCCESS;
}