/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   paging4k.h
 * Author: yogi
 *
 * Created on July 25, 2018, 3:36 PM
 */

#ifndef PAGING4K_H
#define PAGING4K_H

#ifdef __cplusplus
extern "C" {
#endif

    #include <stdint.h>

    typedef struct
    {
	uint64_t noExe : 1;		//No Execute - 63
	uint64_t swsi: 11;		//Software working set index - 52-62
	uint64_t baseAddress: 40;	//Base address of page - 12-51
	uint64_t avl:3;                 //available to software - 11 - 9
	uint64_t mbz:1;                 //N/A - 8
	uint64_t mbz2:1;		//N/A - 8
	uint64_t ign:1;                 //N/A - 6
	uint64_t accessed:1;            //Page has been read or written (set by processor, cleared by software) - 5
	uint64_t cachedisable:1;	//Disable caching for page -4
	uint64_t wt:1;                  //Indicates whether the page-translation table or physical page to which this entry points has a writeback or writethrough caching policy. - 3
	uint64_t supervisor:1;          //Indicates whether user-mode code can access the page or whether the page is limited to kernel-mode access. - 2
	uint64_t writeable:1;           //Write allowed - 1
	uint64_t present:1;		//Indicates whether the translation maps to a page in physical memory. - 0
    } __attribute__((__packed__)) pml4e4k;

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
	uint64_t wt:1;                  //Indicates whether the page-translation table or physical page to which this entry points has a writeback or writethrough caching policy. - 3
	uint64_t supervisor:1;          //Indicates whether user-mode code can access the page or whether the page is limited to kernel-mode access. - 2
	uint64_t writeable:1;           //Write allowed - 1
	uint64_t present:1;		//Indicates whether the translation maps to a page in physical memory. - 0
    } __attribute__((__packed__)) pde4k;

    typedef pde4k pdpe4k;

    typedef struct
    {
	uint64_t noExe : 1;		//No Execute - 63
	uint64_t swsi: 11;		//Software working set index - 52-62
	uint64_t baseAddress: 40;	//Base address of page - 12-51
	uint64_t avl:3;                 //available to software - 11 - 9
	uint64_t global:1;		//Translation applies to all processes - changing CR3 doesn't affect when set if CR4.PAGEGLOBALENABLE is set.  - 8
	uint64_t large:1;		//Large page (not used in PTE entries, only in PDPE and PDE entries) - 7
	uint64_t dirty:1;		//Page has been written (set by processor, cleared by software) - 6
	uint64_t accessed:1;            //Page has been read or written (set by processor, cleared by software) - 5
	uint64_t cachedisable:1;	//Disable caching for page -4
	uint64_t wt:1;                  //Indicates whether the page-translation table or physical page to which this entry points has a writeback or writethrough caching policy. - 3
	uint64_t supervisor:1;          //Indicates whether user-mode code can access the page or whether the page is limited to kernel-mode access. - 2
	uint64_t writeable:1;           //Write allowed - 1
	uint64_t present:1;		//Indicates whether the translation maps to a page in physical memory. - 0
    } __attribute__((__packed__)) pte64_4kl;	//64-bit long mote pte for 4k paging

#ifdef __cplusplus
}
#endif

#endif /* PAGING4K_H */

