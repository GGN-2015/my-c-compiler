#pragma once

#include "array_list.h"
#include "hash_tbl.h"
#include "rand_gen.h"

typedef struct tree_mgr_raw {
    HashTblHead hash_tbl_head; // uuid => array_list, array_list[0]: fa
} TreeMgr;

void             tree_mgr_init        (TreeMgr*);
void             tree_mgr_add_link    (TreeMgr*, const RandGenUuid* fa, const RandGenUuid* son);
ArrayListHead*   tree_mgr_get_son_list(TreeMgr*, const RandGenUuid* fa);
int              tree_mgr_get_son_cnt (TreeMgr*, const RandGenUuid* fa);
void             tree_mgr_get_fa_uuid (TreeMgr*, const RandGenUuid* son, RandGenUuid* fa_uuid);
void             tree_mgr_destr       (TreeMgr*);

