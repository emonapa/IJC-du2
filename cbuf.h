#ifndef CBUF_H
#define CBUF_H

typedef struct CircularBuffer{
    char **buffer;
    int size;
    int start;
    int end;
    int count;
} CircularBuffer;


CircularBuffer *cbuf_create(int n);
void cbuf_put(CircularBuffer *cb, char *line);
char *cbuf_get(CircularBuffer *cb);
void cbuf_free(CircularBuffer *cb);

#endif /* CBUF_H */
