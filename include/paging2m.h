/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   paging2m.h
 * Author: yogi
 *
 * Created on July 25, 2018, 3:37 PM
 */

#ifndef PAGING2M_H
#define PAGING2M_H

#ifdef __cplusplus
extern "C" {
#endif

#include "paging4k.h"
    
    typedef pml4e4k pml4e2m;
    
    typedef struct
    {
	uint64_t noExe : 1;		//No Execute - 63
	uint64_t swsi: 11;		//Software working set index - 52-62
	uint64_t baseAddress: 31;	//Base address of page - 21-51
        uint64_t reserved: 8;           //Reserved must be zero - 13-20
        uint64_t pat: 1;                //PAT
	uint64_t avl:3;                 //available to software - 11 - 9
	uint64_t global:1;		//Translation applies to all processes - changing CR3 doesn't affect when set if CR4.PAGEGLOBALENABLE is set.  - 8
	uint64_t mbo1:1;                //Reserved - must be 1 - 7
	uint64_t dirty:1;		//Page has been written (set by processor, cleared by software) - 6
	uint64_t accessed:1;            //Page has been read or written (set by processor, cleared by software) - 5
	uint64_t cachedisable:1;	//Disable caching for page -4
	uint64_t wt:1;		//Indicates whether the page-translation table or physical page to which this entry points has a writeback or writethrough caching policy. - 3
	uint64_t supervisor:1;	//Indicates whether user-mode code can access the page or whether the page is limited to kernel-mode access. - 2
	uint64_t writeable:1;	//Write allowed - 1
	uint64_t present:1;		//Indicates whether the translation maps to a page in physical memory. - 0
    } __attribute__((__packed__)) pde2m;

    typedef struct
    {
	uint64_t noExe : 1;		//No Execute - 63
	uint64_t swsi: 11;		//Software working set index - 52-62
	uint64_t baseAddress: 40;	//Base address of page - 12-51
	uint64_t avl:3;                 //available to software - 11 - 9
	uint64_t ign1:1;		//N/A - 8
	uint64_t reserved:1;            //N/A - 7
	uint64_t ign2:1;		//N/A - 6
	uint64_t accessed:1;            //Page has been read or written (set by processor, cleared by software) - 5
	uint64_t cachedisable:1;	//Disable caching for page -4
	uint64_t wt:1;		//Indicates whether the page-translation table or physical page to which this entry points has a writeback or writethrough caching policy. - 3
	uint64_t supervisor:1;	//Indicates whether user-mode code can access the page or whether the page is limited to kernel-mode access. - 2
	uint64_t writeable:1;	//Write allowed - 1
	uint64_t present:1;		//Indicates whether the translation maps to a page in physical memory. - 0
    } __attribute__((__packed__)) pdpe2m;

#ifdef __cplusplus
}
#endif

#endif /* PAGING2M_H */

