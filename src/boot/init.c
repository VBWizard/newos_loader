/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: yogi
 *
 * Created on July 25, 2018, 3:26 PM
 */


/*
 * 
 */

#include "mm.h"
#include "init.h"
#include "gdt.h"
#include "io.h"
#include "boot/video.h"

void init() {
    bool mmInitComplete=0;
    
    kTermInit();

    __asm__("cli\nsgdt [eax]\n"::"a" (&kernelGDT));
    __asm__("mov esp,0xff00\n");
    outb(0xa1, 0x7f);
    outb(0x21, 0xff);
    gdt_init();
    mmInitComplete=init_mm();
    
    
    puts("Halting boot at end of Init()");
    __asm__("cli\nhlt\n");
    __asm__("cli\nhlt\n");
    __asm__("cli\nhlt\n");
    
NoExitLoop:
    goto NoExitLoop;
    return;
}

