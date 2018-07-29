/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bits.h
 * Author: yogi
 *
 * Created on July 25, 2018, 6:17 PM
 */

#ifndef BITS_H
#define BITS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

    bool bitsSet(volatile uint32_t* array, uint32_t bit);
    bool bitsReset(volatile uint32_t* array, uint32_t bit);
    bool bitsTest(volatile uint32_t* array, uint32_t bit);
    int bitsScanF(volatile uint32_t* array);
    


#ifdef __cplusplus
}
#endif

#endif /* BITS_H */

