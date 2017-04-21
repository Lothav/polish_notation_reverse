#ifndef POLISH_NOTATION_REVERSE_OPERATION_H
#define POLISH_NOTATION_REVERSE_OPERATION_H

#define EMPTY_VALUE -1
#define GROUP_VALUE -2
#define OPERATION_PLUS '+'

typedef struct Operation{
    int id; 		// identification of tree node
    int grouped;	// boolean, true if already grouped
    int number_a;	// first number
    int number_b;	// second number
    int ind_a;		// the index for this node first child in the tree
    int ind_b;		// the index for this node second child in the tree
} Operation;

// create a new Operation object struct
Operation * newOperation(Operation *operations, int op_count, int *id);

// 'put' the new Operation object on the tree
void setNewOperationAsTreeNode(int *operators, Operation * operations, int op_count);

// calc the recursion value for the operators sequences passed on str
int calcResultRecursion(Operation * operations, int index, char *str);

#endif //POLISH_NOTATION_REVERSE_OPERATION_H
