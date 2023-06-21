#include <assert.h>
#include <stdio.h>

#include "hash_tbl.h"

static int __hash_tbl_hasher(const RandGenUuid* uuid) {
    return uuid -> rand_uint32[0] % HASH_TBL_SIZE;
}

void hash_tbl_init(HashTblHead* hash_tbl_head) {
    int i = 0;
    for(i = 0; i < HASH_TBL_SIZE; i += 1) {
        hash_tbl_head -> heads[i] = NULL;
    }
}

HashTblNode* hash_tbl_exist(HashTblHead* hash_tbl_head, const RandGenUuid* uuid) {
    int hash_val = __hash_tbl_hasher(uuid);
    
    HashTblNode* p = hash_tbl_head -> heads[hash_val];
    while(p != NULL) {
        if(rand_gen_comare(&(p->rand_gen_uuid), uuid) == RAND_GEN_EQU) {
            return p; // exist
        }
        p = p -> next_node;
    }
    return NULL; // not exist
}

void hash_tbl_set(HashTblHead* hash_tbl_head, 
                  const RandGenUuid* uuid, const void* new_data) {
                       
    HashTblNode* node_now = hash_tbl_exist(hash_tbl_head, uuid);
    if(node_now != NULL) {
        node_now -> data = new_data;
    }else {
        int hash_val = __hash_tbl_hasher(uuid);
        
        HashTblNode* p = (HashTblNode*)malloc(sizeof(HashTblNode));
        p -> rand_gen_uuid = *uuid;
        p -> data          = new_data;
        p -> next_node     = hash_tbl_head -> heads[hash_val];
        
        hash_tbl_head -> heads[hash_val] = p; // link new node
    }
}

const void* hash_tbl_get(HashTblHead* hash_tbl_head, const RandGenUuid* uuid) {
    HashTblNode* node_now = hash_tbl_exist(hash_tbl_head, uuid);
    
    if(node_now == NULL) return NULL; // we use NULL ptr to show a uuid is not exist
    return node_now -> data;          // maybe data is NULL ptr (virtual delete)
}

void hash_tbl_destr(HashTblHead* hash_tbl_head) {
    int i = 0;
    for(i = 0; i < HASH_TBL_SIZE; i += 1) {
        while(hash_tbl_head -> heads[i] != NULL) {
            HashTblNode* ptr = hash_tbl_head -> heads[i];
            HashTblNode* nxt = ptr -> next_node;
            
            hash_tbl_head -> heads[i] = nxt;
            free(ptr);
        }
    }
}

#ifdef TEST_HASH_TBL
HashTblHead hash_tbl_head_test;
int main() {
    hash_tbl_init(&hash_tbl_head_test);
    
    RandGenUuid rand_gen_uuid_list[11]; // first ten: in set, last one: not in set
    int i = 0;
    for(i = 0; i < 11; i += 1) {
        rand_gen(&rand_gen_uuid_list[i]);
        
        if(i < 10) {
            hash_tbl_set(&hash_tbl_head_test, &rand_gen_uuid_list[i], (const void*)(i + 1));
        }
    }
    
    // check first ten in set
    int ans = 0;
    for(i = 0; i < 10; i += 1) {
        ans += (int)hash_tbl_get(&hash_tbl_head_test, &rand_gen_uuid_list[i]);
    }
    assert(ans == 55);
    assert(hash_tbl_get(&hash_tbl_head_test, &rand_gen_uuid_list[10]) == NULL);
    fprintf(stderr, "test passed\n");
    
    hash_tbl_destr(&hash_tbl_head_test); // destroy
    return 0;
}
#endif
