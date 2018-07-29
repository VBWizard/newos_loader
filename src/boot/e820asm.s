.intel_syntax noprefix
.section .asm
.extern rmGdtp;
.extern e820Memory;

.globl isE820Available
.type isE820Available, @function
isE820Available:
.code32
mov eax,0x10
mov ds,eax
mov saveESP, esp
mov sp, 0xfffc
call leaveProtMode
.code16
mov ax, 0x8000
mov ss, ax
pusha
mov eax,0x0000E820
mov edx, 0x534D4150
mov ebx, 0
mov ecx, 100
lea di, e820data
int 0x15
mov savedValue, eax
popa
call reenterProtMode
ret

.globl getE820Memory_asm
.type getE820Memory_asm, @function
getE820Memory_asm:
.code32
mov eax,0x10
mov ds,eax
mov saveESP, esp
mov sp, 0xfff7
call leaveProtMode
pusha
.code16
lea eax, dword ptr lowSmapTbl
.code32
mov lowSmapTablePtr,eax
mov ax, 0
mov es, ax
mov ebx, 0
.code16
lea edi, word ptr [lowSmapTbl]
.code32:
getE820Memory_asm_getNext:
mov eax, 0xe820
mov edx, 0x534D4150
mov ecx, 0x24
int 0x15
add edi,20 #ecx - A maximum of 20 bytes will be transferred at one time, even if ECX is higher
#If eax doesn't contain the value passed in EDX, the results are not valid so exit
cmp eax, 0x534D4150
jne getE820Memory_asm_exit
#ecx holds the number of bytes returned, so if it isn't 20 then we're done!
cmp ecx,20
jl getE820Memory_asm_exit
#increment the E820 record count
push eax
mov eax,recCnt
inc eax
mov recCnt, eax
pop eax
#if ebx=0 then we're all done
cmp ebx,0
je  getE820Memory_asm_exit

#loop to get another record, note that ebx and edi values remain
jmp getE820Memory_asm_getNext
getE820Memory_asm_exit:
mov eax,recCnt
mov savedValue, eax
popa
mov eax, savedValue
.code32
call reenterProtMode
ret


.globl leaveProtMode
.type leaveProtMode, @function
leaveProtMode:
.code32
lgdt [rmGdtp]
jmp 0x8:Into16BitProt
Into16BitProt:
.code16
mov ax,0x10
mov ds, ax
mov gs, ax
mov fs, ax
mov es, ax
.code32
mov eax, cr0
and al, 0xFe
mov cr0, eax
.code32
jmp 0:LeaveProtModeJmp
LeaveProtModeJmp:
.code16
mov ax, 0
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
sidt [saved_idt]
lidt [idt_real]
sgdt [saved_gdt16_lo]
.code16
mov ax,0
mov ss,ax
mov ds, ax
.code32
ret

.globl reenterProtMode
.type reenterProtMode, @function
reenterProtMode:
.code32
mov savedValue, eax
.code16
lgdt [saved_gdt16_lo]
lidt [saved_idt]
.code32
mov eax, cr0
or  al, 0x1
.code16
or  eax,0x10000   #clr 05/12/2016 - added wp bit
.code32
mov cr0, eax
.code16
ljmp 0x18:reenterProtModeJmp
reenterProtModeJmp:
.code32
mov ax,0x10
mov ds,ax
mov es,ax
mov gs,ax
lgdt [kernelGDT]
ljmp 0x8:reenterProtMode32Jmp
reenterProtMode32Jmp:
mov ax,0x10
mov ds,ax
mov ss,ax
mov es,ax
mov fs,ax
mov gs,ax
.code32
mov eax,savedValue
mov esp,saveESP
ret

/*Define variables*/
    saved_gdt16_lo: .word 0x0
    saved_gdt16_hi: .word 0
    saved_gdt16_hi2: .word 0
    saveESP: .word 0,0
    savedValue: .word 0, 0, 0, 0
    recCnt: .word 0,0
idt_real:
	.word 0x3ff, 0, 0
    retVal: .word 0
saved_idt:
        .word 0
        .word 0
        .word 0
e820data:
        .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    .globl lowSmapTablePtr
    .type lowSmapTablePtr, @common
    lowSmapTablePtr: .word 0,0, 0, 0
    lowSmapTbl: .zero 480
    .globl idtPtrToLoad
    .type idtPtrToLoad, @common
    idtPtrToLoad: .word 0,0,0,0
