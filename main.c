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
    int grouped;
    int a;
    int b;
    int ind_a;
    int ind_b;
} Operation;

int calcResultRecursion(Operation * operations, int index, char *str){
    if(operations[index].ind_b != EMPTY_VALUE && operations[index].ind_a != EMPTY_VALUE){
        return str[operations[index].id] == OPERATION_PLUS ?
               (calcResultRecursion(operations, operations[index].ind_b, str) + calcResultRecursion(operations, operations[index].ind_a, str)) :
               (calcResultRecursion(operations, operations[index].ind_b, str) * calcResultRecursion(operations, operations[index].ind_a, str));
    }

    if(operations[index].a != EMPTY_VALUE && operations[index].b != EMPTY_VALUE){
        return str[operations[index].id] == OPERATION_PLUS ?
               (operations[index].a + operations[index].b) :
               (operations[index].a * operations[index].b);
    }

    int _not_empty = (operations[index].a == EMPTY_VALUE ? operations[index].b : operations[index].a);

    if(operations[index].ind_b != EMPTY_VALUE){
        return str[operations[index].id] == OPERATION_PLUS ?
               (_not_empty + calcResultRecursion(operations, operations[index].ind_b, str)) :
               (_not_empty * calcResultRecursion(operations, operations[index].ind_b, str));
    }

    if(operations[index].ind_a != EMPTY_VALUE){
        return str[operations[index].id] == OPERATION_PLUS ?
               (_not_empty + calcResultRecursion(operations, operations[index].ind_a, str)) :
               (_not_empty * calcResultRecursion(operations, operations[index].ind_a, str));
    }
}

void intToBin(int num, char *str, int op_count) {
    int mask = 0x2 << op_count - 1;
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
    int op_count = 0;

    fb = fopen(argv[1], "r");
    if ( NULL == fb ) exit(EXIT_FAILURE);

    int i = 0, j = 0, k = 0, id = 0;


    if ( -1 != (line_size = getline(&line, &len, fb))){
        int l = 0;
        line_size -= 2;
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

                operations = realloc(operations, (1 + op_count) * sizeof(Operation));

                operations[op_count].id = id++;
                operations[op_count].a = EMPTY_VALUE;
                operations[op_count].b = EMPTY_VALUE;
                operations[op_count].grouped = 0;
                operations[op_count].ind_a = EMPTY_VALUE;
                operations[op_count].ind_b = EMPTY_VALUE;

                if( operators[0] == G_VALUE && operators[1] == G_VALUE ) {
                    operations[op_count].ind_a = op_count-1;
                    operations[op_count-1].grouped = 1;
                    int op_queued = op_count-2;
                    while( operations[op_queued].grouped ){
                        op_queued--;
                    }
                    if( !operations[op_queued].grouped ){
                        operations[op_count].ind_b = op_queued;
                        operations[op_queued].grouped = 1;
                    }
                } else {
                    if( operators[0] == G_VALUE ){
                        operations[op_count].ind_a = op_count-1;
                        operations[op_count-1].grouped = 1;
                    } else {
                        operations[op_count].a = operators[0];
                    }

                    if( operators[1] == G_VALUE ){
                        operations[op_count].ind_b = op_count-1;
                        operations[op_count-1].grouped = 1;
                    } else {
                        operations[op_count].b = operators[1];
                    }
                }
                if( j == line_size ){
                    break;
                }
                op_count++;

                line[j] = 'G';

                i--;
                j = 2;
                while( j && i >= 0 ){
                    if( line[ i ] != ' ' && line[ i ] != EMPTY_CHAR ){
                        if( line[ i+1 ] == ' ' ) j--;
                        int t = i;
                        while( line[t] != ' ' && t >= 0 ){
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