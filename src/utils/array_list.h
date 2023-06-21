#pragma once

#define ARRAY_LIST_MIN_LENGTH (4)

typedef struct array_list_head_raw {
    const void** arr_now;
    int          max_length_now;
    int          length_now;
} ArrayListHead;

void        array_list_init  (ArrayListHead*);
void        array_list_append(ArrayListHead*, const void*);
const void* array_list_get   (ArrayListHead*, int index);
void        array_list_destr (ArrayListHead*);

