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

int main() {

    // initialize default values
    char * line = malloc(51 * sizeof(int));
    char * value = NULL;
    // 'operators' is the buffer that will get both numbers from input
    int * operators = (int *) malloc(2 * sizeof(int));

    // Operation struct array
    Operation* operations = NULL;

    // initialize counter variables
    int i = 0, j = 0, id = 0, op_count = 0, result;

	scanf("%[^\n]s", line);

    // get first line as char* from file
    if ( strlen(line) ){

        // first principal loop
        while( NULL != (value = strtok(NULL == value ? line : NULL, " \n")) ){
            if( EMPTY_CHAR  == *value ) {
                i += strlen( value ) + 1;
                continue;
            }

            if( OPERATION_MISSING  == *value ) {

                recoverString(line, 50);

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

		scanf("%d", &result);

        char *str = (char *) calloc( (size_t) (op_count + 1), sizeof( char ) );

        // second principal loop
        for( j = 0; j < (0x2 << (op_count - 1)); j++ ){

            intToBin( j, str, op_count );
            if( result == calcResultRecursion( operations, op_count-1, str ) ){
                printf( "%s\n", str );
            }

        }
        if( str ) free( str );
    }

	if( operations ){
		free(operations);
	}
    if( operators ) {
        free(operators);
    }
    if( line ){
		free(line);
	}

    return EXIT_SUCCESS;
}