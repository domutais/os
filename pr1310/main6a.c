#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
	if (argc != 3) {
		printf("Usage: ./main6a.o [name] [value] (-o).\nCreates a new env. variable [name] = [value]. When flag -o is set, overwrites if [name] already exists.\n");
		return 0;
	}

	setenv(argv[1], argv[2], 1);
	printf("%s = %s\n", argv[1], getenv(argv[1]));

	return 0;
}
