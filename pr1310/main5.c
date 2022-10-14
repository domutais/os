#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	if (argc == 1) printf("Usage:\n\t./main5.o [name]\n\twhere [name] is the name of env. variable.\n");

	for (int i = 1; i < argc; i++) {
		printf("%s = %s\n", argv[i], getenv(argv[i]));
	}

	return 0;
}
