#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    FILE* fb;
    char* line = NULL;
    size_t len = 0;
    ssize_t line_size;

    fb = fopen(argv[1], "r");
    if ( NULL == fb ) exit(EXIT_FAILURE);

    while ( (line_size = getline(&line, &len, fb)) != -1 ){
        printf("line length %zu :\n", line_size);
        printf("%s", line);
    }

    fclose(fb);
    if (line) free(line);
    exit(EXIT_SUCCESS);

    return EXIT_SUCCESS;
}