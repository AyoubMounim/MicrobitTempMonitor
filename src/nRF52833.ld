
MEMORY {
    ROM (rx) : ORIGIN = 0x00000000, LENGTH = 512K
    CODERAM (rwx) : ORIGIN = 0x00800000+124K, LENGTH = 4K
    RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 124K
}

OUTPUT_FORMAT ("elf32-littlearm");

ENTRY ("_reset");

SECTIONS {
    .text ALIGN(16) : SUBALIGN(16) {
        KEEP(*(.vectors))
        *(.text*);
        *(.rodata*);
        . = ALIGN(4);
        _text_end = .;

        PROVIDE(nmi_handler = default_handler);
        PROVIDE(hardfault_handler = default_handler);
        PROVIDE(memmgt_handler = default_handler);
        PROVIDE(busfault_handler = default_handler);
        PROVIDE(usagefault_handler = default_handler);
        PROVIDE(svc_handler = default_handler);
        PROVIDE(debugmon_handler = default_handler);
        PROVIDE(pendsv_handler = default_handler);
        PROVIDE(systick_handler = default_handler);
    } > ROM

    .xram : AT (LOADADDR(.text) + SIZEOF(.text)) {
        _xram_start = .;
        *(.xram*);
        . = ALIGN(4);
        _xram_end = .;
    } > CODERAM

    .data : AT (LOADADDR(.xram) + SIZEOF(.xram)) {
        _data_start = .;
        *(.data*);
        . = ALIGN(4);
        _data_end = .;
    } > RAM

    .bss : {
        _bss_start = .;
        *(.bss*);
        *(COMMON);
        . = ALIGN(4);
        _bss_end = .;
        _end = .;
    } > RAM

    _stack = ORIGIN(RAM) + LENGTH(RAM);
    _stack_limit = _stack - 2048;
    ASSERT(_stack_limit >= _end, "RAM and stack are overlapping")
}
