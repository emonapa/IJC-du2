CC = gcc
CFLAGS = -g -pedantic -Wall -Wextra
LDFLAGS = -Wall -Wextra
LIBS = -lm
TARGETS = tail libhtab.a libhtab.so wordcount wordcount-dynamic io

.PHONY: all run clean

# Default target
all: $(TARGETS)

build: $(TARGETS)

run: $(TARGETS)
	./tail

# Remove objects and executable files
clean:
	rm -f $(TARGETS) *.o

# Rules for compiling source files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

tail: cbuf.o tail.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) -c -o $@ $^ -static -fPIC

htab_init.o: htab_init.c htab.h
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) -o $@ $^

htab_lookup_add.o: htab_lookup_add.c htab.h
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

htab_statistics.o: htab_statistics.c htab.h
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

libhtab.a: htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_size.o htab_statistics.o
	ar rcs $@ $^

libhtab.so: htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_size.o htab_statistics.o
	$(CC) -fPIC -shared -o $@ $^

io: io.c htab.h
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)