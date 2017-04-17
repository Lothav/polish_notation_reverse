#define _GNU_SOURCE
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

	(void)argc;

    // initialize default values
    FILE* fb = NULL;
    char* line = NULL;
    size_t len = 0;
    int line_size = 0;
    char * value = NULL;

    // 'operators' is the buffer that will get both numbers from input
    int * operators = (int *) malloc(2 * sizeof(int));

    // Operation struct array
    Operation* operations = NULL;

    // initialize counter variables
    int i = 0, j = 0, id = 0, op_count = 0;

    fb = fopen(argv[1], "r");
    if ( NULL == fb ) exit(EXIT_FAILURE);

    // get first line as char* from file
    if ( -1 != (line_size = (int) getline(&line, &len, fb)) ){

        while( NULL != (value = strtok(NULL == value ? line : NULL, " \n")) ){
            if( EMPTY_CHAR  == *value ) {
                i += strlen( value ) + 1;
                continue;
            }

            if( OPERATION_MISSING  == *value ) {

                recoverString(line, line_size);

                operations = newOperation( operations, op_count, &id );
                setNewOperation( operators, operations, op_count );

                op_count++;


                setStringBufferWithCustomChars(&i, line);

                value = NULL;
            } else {

                operators[j % 2] = * value == 'G' ? G_VALUE : atoi( value );
                i += strlen( value ) + 1;
                j++;
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