#include <stdio.h>
#include <stdlib.h>


FILE *stream;

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

	return 0;
}
