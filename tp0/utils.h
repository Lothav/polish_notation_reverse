#ifndef POLISH_NOTATION_REVERSE_UTILS_H
#define POLISH_NOTATION_REVERSE_UTILS_H

/*
 * convert a decimal number num to a sequence of operators
 * ex.: num = 5
 * binary of 5 = 101
 * so, str will be set as "+*+"
 * (0's are set as '+' and 1's are set as *)
 *
*/
void convertNumberToOperator(int num, char *str, int op_count);

#endif //POLISH_NOTATION_REVERSE_UTILS_H
