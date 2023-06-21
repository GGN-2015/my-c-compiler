#pragma once

#define RAND_GEN_DWORD_CNT (4)
#define RAND_GEN_BYTE_CNT  ((RAND_GEN_DWORD_CNT) * (4))
#define RAND_GEN_BIT_CNT   ((RAND_GEN_DWORD_CNT) * (32))

typedef unsigned int uint32;

// 128 bits uuid
typedef struct rand_gen_uuid_raw {uint32 rand_uint32[RAND_GEN_DWORD_CNT];} RandGenUuid;

// call this when your program init
void rand_gen_init();

// generate a `RandomUuid`
void rand_gen(RandGenUuid* random_uuid);

// compair uuid
int rand_gen_comare(const RandGenUuid* random_uuid_a, const RandGenUuid* random_uuid_b);

// output the integer on to stderr
void rand_gen_debug(const RandGenUuid* random_uuid);

// the result of rand_gen_comare
#define RAND_GEN_LSS (-1)
#define RAND_GEN_EQU ( 0)
#define RAND_GEN_GTR ( 1)
