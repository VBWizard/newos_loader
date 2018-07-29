/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   io.h
 * Author: yogi
 *
 * Created on July 28, 2018, 1:36 PM
 */

#ifndef IO_H
#define IO_H

#ifdef __cplusplus
extern "C" {
#endif

#define PIC1_CMD                    0x20
#define PIC1_DATA                   0x21
#define PIC2_CMD                    0xA0
#define PIC2_DATA                   0xA1
#define PIC_READ_IRR                0x0a    /* OCW3 irq ready next CMD read */
#define PIC_READ_ISR                0x0b    /* OCW3 irq service next CMD read */

void IRQ_set_mask(unsigned char IRQline);
void IRQ_clear_mask(unsigned char IRQline);
static __inline void outb(unsigned short __port, unsigned char __val);
static __inline unsigned char inb(unsigned short __port);


static __inline void outb(unsigned short __port, unsigned char __val)
{
   while (inb((unsigned short)(__port + 5)) & 0x20 == 0);
   __asm__ volatile ("outb %1, %0" : : "a" (__val), "dN" (__port));
}

static __inline void outw(unsigned short __port, unsigned short __val)
{
	__asm__ volatile ("outw %1, %0" : : "a" (__val), "dN" (__port));
}

static __inline void outl(unsigned short __port, unsigned int __val)
{
	__asm__ volatile ("outd %1, %0" : : "a" (__val), "dN" (__port));
}

static __inline unsigned char inb(unsigned short __port)
{
	unsigned char __val;
	__asm__ volatile ("inb %0, %1" : "=a" (__val) : "dN" (__port));
	return __val;
}

static __inline unsigned short inw(unsigned short __port)
{
	unsigned short __val;
	__asm__ volatile ("inw %0, %1" : "=a" (__val) : "dN" (__port));
	return __val;
}

static __inline unsigned int inl(unsigned short __port)
{
	unsigned int __val;
	__asm__ volatile ("ind %0, %1" : "=a" (__val) : "dN" (__port));
	return __val;
}

static __inline void outsb(unsigned short __port, const void *__buf, unsigned long __n)
{
	__asm__ volatile ("cld; rep; outsb"
		      : "+S" (__buf), "+c" (__n)
		      : "d" (__port));
}

static __inline void outsw(unsigned short __port, const void *__buf, unsigned long __n)
{
	__asm__ volatile ("cld; rep; outsw"
		      : "+S" (__buf), "+c" (__n)
		      : "d" (__port));
}

static __inline void outsl(unsigned short __port, const void *__buf, unsigned long __n)
{
	__asm__ volatile ("cld; rep; outsd"
		      : "+S" (__buf), "+c"(__n)
		      : "d" (__port));
}

static __inline void insb(unsigned short __port, void *__buf, unsigned long __n)
{
	__asm__ volatile ("cld; rep; insb"
		      : "+D" (__buf), "+c" (__n)
		      : "d" (__port));
}

static __inline void insw(unsigned short __port, void *__buf, unsigned long __n)
{
	__asm__ volatile ("cld; rep; insw"
		      : "+D" (__buf), "+c" (__n)
		      : "d" (__port));
}

static __inline void insl(unsigned short __port, void *__buf, unsigned long __n)
{
	__asm__ volatile ("cld; rep; insd"
		      : "+D" (__buf), "+c" (__n)
		      : "d" (__port));
}

#ifdef __cplusplus
}
#endif

#endif /* IO_H */

