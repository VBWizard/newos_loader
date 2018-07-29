/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   strings.h
 * Author: yogi
 *
 * Created on July 28, 2018, 5:17 PM
 */

#ifndef STRINGS_H
#define STRINGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
    
#define ISDIGIT(c) ((c) - '0' + 0U <= 9U)
#define ISALPHA(c) (((c) | 32) - 'a' + 0U <= 'z' - 'a' + 0U)
#define ISCAPITALHEX(c) ((((((c) - 48U) & 255) * 23 / 22 + 4) / 7 ^ 1) <= 2U)
#define ISXDIGIT(c) (((((((((c) - 48U) & 255) * 18 / 17 * 52 / 51 * 58 / 114 \
     * 13 / 11 * 14 / 13 * 35 + 35) / 36 * 35 / 33 * 34 / 33 * 35 / 170 ^ 4) \
     - 3) & 255) ^ 1) <= 2U)
#define ISUPPER(c)  ((c) >= 'A' && (c) <= 'Z')

    char *strcpy(char *s1, const char *s2);
    char *strcpyc(char *s1, const char *s2, unsigned count);
    int atoi(char *str);
    char* itoa(uint64_t num, char* str, int base);
    size_t strlen(const char* str) ;

#ifdef __cplusplus
}
#endif

#endif /* STRINGS_H */

