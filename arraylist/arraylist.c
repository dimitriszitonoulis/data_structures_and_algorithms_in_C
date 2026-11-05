#include "arraylist.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct ArrayList {
    void*  data;      // array containing the data of the list
    size_t type_size; // the size of each item of data
    size_t size;      // how many elements are in the list
    size_t capacity;  // how many elements can fit in the list
} ArrayList;

static bool _is_list_valid(ArrayList* list);
static ArrayListStatus _resize(ArrayList* list, size_t items_n);
static ArrayListStatus _shift_right(ArrayList* list, size_t idx);
static ArrayListStatus _shift_left(ArrayList* list, size_t idx);
static ArrayListStatus _get_index(
    ArrayList* list,
    bool (*comparison_func)(void* element, size_t argc, void* args),
    size_t  argc,
    void*   args,
    size_t* output
);
static ArrayListStatus _get(ArrayList* list, size_t idx, void** output);
static ArrayListStatus _delete(ArrayList* list, size_t idx);

/**
 * @brief Checks whether an array list has a valid internal state.
 *
 * @param list Pointer to the array list to validate.
 * @return true if the list structure and its storage metadata are valid;
 *         false otherwise.
 */
static bool _is_list_valid(ArrayList* list) {

    if (list == NULL) {
        return false;
    }

    if (list->size > list->capacity) {
        return false;
    }

    if (list->type_size == 0) {
        return false;
    }

    if (list->capacity > SIZE_MAX / list->type_size) {
        return false;
    }

    // Since list->size < list-> capacity, I do not need to check
    // list->size > SIZE_MAX / list->type_size

    // if a list says it has allocated storage
    // list->data must not be NULL
    if (list->data == NULL && list->capacity != 0) {
        return false;
    }

    return true;
}

/**
 * @brief Ensures that the list has room for additional elements.
 *
 * The capacity is increased as needed, generally by doubling the current
 * capacity.
 * If the capacity cannot be doubled then the requested number of additional
 * slots is added to the current capacity.
 *
 * @param list Pointer to the array list to resize.
 * @param items_n Number of additional element slots to make available.
 * @return AL_OK on success, AL_INVALID_ARGUMENT if the list is invalid,
 *         AL_OVERFLOW if the required capacity cannot be represented, or
 *         AL_ALLOCATION_FAILED if memory allocation fails.
 */
static ArrayListStatus _resize(ArrayList* list, size_t items_n) {

    if (!_is_list_valid(list)) {
        return AL_INVALID_ARGUMENT;
    }

    // will the new capacity fit in memory?
    if (list->capacity > SIZE_MAX - items_n) {
        return AL_OVERFLOW;
    }

    size_t required_capacity = list->capacity + items_n;
    size_t max_capacity      = SIZE_MAX / list->type_size;

    if (required_capacity > max_capacity) {
        return AL_OVERFLOW;
    }

    size_t new_capacity = list->capacity == 0 ? 1 : list->capacity;

    while (new_capacity < required_capacity) {

        if (new_capacity > max_capacity / 2) {
            new_capacity = required_capacity;
            break;
        }

        new_capacity = new_capacity * 2;
    }

    // this is valid because new_capacity <= max_capacity
    size_t new_capacity_bytes = new_capacity * list->type_size;

    void* tmp = realloc(list->data, new_capacity_bytes);

    if (tmp == NULL) {
        return AL_ALLOCATION_FAILED;
    }

    list->data     = tmp;
    list->capacity = new_capacity;

    return AL_OK;
}

/**
 * @brief shifts the elements at and after an index one position to the right.
 *
 * The element after idx is overwritten by the previous element. The element
 * at index is not explicitly removed.
 * Grows the list's storage if it is currently full.
 * The list's size is not changed.
 *
 * @param list pointer to the array list to modify.
 * @param idx index at which the right shift begins; may equal list->size.
 * @return al_ok on success, al_invalid_argument if the list is invalid or
 *         idx is greater than list->size, or an error returned by _resize().
 */
static ArrayListStatus _shift_right(ArrayList* list, size_t idx) {

    if (!_is_list_valid(list) || idx > list->size) {
        return AL_INVALID_ARGUMENT;
    }

    // if true the list will need to be resized
    if (list->size == list->capacity) {
        ArrayListStatus s = _resize(list, 1);
        if (s != AL_OK) {
            return s;
        }
    }

    const size_t size      = list->size;
    const size_t type_size = list->type_size;

    char* data = list->data; // 1st byte of data

    memmove(
        data + (idx + 1) * type_size, data + idx * type_size,
        (size - idx) * type_size
    );

    return AL_OK;
}

/**
 * @brief Shifts all elements after an index one position to the left.
 *
 * The element at idx is overwritten by the following element. The final
 * element is not explicitly removed, and the list's size is not changed.
 *
 * @param list Pointer to the array list to modify.
 * @param idx Index of the element to overwrite; must be less than list->size.
 * @return AL_OK on success, or AL_INVALID_ARGUMENT if the list is invalid
 *         or idx is out of range.
 */
static ArrayListStatus _shift_left(ArrayList* list, size_t idx) {
    if (!_is_list_valid(list) || idx >= list->size) {
        return AL_INVALID_ARGUMENT;
    }

    size_t size      = list->size;
    size_t type_size = list->type_size;

    // 1st byte of data
    char* data = list->data;
    memmove(
        data + idx * type_size, data + (idx + 1) * type_size,
        (size - idx - 1) * type_size
    );

    return AL_OK;
}

/**
 * @brief Finds the index of the first element accepted by a comparison
 * callback.
 *
 * The callback is invoked for each element, in order, until it returns true.
 *
 * @param list Pointer to the array list to search.
 * @param comparison_func Callback that tests an element. It receives the
 *        element pointer, argc, and args.
 * @param argc Number of arguments described by args and passed to the callback.
 * @param args Pointer to callback-specific arguments.
 * @param output Receives the index of the first matching element.
 * @return AL_OK if a match is found, AL_NOT_FOUND if no element matches, or
 *         AL_INVALID_ARGUMENT if an argument is invalid.
 */
static ArrayListStatus _get_index(
    ArrayList* list,
    bool (*comparison_func)(void* element, size_t argc, void* args),
    size_t  argc,
    void*   args,
    size_t* output
) {
    if (!_is_list_valid(list) || comparison_func == NULL || output == NULL) {
        return AL_INVALID_ARGUMENT;
    }

    for (size_t i = 0; i < list->size; i++) {
        void* element = (char*)list->data + i * list->type_size;

        if (comparison_func(element, argc, args)) {
            *output = i;
            return AL_OK;
        }
    }

    return AL_NOT_FOUND;
}

/**
 * @brief Obtains a pointer to an element at the specified index.
 *
 * The returned pointer refers to storage owned by the list and must not be
 * freed by the caller.
 *
 * @param list Pointer to the array list.
 * @param idx Index of the element to retrieve; must be less than list->size.
 * @param output Receives a pointer to the requested element.
 * @return AL_OK on success, or AL_INVALID_ARGUMENT if the list is invalid,
 *         the index is out of range, or output is NULL.
 */
static ArrayListStatus _get(ArrayList* list, size_t idx, void** output) {

    if (!_is_list_valid(list) || idx >= list->size || output == NULL) {
        return AL_INVALID_ARGUMENT;
    }
    *output = (char*)list->data + idx * list->type_size;
    return AL_OK;
}

/**
 * @brief Removes the element at the specified index.
 *
 * Elements after idx are shifted left and the list size is decremented.
 *
 *
 * @param list Pointer to the array list to modify.
 * @param idx Index of the element to remove.
 * @return AL_OK on success, AL_INVALID_ARGUMENT if the list is invalid or
 *         idx is out of range, or an error returned by _shift_left().
 */
static ArrayListStatus _delete(ArrayList* list, size_t idx) {

    if (!_is_list_valid(list) || idx >= list->size) {
        return AL_INVALID_ARGUMENT;
    }

    ArrayListStatus s = _shift_left(list, idx);

    if (s != AL_OK) {
        return s;
    }

    list->size -= 1;
    return AL_OK;
}

// TODO I should set capacity on my own
/**
 * @brief Allocates and initializes a new array list.
 *
 * Both the list structure and its backing storage are allocated dynamically.
 *
 * @param type_size Size in bytes of each element.
 * @param capacity Initial number of elements the list can hold.
 * @return Pointer to the initialized list, or NULL if allocation or
 *         initialization fails.
 */
ArrayList* arraylist_create(size_t type_size, size_t capacity) {

    ArrayList* list = malloc(sizeof(*list));

    if (list == NULL) {
        return NULL;
    }

    ArrayListStatus s = arraylist_init(list, type_size, capacity);
    if (s != AL_OK || !_is_list_valid(list)) {
        free(list);
        return NULL;
    }

    return list;
}

/**
 * @brief Initializes an existing array list structure.
 *
 * Allocates backing storage when capacity is nonzero and sets the list size
 * to zero. The structure must not already own allocated storage.
 * This function should not be called twice on the same list
 * because list->data will leak memory.
 *
 * @param list Pointer to the array list structure to initialize.
 * @param type_size Size in bytes of each element; must be greater than zero.
 * @param capacity Initial number of elements the list can hold.
 * @return AL_OK on success, AL_INVALID_ARGUMENT for invalid arguments,
 *         AL_OVERFLOW if the allocation size would overflow, or
 *         AL_ALLOCATION_FAILED if backing-storage allocation fails.
 */
ArrayListStatus
arraylist_init(ArrayList* list, size_t type_size, size_t capacity) {

    if (list == NULL || type_size == 0) {
        return AL_INVALID_ARGUMENT;
    }

    if (capacity > SIZE_MAX / type_size) {
        return AL_OVERFLOW;
    }

    void* data = NULL;
    if (capacity > 0) {
        data = malloc(capacity * type_size);

        if (data == NULL) {
            return AL_ALLOCATION_FAILED;
        }
    }

    list->data      = data;
    list->type_size = type_size;
    list->size      = 0;
    list->capacity  = capacity;

    return AL_OK;
}

/**
 * @brief Deinitializes and frees an array list allocated by arraylist_create().
 *
 * This function frees both the list's backing storage and the list structure.
 * Do not call it for a list structure that was not dynamically allocated.
 *
 * @param list Pointer to the dynamically allocated array list; NULL is ignored.
 */
void arraylist_destroy(ArrayList* list) {

    if (list == NULL) {
        return;
    }

    if (!arraylist_deinit(list)) {
        return;
    }

    free(list);
}

// does not free(list)
// assumes list is initialized
/**
 * @brief Releases an array list's backing storage and resets its fields.
 *
 * The ArrayList structure itself is not freed.
 *
 * @param list Pointer to the array list to deinitialize.
 * @return true if list is non-NULL and was reset; false if list is NULL.
 */
bool arraylist_deinit(ArrayList* list) {

    if (list == NULL) {
        return false;
    }

    free(list->data);
    list->data      = NULL;
    list->type_size = 0;
    list->size      = 0;
    list->capacity  = 0;

    return true;
}

// Appends multiple elements at the end of the arraylist
// Because of realloc() my array list does not support overlapping memory
// regions, memcpy() also does not support overlapping memory regions
/**
 * @brief Appends multiple elements to the end of an array list.
 *
 * Copies items_n elements from data into the list, increasing its size.
 * The source memory must not overlap the list's backing storage.
 *
 * @param list Pointer to the array list to extend.
 * @param data Pointer to the first source element.
 * @param items_n Number of elements to append; must be greater than zero.
 * @return AL_OK on success, AL_INVALID_ARGUMENT for invalid arguments,
 *         AL_OVERFLOW if a size calculation overflows, or an allocation
 *         error returned by _resize().
 */
ArrayListStatus arraylist_extend(ArrayList* list, void* data, size_t items_n) {

    if (!_is_list_valid(list) || (items_n > 0 && data == NULL) ||
        items_n == 0 || list->type_size == 0) {
        return AL_INVALID_ARGUMENT;
    }

    // does the size of the new items in bytes fit?
    if (items_n > SIZE_MAX / list->type_size) {
        return AL_OVERFLOW;
    }

    size_t bytes_n = items_n * list->type_size;

    // does the new size of the list fit?
    if (list->size > SIZE_MAX - items_n) {
        return AL_OVERFLOW;
    }

    size_t new_size = list->size + items_n;

    // does the list have enough space?
    if (new_size > list->capacity) {
        size_t additional_items = new_size - list->capacity;

        ArrayListStatus s = _resize(list, additional_items);

        if (s != AL_OK) {
            return s;
        }
    }

    char* destination = (char*)list->data + list->size * list->type_size;
    memcpy(destination, data, bytes_n);

    list->size = new_size;
    return AL_OK;
}

/**
 * @brief Appends one element to the end of an array list.
 *
 * @param list Pointer to the array list to modify.
 * @param data Pointer to the element to copy into the list.
 * @return AL_OK on success, or an error returned by arraylist_extend().
 */
ArrayListStatus arraylist_append(ArrayList* list, void* data) {
    if (!_is_list_valid(list)) {
        return AL_INVALID_ARGUMENT;
    }

    return arraylist_extend(list, data, 1);
}

/**
 * @brief Finds the first element that satisfies a comparison callback.
 *
 * The returned element pointer is owned by the list and must not be freed.
 * It may become invalid if a later operation (ex _resize()) reallocates
 * the list's storage.
 *
 * @param list Pointer to the array list to search.
 * @param comparison_func Callback that tests an element. It receives the
 *        element pointer, argc, and args.
 * @param argc Number of arguments described by args and passed to the callback.
 * @param args Pointer to callback-specific arguments.
 * @param output Receives a pointer to the first matching element.
 * @return AL_OK if a match is found, AL_NOT_FOUND if no element matches, or
 *         an error returned by the internal lookup functions.
 */
ArrayListStatus arraylist_find(
    ArrayList* list,
    bool (*comparison_func)(void* element, size_t argc, void* args),
    size_t argc,
    void*  args,
    void** output
) {

    if (output == NULL) {
        return AL_INVALID_ARGUMENT;
    }

    size_t index;

    ArrayListStatus status =
        _get_index(list, comparison_func, argc, args, &index);

    if (status != AL_OK) {
        return status;
    }

    return _get(list, index, output);
}

// returns a pointer to the item at idx if it exists
// If extend is called and the list is resized and moved by realloc
// the pointer returned might get invalidated
/**
 * @brief Gets a pointer to the element at the specified index.
 *
 * The pointer is owned by the list and must not be freed. It may be
 * invalidated if an operation such as arraylist_extend() reallocates storage.
 *
 * @param list Pointer to the array list.
 * @param idx Index of the element to retrieve.
 * @param output Receives a pointer to the requested element.
 * @return AL_OK on success, or an error returned by _get().
 */
ArrayListStatus arraylist_get(ArrayList* list, size_t idx, void** output) {
    return _get(list, idx, output);
}

/**
 * @brief Copies the element at the specified index into caller-provided memory.
 *
 * The destination must have room for at least list->type_size bytes.
 *
 * @param list Pointer to the array list.
 * @param idx Index of the element to copy.
 * @param output Destination buffer that receives the element's bytes.
 * @return AL_OK on success, AL_INVALID_ARGUMENT if output is NULL, or an
 *         error returned by the internal element lookup.
 */
ArrayListStatus arraylist_get_copy(ArrayList* list, size_t idx, void* output) {

    if (output == NULL) {
        return AL_INVALID_ARGUMENT;
    }

    void* element = NULL;

    ArrayListStatus s = _get(list, idx, &element);

    if (s != AL_OK) {
        return s;
    }

    memcpy(output, element, list->type_size);

    return AL_OK;
}

// does not allow to insert at size
// list->size = (index of element) + 1
/**
 * @brief Inserts an element at an existing position in the array list.
 *
 * Elements from idx onward are shifted right before element is copied into
 * the newly opened slot. This implementation requires idx to be less than
 * the current list size, since the index of the last element is equal to
 * (size - 1).
 *
 * @param list Pointer to the array list to modify.
 * @param idx Index at which to insert the element.
 * @param element Pointer to the element to copy into the list.
 * @return AL_OK on success, AL_INVALID_ARGUMENT for invalid arguments, or
 *         an error returned by _shift_right().
 */
ArrayListStatus arraylist_insert(ArrayList* list, size_t idx, void* element) {

    if (!_is_list_valid(list) || idx >= list->size || element == NULL) {
        return AL_INVALID_ARGUMENT;
    }

    ArrayListStatus s = _shift_right(list, idx);

    if (s != AL_OK) {
        return s;
    }

    char* destination = (char*)list->data + idx * list->type_size;
    memcpy(destination, element, list->type_size);

    list->size += 1;
    return AL_OK;
}

/**
 * @brief Deletes the first element that satisfies a comparison callback.
 *
 * The callback is used to locate the element; the matching element is then
 * removed and the subsequent elements are shifted left.
 *
 * @param list Pointer to the array list to modify.
 * @param comparison_function Callback that tests an element. It receives
 *        the element pointer, argc, and args.
 * @param argc Number of arguments described by args and passed to the callback.
 * @param args Pointer to callback-specific arguments.
 * @return AL_OK if an element is found and deleted, AL_NOT_FOUND if no
 *         element matches, or an error returned by the internal functions.
 */
ArrayListStatus arraylist_delete(
    ArrayList* list,
    bool (*comparison_function)(void* element, size_t argc, void* args),
    size_t argc,
    void*  args
) {

    size_t item;

    ArrayListStatus s =
        _get_index(list, comparison_function, argc, args, &item);

    if (s != AL_OK) {
        return s;
    }

    return _delete(list, item);
}

/**
 * @brief Deletes the element at the specified index.
 *
 * @param list Pointer to the array list to modify.
 * @param idx Index of the element to delete.
 * @return AL_OK on success, or an error returned by _delete().
 */
ArrayListStatus arraylist_delete_by_idx(ArrayList* list, size_t idx) {
    return _delete(list, idx);
}
