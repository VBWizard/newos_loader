/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdbool.h>
#include "boot/video.h"
#include "boot/strings.h"
#include "boot/memcpy.h"
#include "io.h"

#define TEXTMODE_MEMORY_START 0xB8000

#define VGA_WIDTH SYS_VGA_WIDTH
#define VGA_HEIGHT SYS_VGA_HEIGHT

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
uint8_t savedPosX[10];
uint8_t savedPosY[10];
int8_t savedPosPointer=0;
uint8_t kTerminalHeight;

char ansiValue1[5];
char ansiValue2[5];
int ansiValue1Index = 0;
int ansiValue2Index = 0;

typedef enum eansisteps
{
    STEP_NONE,
    STEP_INITIALIZED,
    STEP_VALUE1,
    STEP_VALUE2,
    STEP_COMMAND
} eAnsiSteps;

eAnsiSteps ansiStep = STEP_NONE;

void update_cursor()
 {
    unsigned short position=(terminal_row*VGA_WIDTH) + terminal_column;
 
    // cursor LOW port to vga INDEX register
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(position&0xFF));
    // cursor HIGH port to vga INDEX register
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char )((position>>8)&0xFF));
    //Move the cursor in the bios data area
 }

uint8_t make_color(enum vga_color fg, enum vga_color bg) {
        return fg | bg << 4;
}

uint16_t make_vgaentry(char c, uint8_t color) {
        uint16_t c16 = c;
        uint16_t color16 = color;
        return c16 | color16 << 8;
}


void terminal_setcolor(uint8_t color) {
        terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
        terminal_buffer[index] = make_vgaentry(c, color);
}

void cursorSavePosition()
{
    if (savedPosPointer < 10)
    {
        savedPosX[++savedPosPointer] = terminal_column;
        savedPosY[savedPosPointer] = terminal_row;
    }
}

void cursorRestorePosition()
{
    if (savedPosPointer > 0)
    {
        terminal_column = savedPosX[savedPosPointer];
        terminal_row = savedPosY[savedPosPointer--];
        update_cursor();
    }
}

void terminal_clear()
{
    //terminal_color = make_color(COLOR_LIGHT_GREEN, COLOR_BLACK);
        for (size_t y = 0; y < kTerminalHeight; y++) {
                for (size_t x = 0; x < VGA_WIDTH; x++) {
                        const size_t index = y * VGA_WIDTH + x;
                        terminal_buffer[index] = make_vgaentry(' ', terminal_color);
                }
        }
    terminal_column=0;
    terminal_row=0;
    update_cursor();
}

void terminal_clear_line(unsigned lineNo)
{
    if (lineNo>SYS_VGA_HEIGHT-1)
        return;
    for (unsigned cnt=0;cnt<VGA_WIDTH;cnt++)
    {
        const size_t index = lineNo * VGA_WIDTH + cnt;
        terminal_buffer[index] = make_vgaentry(' ', terminal_color);
    }
}

void terminal_copyline(unsigned dstLine, unsigned srcLine)
{
    unsigned rowBytes = VGA_WIDTH*2;
    uintptr_t dest=(uintptr_t)TEXTMODE_MEMORY_START+(dstLine*rowBytes);
    uintptr_t src=(uintptr_t)TEXTMODE_MEMORY_START+(srcLine*rowBytes);
    
    memcpy((void*)dest,(void*)src,rowBytes);
}

void char2short(unsigned char* pchar, unsigned short* pshort)
{
  *pshort = (pchar[0] << 8) | pchar[1];
}

void resetANSI()
{
    ansiStep = STEP_NONE;
    strcpy(ansiValue1,"\0\0\0\0");
    strcpy(ansiValue2,"\0\0\0\0");
    ansiValue1Index = 0;
    ansiValue2Index = 0;
}

///Processes an ANSI escape sequence character
///Returns true if the character is consumed, false if it is not
///NOTE: This only works for "Cursor Position" (i.e. CSIn;mH)
bool processANSI(char c)
{
    switch (ansiStep)
    {
        //STEP_INITIALIZED: \033 has been sent but not [ so look for it
        case (STEP_INITIALIZED):
            if (c != '[')
            {
                resetANSI();
                return false;
            }
            ansiStep = STEP_VALUE1;
            return true;
            break;
        //STEP_VALUE1: \033[ has been sent so look for the first value
        case (STEP_VALUE1):
            //If the charater is a ; then following characters will be parameter 2, otherwise reset
            if (ISDIGIT(c))
            {
                ansiValue1[ansiValue1Index++]=c;
                return true;
            }
            if (c == ';')
            {
                ansiStep = STEP_VALUE2;
                return true;
            }
            else
            {
                ansiStep = STEP_COMMAND;
                return processANSI(c);
            }
            break;
        //STEP_VALUE2: first parameter and separating ; have been sent so now accept the 2nd parameter
        //bail if it is not numeric
        case STEP_VALUE2:
            if (ISDIGIT(c))
            {
                ansiValue2[ansiValue2Index++]=c;
                return true;
            }
            else
            {
                ansiStep = STEP_COMMAND;
                return processANSI(c);
            }
            break;
        case (STEP_COMMAND):
            switch (c)
            {
                case ('A'):
                        cursorMoveToY(terminal_row-atoi(ansiValue1));
                    break;
                case ('B'):
                        cursorMoveToY(terminal_row+atoi(ansiValue1));
                    break;
                case ('C'):
                    cursorMoveToX(terminal_column+atoi(ansiValue1));
                    break;
                case ('D'):
                    cursorMoveToX(terminal_column-atoi(ansiValue1));
                    break;
                case ('H'):
                    cursorMoveTo(atoi(ansiValue1), atoi(ansiValue2));
                    break;
                case ('K'):
                    terminal_clear_line(terminal_row);
                    cursorMoveTo(0,terminal_row);
                    break;
                default:
                    resetANSI();
                    return false;
                    break;
            }
            resetANSI();
            return true;
            break;
    }
    
    
}

void terminal_putchar(char c) {
    if (c=='\033')
    {
        ansiStep = STEP_INITIALIZED;
        return;
    }
    else if (ansiStep != STEP_NONE)
    {
        if (processANSI(c));
        return;
    }
    if (c=='\n')
    {
            terminal_column = 0;
            terminal_row += 1;
    }
    else if (c=='\b')
    {
        if (terminal_column > 1)
            terminal_column--;
        else
        {
            terminal_row--;
            terminal_column=VGA_WIDTH;
        }
        terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
        
    }
    else if (c=='\t')
    {
        uint32_t goTo= terminal_column + (SCREEN_SPACES_PER_TAB - (terminal_column % SCREEN_SPACES_PER_TAB));
        if (goTo==terminal_column)
            goTo=SCREEN_SPACES_PER_TAB;
        
        while (terminal_column < goTo)
            terminal_putchar(' ');;
    
    //6 - cnt=0 to (5-1) 4
    //8 - cnt= to (5-3) 2
    }
    //We're going to ignore carriage return since most systems don't use it.  Unfortunately the FAT library we are using does
    else if (c=='\r')
        return;
    else
    {
            terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
            if (++terminal_column == VGA_WIDTH) {
                    terminal_column = 0;
                    terminal_row++;
            }
    }

    if (terminal_row == kTerminalHeight)
    {
        for (unsigned row=0;row<kTerminalHeight;row++)
            terminal_copyline(row, row+1);
        //memcpy((void *)TEXTMODE_MEMORY_START, (void *)TEXTMODE_MEMORY_START+160, 160*25);
        terminal_row--;
    }
    update_cursor();
}

void cursorUpdateBiosCursor()
{
    uint8_t* bda=(uint8_t*)0x450;
    *bda=(uint8_t)(terminal_column & 0xFF);
    bda++;
    *bda=(uint8_t)((terminal_row+3) & 0xFF);
}

void cursorMoveTo(uint8_t x, uint8_t y)
{
    if (x >= 0 && x < VGA_WIDTH && y >= 0 && y < VGA_HEIGHT)
    {
        terminal_row = y;
        terminal_column = x;
        update_cursor();
    }
}

void cursorMoveToX(uint8_t x)
{
    if (x >= 0 && x < VGA_WIDTH)
    {
        terminal_column = x;
        update_cursor();
    }
}

void cursorMoveToY(uint8_t y)
{
    if (y >= 0 && y < VGA_HEIGHT)
    {
        terminal_row = y;
        update_cursor();
    }
}

uint8_t cursorGetPosX()
{
    return terminal_column;
}
int cursorGetMaxX()
{
    return VGA_WIDTH;
}

int cursorGetMaxY()
{
    return kTerminalHeight;
}

void displayGetMaxXY(int* maxX, int* maxY)
{
    *maxX=VGA_WIDTH;
    *maxY=kTerminalHeight;
    return;
}

uint8_t cursorGetPosY()
{
    return terminal_row;
}

void kTermPrint(const char* data) {
        size_t datalen = strlen(data);
        for (size_t i = 0; i < datalen; i++)
                terminal_putchar(data[i]);
}


void kTermInit() {
    kTerminalHeight=SYS_VGA_HEIGHT;
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = make_color(COLOR_LIGHT_BROWN, COLOR_BLACK);
    terminal_buffer = (uint16_t*) TEXTMODE_MEMORY_START;
    //terminal_clear();
}

void puts(char* in)
{
    while (*in>'\0')
    {
        terminal_putchar(*in++);
    }
}

void putc(char c)
{
    terminal_putchar(c);
}