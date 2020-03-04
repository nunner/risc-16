#include <stdlib.h>

#include "common.h"
#include "instructions.h"

emu_t *emu; 

void
init_emu(void)
{
	emu = malloc(sizeof(emu_t));
}
