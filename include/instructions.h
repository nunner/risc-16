#ifndef HANDLERS_H
#define HANDLERS_H

#include "emu.h"

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

static instruction_t map[] = {
	{"ADD", 	RRR,	&handle_add},
	{"ADDI", 	RRI, 	&handle_addi},
	{"NAND", 	RRR, 	&handle_nand},
	{"LUI", 	RI,		&handle_lui},
	{"SW", 		RRI,	&handle_sw},
	{"LW", 		RRI,	&handle_lw},
	{"BNE", 	RRI,	&handle_bne},
	{"JALR", 	RRI,	&handle_jalr}
};



#endif
