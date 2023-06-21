#pragma once

#include <stdbool.h>

#include "rand_gen.h" // use RandGenUuid

#define HASH_TBL_SIZE (1048576)

// for a hash table node, record a map from uuid to data
typedef struct hash_tbl_node_raw {
    RandGenUuid               rand_gen_uuid;
    const void*               data;
    struct hash_tbl_node_raw* next_node;
} HashTblNode;

// for a hash table, record every head of a linked list
typedef struct hash_tbl_head_raw {
    HashTblNode* heads[HASH_TBL_SIZE];
} HashTblHead;

void         hash_tbl_init (HashTblHead*);                                  // initial lize a hash table
HashTblNode* hash_tbl_exist(HashTblHead*, const RandGenUuid*);              // try to find element in hash_tbl
void         hash_tbl_set  (HashTblHead*, const RandGenUuid*, const void*); // hash_tbl[uuid] = data
const void*  hash_tbl_get  (HashTblHead*, const RandGenUuid*);              // hash_tbl[uuid]
void         hash_tbl_destr(HashTblHead*);                                  // destruct a hash_tbl

