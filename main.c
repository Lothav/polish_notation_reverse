#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPERATION_MISSING '?'

typedef struct{
    int a;
    int b;
    struct Operation *op_a;
    struct Operation *op_b;
} Operation;


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

    int i = 0;
    while ( -1 != (line_size = getline(&line, &len, fb))){
        while( NULL != (value = strtok(NULL == value ? line : NULL, " \n")) ){

            if( OPERATION_MISSING  == *value ) {
                operations = realloc(operations, (1+actual_ope) * sizeof(Operation));
                operations[actual_ope].a = operators[0];
                operations[actual_ope].b = operators[1];
                operations[actual_ope].op_a = NULL;
                operations[actual_ope].op_b = NULL;

                i = 0;
            } else {
                operators[i % 2] = atoi( value );
                i++;
            }
        }
    }

    fclose(fb);
    if (line) free(line);
    if (operations) free(operations);
    exit(EXIT_SUCCESS);

    return EXIT_SUCCESS;
}