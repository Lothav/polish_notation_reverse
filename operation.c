#include <stdlib.h>
#include "operation.h"

Operation * newOperation(Operation *operations, int op_count, int *id){

    Operation * new_op = realloc(operations, (1 + op_count) * sizeof(Operation));

    new_op[op_count].id = (*id)++;
    new_op[op_count].a = EMPTY_VALUE;
    new_op[op_count].b = EMPTY_VALUE;
    new_op[op_count].grouped = 0;
    new_op[op_count].ind_a = EMPTY_VALUE;
    new_op[op_count].ind_b = EMPTY_VALUE;

    return new_op;
}

void setNewOperationAsTreeNode(int *operators, Operation * operations, int op_count){
    if( operators[0] == GROUP_VALUE && operators[1] == GROUP_VALUE ) {
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
        if( operators[0] == GROUP_VALUE ){
            operations[op_count].ind_a = op_count-1;
            operations[op_count-1].grouped = 1;
        } else {
            operations[op_count].a = operators[0];
        }

        if( operators[1] == GROUP_VALUE ){
            operations[op_count].ind_b = op_count-1;
            operations[op_count-1].grouped = 1;
        } else {
            operations[op_count].b = operators[1];
        }
    }
}


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
    return EMPTY_VALUE;
}
