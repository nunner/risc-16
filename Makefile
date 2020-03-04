CFLAGS=-Wall -Werror -O3
CC=gcc

INCLUDE=include

EMU=src/emu.c
ASM=src/asm.c

TARGET_EMU=risc-16-emu
TARGET_ASM=risc-16-asm

emu:
	$(CC) -I $(INCLUDE) -o $(TARGETE_EMU) $(CFLAGS) $(LDFLAGS) $(EMU) $(LDLIBS)

asm:
	$(CC) -I $(INCLUDE) -o $(TARGET_ASM) $(CFLAGS) $(LDFLAGS) $(ASM) $(LDLIBS)

clean:
	rm -f $(TARGET_ASM) $(TARGET_EMU)
