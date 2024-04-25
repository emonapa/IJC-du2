#include "htab.h"
#include <stdlib.h>
#include <stdio.h>

struct htab {
    size_t arr_size;        // Velikost pole
    size_t size;            // Počet prvků v tabulce
    htab_pair_t **array;    // Pole ukazatelů na prvky tabulky
};

htab_t *htab_init(const size_t n) {
    htab_t *table = (htab_t *)malloc(sizeof(htab_t));
    if (table == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    table->arr_size = n;
    table->size = 0;
    table->array = (htab_pair_t **)calloc(n, sizeof(htab_pair_t *));
    if (table->array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(table);
        exit(EXIT_FAILURE);
    }

    return table;
}