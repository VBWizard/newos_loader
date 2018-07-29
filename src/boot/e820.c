/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "boot/boot.h"
#include "boot/strings.h"
#include "boot/memcpy.h"
#include "boot/e820.h"

void getE820Memory()
{
    char temp[10];
    int recCount = getE820Memory_asm();
    uint64_t usable=0, unusable=0;

    memcpy(e820Memory, lowSmapTablePtr,sizeof(sE820SystemMemory) * recCount);
    puts("E820 memory map initialized\n");
    puts("Rec\tSt\tLen\tType\n");
    for (int cnt=0;cnt<recCount;cnt++)
    {
        puts(itoa(cnt,temp,10));
        puts("\t");
        puts(itoa(e820Memory[cnt].baseAddress,temp,16));
        puts("\t");
        puts(itoa(e820Memory[cnt].length,temp,16));
        puts("\t");
        puts(itoa(e820Memory[cnt].memType,temp,10));
        puts("\n");
        if (e820Memory[cnt].memType==1)
            usable+=e820Memory[cnt].length;
        else
            unusable+=e820Memory[cnt].length;
    }
    puts("Usable Memory: ");
    puts(itoa(usable,temp,16));
    puts("\n");
    puts("Unusable Memory: ");
    puts(itoa(unusable,temp,16));
    puts("\n");

}