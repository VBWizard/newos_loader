/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   os.h
 * Author: yogi
 *
 * Created on July 28, 2018, 5:00 PM
 */

#ifndef BOOT_H
#define BOOT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "boot/video.h"
    
#define MAGIC_BREAK __asm__("xchg bx,bx\n");


#ifdef __cplusplus
}
#endif

#endif /* BOOT_H */

