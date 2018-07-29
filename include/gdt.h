/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gdt.h
 * Author: yogi
 *
 * Created on July 25, 2018, 5:34 PM
 */

#ifndef GDT_H
#define GDT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "bits.h"
    
typedef struct sgdt
{
    unsigned short limit_low;       //2
    unsigned short base_low;        //2
    char base_middle;               //1
    char access;                    //1
    char flags_and_limit;           //1
    char base_high;                 //1
} sGDT;

typedef struct 
{
    unsigned short limit;
    unsigned int base;
}__attribute__((packed)) gdt_ptr;

enum {
    // Access byte properties
    GDT_PRESENT    = 0x80,

    GDT_DPL0       = 0x00, // DPL = descriptor privilege level (ring level)
    GDT_DPL1       = 0x20,
    GDT_DPL2       = 0x40,
    GDT_DPL3       = 0x60,

    GDT_CODE       = 0x08,
    GDT_READABLE   = 0x00,
    GDT_CONFORMING = 0x04,

    GDT_DATA       = 0x00,
    GDT_WRITABLE   = 0x02,
    GDT_GROW_DOWN  = 0x04,

    // Flags
    GDT_GRANULAR   = 0x80,
    GDT_32BIT       = 0x40,
    GDT_16BIT       = 0x00
};
    sGDT bootGDT[40], rmGDT[8];
    gdt_ptr kernelGDT, rmGdtp;

    void gdt_init();
    int isE820Available();
    extern void set_gdt(gdt_ptr *addr);
    
#ifdef __cplusplus
}
#endif

#endif /* GDT_H */

