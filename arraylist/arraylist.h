#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct ArrayList ArrayList;

typedef enum {
    AL_OK = 0,
    AL_INVALID_ARGUMENT,
    AL_OVERFLOW,
    AL_ALLOCATION_FAILED,
    AL_NOT_FOUND
} ArrayListStatus;

ArrayList* arraylist_create(size_t type_size, size_t capacity);
ArrayListStatus
arraylist_init(ArrayList* list, size_t type_size, size_t capacity);
void arraylist_destroy(ArrayList* list);
bool arraylist_deinit(ArrayList* list);
ArrayListStatus arraylist_extend(ArrayList* list, void* data, size_t items_n);
ArrayListStatus arraylist_append(ArrayList* list, void* element);
ArrayListStatus arraylist_find(
    ArrayList* list,
    bool (*comparison_func)(void* element, size_t argc, void* args),
    size_t argc,
    void*  args,
    void** output
);
ArrayListStatus arraylist_get(ArrayList* list, size_t idx, void** output);
ArrayListStatus arraylist_get_copy(ArrayList* list, size_t idx, void* output);
ArrayListStatus arraylist_insert(ArrayList* list, size_t idx, void* element);
ArrayListStatus arraylist_delete(
    ArrayList* list,
    bool (*comparison_function)(void* element, size_t argc, void* args),
    size_t argc,
    void*  args
);
ArrayListStatus arraylist_delete_by_idx(ArrayList* list, size_t idx);

#endif
