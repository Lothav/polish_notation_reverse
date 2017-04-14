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

    Operation* operations = (Operation *) malloc( sizeof(Operation) );
    int actual_ope = 0;

    int i;

    fb = fopen(argv[1], "r");
    if ( NULL == fb ) exit(EXIT_FAILURE);

    while ( (line_size = getline(&line, &len, fb)) != -1 ){
        while( (value = strtok(NULL == value ? line : NULL, " \n")) != NULL ){
            if( *value == OPERATION_MISSING ){

            } else {
                operations = realloc(operations, (1+actual_ope) * sizeof(Operation));
                operations[actual_ope].a = atoi( value );
                actual_ope++;
            }
        }
    }

    fclose(fb);
    if (line) free(line);
    exit(EXIT_SUCCESS);

    return EXIT_SUCCESS;
}