/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mm.h
 * Author: yogi
 *
 * Created on July 25, 2018, 3:35 PM
 */

#ifndef MM_H
#define MM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "paging4k.h"
#include "paging2m.h"
#include "paging1g.h"
    
    typedef enum
    {
        PML4E,
        PDPE,
        PDE,
        PTE,
        Page
    } eMemType;

    typedef enum 
    {
        FOUR_K,
        TWO_MEG,
        ONE_GIG
    } ePageSize;

    typedef struct 
    {
        union {
            pml4e4k *pml4eEntry4k;
            pml4e2m *pml4eEntry2m;
            pml4e1g *pml4eEntry2g;
        } pml4e;
        union {
            pdpe4k *pdpeEntry4k;
            pdpe2m *pdpeEntry2m;
            pdpe1g *pdpeEntry1g;
        } pdpe;
        union {
            pde4k *pdEntry4k;
            pde2m *pdEntry2m;
        } pde;
        pte64_4kl *ptEntry;
        uint64_t *page;
        eMemType pageType;
        ePageSize pageSize;
    } s_memoryBlock;

    bool init_mm();
    
#ifdef __cplusplus
}
#endif

#endif /* MM_H */

