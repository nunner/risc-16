#ifndef EMU_H
#define EMU_H

#include "common.h" 

int
handle_add(emu_t *t);

int
handle_addi(emu_t *t);

int
handle_nand(emu_t *t);

int
handle_lui(emu_t *t);

int
handle_sw(emu_t *t);

int
handle_lw(emu_t *t);

int
handle_bne(emu_t *t);

int
handle_jalr(emu_t *t);

#endif
