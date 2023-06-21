#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_list.h"

void array_list_init(ArrayListHead* array_list_head) {
    array_list_head -> arr_now        = (const void**)malloc(ARRAY_LIST_MIN_LENGTH * sizeof(const void*));
    array_list_head -> max_length_now = ARRAY_LIST_MIN_LENGTH;
    array_list_head -> length_now     = 0;
}

void array_list_append(ArrayListHead* array_list_head, const void* new_data) {
    
    if(array_list_head -> length_now >= array_list_head -> max_length_now) {
        int old_len =  array_list_head -> max_length_now;
        int new_len = (array_list_head -> max_length_now *= 2);
        
        // alloc new array and copy data
        const void** new_arr = (const void**)malloc(new_len * sizeof(const void*));
        int i = 0;
        for(i = 0; i < old_len; i += 1) {
            new_arr[i] = array_list_head -> arr_now[i]; // copy
        }
        
        // free old arr, and link new array
        const void** p             = array_list_head -> arr_now;
        array_list_head -> arr_now = new_arr;
        free(p);
    }
    
    // save new_data
    int pos                         = (array_list_head -> length_now) ++;
    array_list_head -> arr_now[pos] = new_data;
}

const void* array_list_get(ArrayListHead* array_list_head, int index) {
    assert(0 <= index && index < array_list_head -> length_now);
    
    return array_list_head -> arr_now[index];
}

void array_list_destr(ArrayListHead* array_list_head) {
    
    // free array
    free(array_list_head -> arr_now);
    array_list_head -> arr_now = NULL;
    
    // clear count
    array_list_head -> max_length_now = 0;
    array_list_head -> length_now = 0;
}

int main() {
    ArrayListHead array_list_head; array_list_init(&array_list_head);
    
    // save data
    int i = 0; 
    for(i = 0; i < 100; i += 1) {
        array_list_append(&array_list_head, (const void*)(i + 1));
    }
    
    // read data
    int ans = 0;
    for(i = 0; i < 100; i += 1) {
        ans += (int)array_list_get(&array_list_head, i);
    }
    assert(ans == 5050);
    fprintf(stderr, "test passed\n");
    
    array_list_destr(&array_list_head);
    return 0;   
}
