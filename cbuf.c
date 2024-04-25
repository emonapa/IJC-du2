#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cbuf.h"

#define MAX_LINE_LENGTH 200
char *strdup(const char *s);

CircularBuffer *cbuf_create(int n) {
    CircularBuffer *cb = (CircularBuffer *)malloc(sizeof(CircularBuffer));    

    if (cb == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    cb->buffer = (char **)malloc(n * sizeof(char *));
    if (cb->buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    cb->size = n;
    cb->start = 0;
    
    cb->end = 0;
    cb->count = 0;
    return cb;
}

void cbuf_put(CircularBuffer *cb, char *line) {
    if (cb->count >= cb->size) {
        free(cb->buffer[cb->end]);
    }
    cb->count++;
    cb->buffer[cb->end] = strdup(line);
    cb->end = (cb->end + 1) % cb->size;
}


char *cbuf_get(CircularBuffer *cb) {
    if (cb->count == 0) {
        return NULL;
    }
    char *line = cb->buffer[cb->start];
    cb->start = (cb->start + 1) % cb->size;
    return line;
}


void cbuf_free(CircularBuffer *cb) {
    for (int i = 0; i < cb->size; i++) {
        free(cb->buffer[i]);
    }
    free(cb->buffer);
    free(cb);
}