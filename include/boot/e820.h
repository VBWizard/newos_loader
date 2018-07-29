/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   e820.h
 * Author: yogi
 *
 * Created on July 25, 2018, 5:13 PM
 */

#ifndef E820_H
#define E820_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    extern int isE820Available();
    extern int getE820Memory_asm();
    extern uint64_t *lowSmapTablePtr;
    
/* from: http://www.ctyme.com/intr/rb-1741.htm
Offset  Size    Description     (Table 00580)
00h    QWORD   base address
08h    QWORD   length in bytes
10h    DWORD   type of address range (see #00581)
 */

    typedef enum uint32_t {
        E820_AVAILABLE,
        E820_RESERVED,
        E820_ACPI_RECLAIM,
        E820_ACPI_NVS
    } eE820MemoryType;
    
    typedef struct 
    {
        uint64_t baseAddress;
        uint64_t length;
        eE820MemoryType memType;
    } __attribute__((__packed__)) sE820SystemMemory;

    sE820SystemMemory e820Memory[100];
    void getE820Memory();
#ifdef __cplusplus
}
#endif

#endif /* E820_H */

