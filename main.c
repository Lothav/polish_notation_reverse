#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "operation.h"
#include "stringBuffer.h"

#define EMPTY_CHAR 'E'
#define EMPTY_VALUE -1
#define G_VALUE -2
#define OPERATION_MISSING '?'

int main(int argc, char** argv) {

    FILE* fb = NULL;
    char* line = NULL;
    size_t len = 0;
    ssize_t line_size = 0;

    char * value = NULL;

    int * operators = (int *) malloc(2 * sizeof(int));

    Operation* operations = NULL;
    int op_count = 0;

    fb = fopen(argv[1], "r");
    if ( NULL == fb ) exit(EXIT_FAILURE);

    int i = 0, j = 0, id = 0;

    if ( -1 != (line_size = getline(&line, &len, fb))){
        int l = 0;
        line_size -= 2;
        while( NULL != (value = strtok(NULL == value ? line : NULL, " \n")) ){
            if( EMPTY_CHAR  == *value ) {
                i += 2;
                continue;
            }

            if( OPERATION_MISSING  == *value ) {

                recoverString(line, (int)line_size);

                operations = newOperation( operations, op_count, &id );
                setNewOperation( operators, operations, op_count );

                op_count++;

                line[i] = 'G';

                setStringBufferWithCustomChars(&i, line);

                value = NULL;
            } else {
                operators[l % 2] = * value == 'G' ? G_VALUE : atoi( value );
                i += strlen(value) + 1;
                l++;
            }
        }
        getline( &line, &len, fb );

        int result = atoi(line);
        char *str = (char *) calloc( (size_t) (op_count + 1), sizeof( char ) );

        for( j = 0; j < (0x2 << (op_count - 1)); j++ ){

            intToBin( j, str, op_count );
            convertBinToOperators( str, op_count );
            if( result == calcResultRecursion( operations, op_count-1, str ) ){
                printf( "%s\n", str );
            }

        }
        if( str ) free( str );
    }

    if( operators ) free( operators );
    fclose( fb );
    if ( line ) free( line );
    if ( operations ) free( operations );

    return EXIT_SUCCESS;
}