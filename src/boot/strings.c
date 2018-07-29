/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "boot/strings.h"

char *strcpy(char *s1, const char *s2)
{
    char *s = s1;
    while ((*s++ = *s2++) != 0)
	;
    return (s1);
}

char *strcpyc(char *s1, const char *s2, unsigned count)
{
    char *s = s1;
    while ((*s++ = *s2++) != 0 && count-->0)
	;
    return (s1);
}

// A simple atoi() function - from http://www.geeksforgeeks.org/write-your-own-atoi
int atoi(char *str)
{
    int res = 0; // Initialize result
  
    // Iterate through all characters of input string and
    // update result
    for (int i = 0; str[i] != '\0'; ++i)
        res = res*10 + str[i] - '0';
  
    // return result.
    return res;
}

/* reverse:  reverse string s in place */
/* void reverse(char *s)
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }*/
 
 /*char* itoa(int n, char *s)
 {
     int i, sign;

     if ((sign = n) < 0)  // record sign 
         n = -n;          // make n positive 
     i = 0;
     do {       // generate digits in reverse order 
         s[i++] = n % 10 + '0';   // get next digit 
     } while ((n /= 10) > 0);     // delete it 
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
     return s;
 }*/

#define SWAP(T, a, b) do { T tmp = a; a = b; b = tmp; } while (0)
       
/* A utility function to reverse a string  */
void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        SWAP(int, *(str+start), *(str+end));
        start++;
        end--;
    }
}

// Implementation of itoa()
char* itoa(uint64_t num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}

size_t strlen(const char* str) 
{
          size_t ret = 0;
        while ( str[ret] != 0 )
                ret++;
        return ret;
}
