#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "instructions.h"
#include "common.h"

#define MAX_LABELS 	100
#define MAX_LEN		300

FILE *stream;
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

void
write(FILE *stream, char *msg)
{
	fprintf(stream, "%s", msg);
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

uint16_t
resolve_label(char *label)
{
	for(int i = 0; i < MAX_LABELS; i++) {
		if(strncmp(labels[i], label, strlen(label)) == 0) {
			return label_addr[i];
		}
	}
	return -1;
}
		
void
parse_file()
{
	char *token;

	int16_t option = 0;
	int line = 0;

	int8_t ops[3] = {0, 0, 0}; 
	char imm[MAX_LEN]; 

	while(get_line() != NULL) {
			token = strtok(buf, " \t\n");

			if(token[strlen(token) - 1] == ':')
				token = strtok(NULL, " \t\n");

			printf("%s\n", token);

			for(size_t i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
				option = 0;

				if(strcasecmp(map[i].name, token) == 0) {
					token = strtok(NULL, " \t\n");

					switch(map[i].type) {
						case RRR:
							sscanf(token, "%" SCNd8 ",%" SCNd8 ",%" SCNd8, &ops[0], &ops[1], &ops[2]);

							option = (i << 13);
							option |= (ops[0] << 10);
							option |= (ops[1] << 7);
							option |= (ops[2]);
							
							break;
						case RRI:
							sscanf(token, "%" SCNd8 ",%" SCNd8 ",%s", &ops[0], &ops[1], imm);

							option = (i << 13);
							option |= (ops[0] << 10);
							option |= (ops[1] << 7);
							option |= (resolve_label(imm) & 0xFF);

							break;
						case RI:
							break;
					}

					printf("%04x\n", option & 0xFFFF);
				}
			}
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

	index_labels();
	rewind(stream);
	parse_file();

	return 0;
}
