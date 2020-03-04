#ifndef EMU_H
#define EMU_H

#include <stdint.h>

/*
 * Function definitions
 */

void
init(void);

/*
 * Type definitions
 */

typedef enum {
	RRR,
	RRI,
	RI
} instruction_type_t;

typedef struct {
	int8_t regs[8];
	instruction_type_t current_type;
} emu_t;

typedef int (*Handler)(emu_t *t);

typedef struct {
	char *name;
	instruction_type_t type;
	Handler h;
} instruction_t;

#endif
