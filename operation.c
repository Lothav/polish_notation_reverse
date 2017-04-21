#include <stdlib.h>
#include "operation.h"

Operation * newOperation(Operation *operations, int op_count, int *id){

	// create a new operation struct object that will be a node on tree
    Operation * new_op = realloc(operations, (1 + op_count) * sizeof(Operation));

	// set default values
    new_op[op_count].id = (*id)++;
    new_op[op_count].number_a = EMPTY_VALUE;
    new_op[op_count].number_b = EMPTY_VALUE;
    new_op[op_count].grouped = 0;
    new_op[op_count].ind_a = EMPTY_VALUE;
    new_op[op_count].ind_b = EMPTY_VALUE;

	// return pointer
    return new_op;
}

void setNewOperationAsTreeNode(int *operators, Operation * operations, int op_count){
    if( operators[0] == GROUP_VALUE && operators[1] == GROUP_VALUE ) {
		// is a node with 2 sub nodes

		// first son is the last node
        operations[op_count].ind_a = op_count-1;
		// set as grouped
        operations[op_count-1].grouped = 1;

		// here, we need to get second son
		int op_queued = op_count-2;
        while( operations[op_queued].grouped ){
            // find first that's is not grouped
			op_queued--;
        }
        if( !operations[op_queued].grouped ){
         	// set as son
            operations[op_count].ind_b = op_queued;
            operations[op_queued].grouped = 1;
        }
    } else {
        if( operators[0] == GROUP_VALUE ){
			// first operator is a group
			// set last group as his son
            operations[op_count].ind_a = op_count-1;
            operations[op_count-1].grouped = 1;
        } else {
			// first operator is a number
            operations[op_count].number_a = operators[0];
        }

        if( operators[1] == GROUP_VALUE ){
			// second operator is a group
			// set last group as his son
            operations[op_count].ind_b = op_count-1;
            operations[op_count-1].grouped = 1;
        } else {
			// second operator is a number
			operations[op_count].number_b = operators[1];
        }
    }
}


int calcResultRecursion(Operation * operations, int index, char *str){
    if(operations[index].ind_b != EMPTY_VALUE && operations[index].ind_a != EMPTY_VALUE){
		// node has 2 sub-nodes
		// split in two recursions
        return str[operations[index].id] == OPERATION_PLUS ?
			   // operation plus
               (calcResultRecursion(operations, operations[index].ind_b, str) + calcResultRecursion(operations, operations[index].ind_a, str)) :
               // operation multiply
			   (calcResultRecursion(operations, operations[index].ind_b, str) * calcResultRecursion(operations, operations[index].ind_a, str));
    }

    if(operations[index].number_a != EMPTY_VALUE && operations[index].number_b != EMPTY_VALUE){
		// node has 2 number
		// just return their sum or multiply
        return str[operations[index].id] == OPERATION_PLUS ?
			   // operation plus
			   (operations[index].number_a + operations[index].number_b) :
			   // operation multiply
			   (operations[index].number_a * operations[index].number_b);
    }

	// if node doest has 2 number or 2 sub-nodes, he has a number and a sub-node

	// get which number is not null
    int _not_empty = (operations[index].number_a == EMPTY_VALUE ? operations[index].number_b : operations[index].number_a);

	// now, find which sub-node is set

	if(operations[index].ind_a != EMPTY_VALUE){
		// if sub-node a is set
		// return the number plus or multiply a recursion
		return str[operations[index].id] == OPERATION_PLUS ?
			   // operation plus
			   (_not_empty + calcResultRecursion(operations, operations[index].ind_a, str)) :
			   // operation multiply
			   (_not_empty * calcResultRecursion(operations, operations[index].ind_a, str));
	}

    if(operations[index].ind_b != EMPTY_VALUE){
    	// if sub-node b is set
		// return the number plus or multiply a recursion
		return str[operations[index].id] == OPERATION_PLUS ?
			   // operation plus
			   (_not_empty + calcResultRecursion(operations, operations[index].ind_b, str)) :
			   // operation multiply
			   (_not_empty * calcResultRecursion(operations, operations[index].ind_b, str));
    }

	// just a default return to prevent compiling warnings (this will not happening in normal conditions)
    return EMPTY_VALUE;
}
