#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int clearenv(void) __THROW;

int main(int argc, char **argv) {
	if (argc == 1) clearenv();

	for (int i = 1; i < argc; i++) {
		unsetenv(argv[i]);
		printf("%s = %s\n", argv[i], getenv(argv[i]));
	}

	return 0;
}
