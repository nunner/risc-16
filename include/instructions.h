#ifndef HANDLERS_H
#define HANDLERS_H

#include "common.h"

static instruction_t map[] = {
	{"ADD", 	RRR,	0},
	{"ADDI", 	RRI, 	0},
	{"NAND", 	RRR, 	0},
	{"LUI", 	RI,		0},
	{"SW", 		RRI,	0},
	{"LW", 		RRI,	0},
	{"BNE", 	RRI,	0},
	{"JALR", 	RRI,	0}
};



#endif
