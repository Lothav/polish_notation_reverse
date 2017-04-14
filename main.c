#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPERATION_MISSING '?'

typedef struct{
    int a;
    int b;
    struct Operation *op;
} Operation;


int main(int argc, char** argv) {

    FILE* fb;
    char* line = NULL;
    size_t len = 0;
    ssize_t line_size;

    char * value;

    Operation* operations = (Operation *) malloc( sizeof(Operation) );

    int i;

    fb = fopen(argv[1], "r");
    if ( NULL == fb ) exit(EXIT_FAILURE);

    while ( (line_size = getline(&line, &len, fb)) != -1 ){
        while( (value = strtok(line, " ")) != NULL ){
            if( *value != OPERATION_MISSING ){

            }
        }
    
        printf("%s", line);
    }

    fclose(fb);
    if (line) free(line);
    exit(EXIT_SUCCESS);

    return EXIT_SUCCESS;
}