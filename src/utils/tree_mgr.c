#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "tree_mgr.h"

void tree_mgr_init(TreeMgr* tree_mgr) {
    hash_tbl_init(&(tree_mgr -> hash_tbl_head));
}

// init a new array list for a certain uuid
static void __tree_mgr_init_array(HashTblHead* hash_tbl_head_now, const RandGenUuid* node_uuid) {
    ArrayListHead* p = (ArrayListHead*)malloc(sizeof(ArrayListHead*));
    array_list_init(p);
    array_list_append(p, NULL); // no father
    
    hash_tbl_set(hash_tbl_head_now, node_uuid, (const void*)p); // insert into hash map
}

void tree_mgr_add_link(TreeMgr* tree_mgr, const RandGenUuid* fa, const RandGenUuid* son) {
    HashTblHead* hash_tbl_head_now = &(tree_mgr->hash_tbl_head);
    
    HashTblNode* fa_node_now  = hash_tbl_exist(hash_tbl_head_now, fa);
    HashTblNode* son_node_now = hash_tbl_exist(hash_tbl_head_now, son);
    
    // init new array lists
    if(fa_node_now  == NULL) __tree_mgr_init_array(hash_tbl_head_now, fa);
    if(son_node_now == NULL) __tree_mgr_init_array(hash_tbl_head_now, son);
    
    fa_node_now  = hash_tbl_exist(hash_tbl_head_now, fa);
    son_node_now = hash_tbl_exist(hash_tbl_head_now, son);
    
    // set father of the son_uuid
    ArrayListHead* son_list                   = (ArrayListHead*)hash_tbl_get(hash_tbl_head_now, son);
    son_list                  -> arr_now[0]   = malloc(sizeof(RandGenUuid));
    *((RandGenUuid*)(son_list -> arr_now[0])) = *fa;
    
    // set son of the father_uuid
    ArrayListHead* fa_list                     = (ArrayListHead*)hash_tbl_get(hash_tbl_head_now, fa);
    array_list_append(fa_list, malloc(sizeof(RandGenUuid))); // append new son
    int pos                                    = ((ArrayListHead*)fa_node_now -> data) -> length_now - 1;
    *((RandGenUuid*)(fa_list -> arr_now[pos])) = *son;
}

ArrayListHead* tree_mgr_get_son_list(TreeMgr* tree_mgr, const RandGenUuid* fa) {
    HashTblHead* hash_tbl_head_now = &(tree_mgr->hash_tbl_head);
    ArrayListHead* fa_list = (ArrayListHead*)hash_tbl_get(hash_tbl_head_now, fa);
    assert(fa_list != NULL);
    
    return fa_list;
}

int tree_mgr_get_son_cnt(TreeMgr* tree_mgr, const RandGenUuid* fa) {
    HashTblHead* hash_tbl_head_now = &(tree_mgr->hash_tbl_head);
    ArrayListHead* fa_list = (ArrayListHead*)hash_tbl_get(hash_tbl_head_now, fa);
    assert(fa_list != NULL);
    
    return fa_list -> length_now - 1;
}

void tree_mgr_get_fa_uuid(TreeMgr* tree_mgr, const RandGenUuid* son, RandGenUuid* fa_uuid) {
    HashTblHead* hash_tbl_head_now = &(tree_mgr->hash_tbl_head);
    ArrayListHead* son_list = (ArrayListHead*)hash_tbl_get(hash_tbl_head_now, son);
    assert(son_list != NULL);
    
    *fa_uuid = *((RandGenUuid*)son_list -> arr_now[0]);
}

void tree_mgr_destr(TreeMgr* tree_mgr) {
    assert(false); // TODO: free all resources
}

static void __tree__mgr_dfs(TreeMgr* tree_mgr, const RandGenUuid* x_uuid) {
    ArrayListHead* sl = tree_mgr_get_son_list(tree_mgr, x_uuid);
    
    int i = 0;
    int len = tree_mgr_get_son_cnt(tree_mgr, x_uuid);
    for(i = 1; i <= len; i += 1) {
        rand_gen_debug(x_uuid); 
        fprintf(stderr, " -> ");
        rand_gen_debug((const RandGenUuid*)(sl -> arr_now[i])); 
        fprintf(stderr, "\n");
        __tree__mgr_dfs(tree_mgr, (const RandGenUuid*)(sl -> arr_now[i]));
    }
}

TreeMgr tree_mgr;
int main() {
    tree_mgr_init(&tree_mgr);
    RandGenUuid rand_gen_uuid[5];
    
    int i = 0;
    for(i = 0; i < 5; i += 1) {
        rand_gen(&rand_gen_uuid[i]); // rand generate
        
        fprintf(stderr, "%d: ", i);  // debug show
        rand_gen_debug(&rand_gen_uuid[i]);
        fprintf(stderr, "\n");
    }
    
    // add link
    tree_mgr_add_link(&tree_mgr, &rand_gen_uuid[0], &rand_gen_uuid[1]);
    tree_mgr_add_link(&tree_mgr, &rand_gen_uuid[0], &rand_gen_uuid[2]);
    tree_mgr_add_link(&tree_mgr, &rand_gen_uuid[2], &rand_gen_uuid[3]);
    tree_mgr_add_link(&tree_mgr, &rand_gen_uuid[2], &rand_gen_uuid[4]);
    
    fprintf(stderr, "\n");
    
    __tree__mgr_dfs(&tree_mgr, &rand_gen_uuid[0]);
    
    // destr
    tree_mgr_destr(&tree_mgr);
    return 0;
}
