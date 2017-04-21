#ifndef POLISH_NOTATION_REVERSE_OPERATION_H
#define POLISH_NOTATION_REVERSE_OPERATION_H

#define EMPTY_VALUE -1
#define GROUP_VALUE -2
#define OPERATION_PLUS '+'

typedef struct Operation{
    int id;
    int grouped;
    int a;
    int b;
    int ind_a;
    int ind_b;
} Operation;

Operation * newOperation(Operation *operations, int op_count, int *id);
void setNewOperationAsTreeNode(int *operators, Operation * operations, int op_count);
int calcResultRecursion(Operation * operations, int index, char *str);

#endif //POLISH_NOTATION_REVERSE_OPERATION_H
