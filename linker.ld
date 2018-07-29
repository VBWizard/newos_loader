/* The bootloader will look at this image and start execution at the symbol
   designated as the entry point. */
ENTRY(_start)

/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS
{
        /* Begin putting sections at 1 MiB, a conventional place for kernels to be
           loaded at by the bootloader. */
        . = 0x1000;

        /* First put the multiboot header, as it is required to be put very early
           early in the image or the bootloader won't recognize the file format.
           Next we'll put the .text section. */
        .text BLOCK(1K) : ALIGN(1K)
        {
		*(.asmMP)
                *(.multiboot)
		*(.asm)
                *(.text)
        }

        /* Read-write data (initialized) */
        .data BLOCK(1K) : ALIGN(1K)
        {
                *(.data)
        }

        /* Read-only data. */
        .rodata BLOCK(4K) : ALIGN(4K)
        {
                *(.rodata)
        }

/*	. = 0x100000;*/

        /* Read-write data (uninitialized) and stack */
        .bss BLOCK(4K) : ALIGN(4K)
        {
                *(COMMON)
                *(.bss)
                *(.bootstrap_stack)
        }

/*INCLUDE ./kernelData.ld*/
}

