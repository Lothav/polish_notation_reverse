#ifndef POLISH_NOTATION_REVERSE_STRINGBUFFER_H
#define POLISH_NOTATION_REVERSE_STRINGBUFFER_H

#define EMPTY_CHAR 'E'
#define GROUP_CHAR 'G'
#define MAX_CHAR 201

// recover string that strtok messed up
// basically, find \0 and set as space
void recoverString(char *str);

// set the buffer string with :
// - '?' to 'G'
// - and last two valid characters to 'E'
void setStringBufferWithCustomChars(int *i, char * line);

#endif //POLISH_NOTATION_REVERSE_STRINGBUFFER_H
