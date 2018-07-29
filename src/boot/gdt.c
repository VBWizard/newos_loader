/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "gdt.h"

void gdtEntryI(int entryNo, int base, int limit, char access, char flags,bool inUse,bool setSFlag)
{
    bootGDT[entryNo].base_low        = base & 0xFFFF;
    bootGDT[entryNo].base_middle     = (base >> 16) & 0xFF;
    bootGDT[entryNo].base_high       = (base >> 24) & 0xFF;
    bootGDT[entryNo].limit_low       = limit & 0xFFFF;
    bootGDT[entryNo].flags_and_limit = flags | (((limit >> 16) & 0xF));
    bootGDT[entryNo].access          = access;
    if (setSFlag)
        bootGDT[entryNo].access |= 0x10;
    /*if (inUse)
        bitsReset(kGDTSlotAvailableInd,entryNo);
    else
        bitsSet(kGDTSlotAvailableInd,entryNo);*/
}

//Create entries in the real mode GDT table
void gdtEntryRM(int entryNo, int base, int limit, char access, char flags)
{
    rmGDT[entryNo].base_low        = base & 0xFFFF;
    rmGDT[entryNo].base_middle     = base >> 16 & 0xFF;
    rmGDT[entryNo].base_high       = base >> 24 & 0xFF;
    rmGDT[entryNo].limit_low       = limit & 0xFFFF;
    rmGDT[entryNo].flags_and_limit = flags | (limit >> 16 & 0xF);
    rmGDT[entryNo].access          = access | 0x10;
}

//Create/modify entries in the protected mode GDT
void gdtEntryApplication(int entryNo, int base, int limit, char access, char flags,bool inUse)
{
    gdtEntryI(entryNo,base,limit,access,flags,inUse,true);
}

void gdt_init()
{
    const int KERNEL_PAGED_BASE_ADDRESS = 0xc0000000;
    
   gdtEntryApplication(0x1, 0, 0xFFFFF, GDT_PRESENT | GDT_DPL0 | GDT_CODE | GDT_READABLE,       //ring 0 starting at 0x00, always
              GDT_GRANULAR | GDT_32BIT,true);
    gdtEntryApplication(0x2, 0, 0xFFFFF, GDT_PRESENT | GDT_DPL0 | GDT_DATA | GDT_WRITABLE,       //ring 0 starting at 0x0, updated to 0xC0000000 when paging initialized
              GDT_GRANULAR | GDT_32BIT,true);
    gdtEntryApplication(0x3, 0, 0xFFFFF, GDT_PRESENT | GDT_DPL0 | GDT_DATA | GDT_WRITABLE,    //18 - ring 0 Kernel starting at 0x0 ***Need to change this to KERNEL_PAGED_BASE_ADDRESS base
              GDT_GRANULAR | GDT_32BIT,true);
    gdtEntryApplication(0x4, KERNEL_PAGED_BASE_ADDRESS , 0xFFFFF, GDT_PRESENT | GDT_DPL0 | GDT_CODE | GDT_READABLE,  //20 - ring 0 Kernel starting at 0xC0000000
              GDT_GRANULAR | GDT_32BIT,true);
    gdtEntryApplication(0x5, 0x0 , 0xFFFFF, GDT_PRESENT | GDT_DPL0 | GDT_DATA | GDT_WRITABLE /*| GDT_GROW_DOWN*/,       //28 - ring 0 starting at 0x0
              GDT_GRANULAR | GDT_32BIT,true);
    gdtEntryApplication(0x6, 0, 0xFFFFFFFF, GDT_PRESENT | GDT_DPL3 | GDT_DATA | GDT_WRITABLE,    //30 (33) - ring 3 segment starting at 0x0
              GDT_GRANULAR | GDT_32BIT,true);
    gdtEntryApplication(0x7, 0 , 0xFFFFF, GDT_PRESENT | GDT_DPL3 | GDT_CODE | GDT_READABLE ,       //38 (3b) - ring 3 starting at 0x0
              GDT_GRANULAR | GDT_32BIT,true);
    gdtEntryApplication(0x8, 0x0 , 0xFFFFF, GDT_PRESENT | GDT_DPL3 | GDT_DATA | GDT_WRITABLE /*| GDT_GROW_DOWN*/,       //40 (43) - ring 3 starting at 0x0
          GDT_GRANULAR | GDT_32BIT,true);
    gdtEntryApplication(0x10, 0x0 , 0xFFFFF, GDT_PRESENT | GDT_DPL0 | GDT_CODE | GDT_READABLE,  //20 - ring 0 starting at 0x0
              GDT_GRANULAR | GDT_32BIT,true);

    gdtEntryApplication(0x11, 0x0, 0xFFFFF, GDT_PRESENT | GDT_DPL0 | GDT_CODE | GDT_READABLE, //88 ring 0 starting at 0x0 - code used by sysEnter
          GDT_GRANULAR | GDT_32BIT,true);
    gdtEntryApplication(0x12, 0x0, 0xFFFFF, GDT_PRESENT | GDT_DPL0 | GDT_DATA | GDT_WRITABLE,    //90 - ring 0 starting at 0x0 data used by sysEnter
              GDT_GRANULAR | GDT_32BIT,true);

    gdtEntryApplication(0x13, 0x0, 0xFFFFF, GDT_PRESENT | GDT_DPL3 | GDT_CODE | GDT_READABLE, //98 ring 0 starting at 0x0 - code used by sysEnter
          GDT_GRANULAR | GDT_32BIT,true);
    gdtEntryApplication(0x14, 0x0, 0xFFFFF, GDT_PRESENT | GDT_DPL3 | GDT_DATA | GDT_WRITABLE,    //A0 - ring 0 starting at 0x0 data used by sysEnter
              GDT_GRANULAR | GDT_32BIT,true);

    
    gdtEntryRM(1, 0, 0xFFFFF, GDT_PRESENT | GDT_DPL0 | GDT_CODE | GDT_READABLE,
              GDT_GRANULAR | GDT_16BIT);
    gdtEntryRM(2, 0, 0xFFFFF, GDT_PRESENT | GDT_DPL0 | GDT_DATA | GDT_WRITABLE,
              GDT_GRANULAR | GDT_16BIT);
    gdtEntryRM(3, 0, 0xFFFFF, GDT_PRESENT | GDT_DPL0 | GDT_CODE | GDT_WRITABLE,
              GDT_GRANULAR | GDT_32BIT);

    kernelGDT.limit = 0x7ff; // (sizeof(sGDT) * GDT_ENTRIES) - 1;
    kernelGDT.base = (unsigned int)&bootGDT;
    rmGdtp.limit = (unsigned short)(sizeof(sGDT) * 0x20);
    rmGdtp.base = (unsigned int)rmGDT;
    set_gdt(&kernelGDT);
}