all:
   gcc main.c operations.c stringBuffer.c utils.c -o exe -Wall -std=c99
clean:
   rm ./exe
