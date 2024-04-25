#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cbuf.h"

#define DEFAULT_LINES 10
#define MAX_LINE_LENGTH 200

void print_last_lines(FILE *file, int num_lines, unsigned int max_length) {
    CircularBuffer *cb = cbuf_create(num_lines);

    char *tempBuffer = (char *)malloc(max_length * sizeof(char) + 1);
    char c;
    unsigned int i = 0;
    char last_while = 1;
    char was_enter = 0;
    while (last_while) {
        c = fgetc(file);
        tempBuffer[i] = c;
        if (i >= max_length) {
            //error
            exit(1);
        } else if ((c == '\n')) {
            tempBuffer[i+1] = '\0';
            cbuf_put(cb, tempBuffer);
            i = 0;
            was_enter = 1;
            continue;
        } else if ((c == EOF) && !was_enter){
            last_while = 0;
            tempBuffer[i] = '\0';
            cbuf_put(cb, tempBuffer);
            break;
        } else if (c == EOF) {
            break;
        }
        was_enter = 0;
        i++;
    }

    free(tempBuffer);

    cb->start = cb->end;
    while (num_lines > 0) {
        char *line = cbuf_get(cb);
        if (line != NULL) {
            printf("%s", line);
            num_lines--;
        } else {
            break; // Pokud není žádný další řádek v bufferu, skončete s cyklem
        }
    }
    cbuf_free(cb);
}

int main(int argc, char *argv[]) {
    if (argc > 4) {
        fprintf(stderr, "Too many arguments.\n");
        return 1;
    }

    FILE *file;
    int num_lines = DEFAULT_LINES;
    unsigned int max_length = MAX_LINE_LENGTH;
    int file_index = -1;

    if (argc == 4) {
        num_lines = atoi(argv[2]);
        file_index = 3;
    } else if (argc == 3) {
        num_lines = atoi(argv[2]);
    } else if (argc == 2) {
        file_index = 1;
    }

    if (num_lines <= 0) {
        fprintf(stderr, "Number of lines is invalid.\n");
        return 1;
    }
    
    // Open file or use stdin
    if (file_index != -1 && argc > file_index) {
        file = fopen(argv[file_index], "r");
        if (file == NULL) {
            fprintf(stderr, "File can't be opened.\n");
            return 1;
        }
    } else {
        file = stdin;
    }

    // Print last lines
    print_last_lines(file, num_lines, max_length);

    // Close file if it's not stdin
    if (file != stdin) {
        fclose(file);
    }

    return EXIT_SUCCESS;
}
