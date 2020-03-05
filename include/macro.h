#ifndef MACRO_H
#define MACRO_H

#include <stdint.h>

typedef struct {
	char *name;
	int16_t val;
} macro_t;

static macro_t macro_map[] = {
	{"nop", 	0x0000},
	{"halt", 	0xE071},
	{".fill",	-1}
};

#endif
