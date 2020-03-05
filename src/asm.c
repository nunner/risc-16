#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

#include "instructions.h"
#include "macro.h"
#include "common.h"

#define MAX_LABELS 	100
#define MAX_LEN		300

FILE *stream;
FILE *output;
char buf		[MAX_LEN];

char *labels	[MAX_LABELS];
char label_addr	[MAX_LABELS];

/*
 * ============================
 * Helper functions for parsing
 * ============================
 */


int
open_file(char *path)
{
	stream = fopen(path, "r");
	return (stream == 0);
}

int
open_output()
{
	output = fopen("out.bin", "wb");
	return (output == 0);
}

void
write(FILE *stream, char *msg)
{
	fprintf(stream, "%s", msg);
}

void
write_out(int16_t val)
{
	fwrite(&val, sizeof(val), 1, output);
	printf("%04x\n", val & 0xFFFF);
}

char *
get_line() 
{
	return fgets(buf, MAX_LEN, stream);
}

void
index_labels()
{
	size_t index = 0;
	size_t addr  = 0;
	char *token;

	while(get_line() != NULL)
	{
		token = strtok(buf, " \t\n");
		if(token[strlen(token) - 1] == ':') {
			token[strlen(token) - 1] = '\0';

			labels[index] = malloc(MAX_LEN * sizeof(char));
			strncpy(labels[index], token, MAX_LEN);
			label_addr[index] = addr;

			index++;
		}
		addr++;
	}
}

int8_t
resolve_label(char *label)
{
	for(int i = 0; i < MAX_LABELS; i++) {
		if(strncmp(labels[i], label, strlen(label)-1) == 0) {
			return label_addr[i];
		}
	}
	return 0;
}
		
void
parse_file()
{
	char *token;

	int16_t opcode = 0;
	int line = 0;

	int8_t ops[3] = {0, 0, 0}; 
	char imm[MAX_LEN]; 

	bool found = false;

	while(get_line() != NULL) {
			token = strtok(buf, " \t\n");
			opcode = 0;
			found = false;

			if(token[strlen(token) - 1] == ':')
				token = strtok(NULL, " \t\n");

			for(size_t i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
				if(strcasecmp(map[i].name, token) == 0) {
					token = strtok(NULL, " \t\n");

					switch(map[i].type) {
						case RRR:
							sscanf(token, "%" SCNd8 ",%" SCNd8 ",%" SCNd8, &ops[0], &ops[1], &ops[2]);

							opcode = (i << 13);
							opcode |= (ops[0] << 10);
							opcode |= (ops[1] << 7);
							opcode |= (ops[2]);
							
							break;
						case RRI:
							sscanf(token, "%" SCNd8 ",%" SCNd8 ",%s", &ops[0], &ops[1], imm);

							opcode = (i << 13);
							opcode |= (ops[0] << 10);
							opcode |= (ops[1] << 7);
							if(strcasecmp(map[i].name, "bne") == 0)
								opcode |= ((resolve_label(imm) - line - 1) & 0xFF );
							else 
								opcode |= (resolve_label(imm) & 0xFF);

							break;
						case RI:
							break;
					}

					found = true;
				}
			}

			// Search in the macro definitions
			for(size_t i = 0; i < sizeof(macro_map) / sizeof(macro_map[0]); i++) {
				if(strcasecmp(macro_map[i].name, token) == 0) {
					if(strcasecmp(".fill", token) == 0) {
						int16_t val = 0;
						token = strtok(NULL, " \t\n");
						sscanf(token, "%" SCNd16, &val);
						write_out(val);
					} else {
						write_out(macro_map[i].val);
					}
				}
			}

			if(found)
				write_out(opcode);

			line++;
	}
}

int
main(int argc, char *argv[])
{
	if(argc != 2) {
		write(stderr, "No files given\n");
		exit(1);
	}

	if(open_file(argv[1])) {
		write(stderr, "File does not exist!\n");
		exit(1);
	}

	if(open_output()) {
		write(stderr, "Could not open output file!\n");
		exit(1);
	}

	index_labels();
	rewind(stream);
	parse_file();

	return 0;
}
