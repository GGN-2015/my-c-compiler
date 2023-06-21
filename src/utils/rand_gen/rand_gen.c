#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#include "rand_gen.h"

void rand_gen_init() {
    srand(time(NULL));   
}

static uint32 __rand_gen_uint32() { // private
    uint32 ans = 0;
    
    int i = 0;
    for(i = 0; i < RAND_GEN_BYTE_CNT; i += 1) {
        ans <<= 8;
        ans  |= (rand() & ((1 << 8) - 1)); // get last 8 bit
    }
    return ans;
}

void rand_gen(RandGenUuid* random_uuid) {
    int i = 0;
    for(i = 0; i < RAND_GEN_DWORD_CNT; i += 1) {
        random_uuid -> rand_uint32[i] = __rand_gen_uint32();
    }
}

int rand_gen_comare(const RandGenUuid* random_uuid_a, 
                    const RandGenUuid* random_uuid_b) {
    int i = 0;
    for(i = 0; i < RAND_GEN_DWORD_CNT; i += 1) {
        uint32 a = random_uuid_a -> rand_uint32[i];
        uint32 b = random_uuid_b -> rand_uint32[i];
        
        if(a != b) {
            return a < b ? RAND_GEN_LSS : RAND_GEN_GTR;
        }
    }
    return RAND_GEN_EQU;
}

// output hex integer
void rand_gen_debug(const RandGenUuid* random_uuid) {
    int i = 0;
    for(i = 0; i < RAND_GEN_DWORD_CNT; i += 1) {
        fprintf(stderr, "%08x", random_uuid -> rand_uint32[i]);
        
        if(i != RAND_GEN_DWORD_CNT - 1) { // output xxxxxxxx-xxxxxxxx-xxxxxxxx-xxxxxxxx
            fprintf(stderr, "-");
        }
    }
}

static char __rand_gen_get_ope_name(int rand_gen_ope) {
    switch(rand_gen_ope) {
        case RAND_GEN_LSS: return '<';
        case RAND_GEN_EQU: return '=';
        case RAND_GEN_GTR: return '>';
    }
    assert(false);
}

int main() {
    rand_gen_init();                                     // init before_use
    
    RandGenUuid random_uuid_a; rand_gen(&random_uuid_a); // random gen a
    RandGenUuid random_uuid_b; rand_gen(&random_uuid_b); // random gen b
    
    int ope = rand_gen_comare(&random_uuid_a, &random_uuid_b);
    rand_gen_debug(&random_uuid_a); fprintf(stderr, " ");
    
    fprintf(stderr, "%c ", __rand_gen_get_ope_name(ope)); // output result
    rand_gen_debug(&random_uuid_b); fprintf(stderr, " ");
    
    return 0;   
}
