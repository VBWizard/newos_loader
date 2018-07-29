/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "bits.h"

bool bitsSet(volatile uint32_t* array, uint32_t bit)
{
    int lRetVal=0;
    __asm__ volatile ("bts [%[array]],%[bit]\nmov eax,0\nsetc al\n" : [array] "+m" (*array), "=a" (lRetVal) : [bit] "r" (bit));
    return lRetVal;
}
bool bitsReset(volatile uint32_t* array, uint32_t bit)
{
    int lRetVal=0;
    __asm__ volatile ("btr [%[array]],%[bit]\nmov eax,0\nsetc al\n" : [array] "+m" (*array), "=a" (lRetVal) : [bit] "r" (bit));
    return lRetVal;
}
bool bitsTest(volatile uint32_t* array, uint32_t bit)
{
    int lRetVal=0;
    __asm__ volatile ("bt [%[array]],%[bit]\nmov eax,0\nsetc al\n" :[array] "+m" (*array), "=a" (lRetVal) : [bit] "r" (bit));
    return lRetVal;
}

int bitsScanF(volatile uint32_t* array)
{
    int lRetVal=0;
    bool lErr=false;
    __asm__ volatile ("bsf %[ret],[%[array]]\nsetz cl\n" : [ret] "=b" (lRetVal), [lErr] "=c" (lErr) : [array] "m" (*array));
    if (lErr==false)
        return lRetVal;
    else
        return -1;
}