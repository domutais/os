#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

void help() {
	printf("Available flags:\n");
	printf("  -h\tshows this message\n");
	printf("  -c\tspecial mode (explanation here!!!)\n");
	printf("  -o [output_name]\tsets output file to [output_name]\n");
	printf("  [in1] [in2] ... \tsets input files\n");
}

int main(int argc, char **argv) {
	if (argc == 1) {
		help();
		return 0;
	}

	int cflag = 0;
	char *ovalue = "default.out";
	char c;

	while (((c = getopt(argc, argv, "hco:")) != -1)) {
		switch (c) {
			case 'h':
				help();
				break;
			case 'c':
				cflag = 1;
				break;
			case 'o':
				ovalue = optarg;
				break;
			case '?':
				if (isprint(optopt)) fprintf(stderr, "-%c is not a valid flag.\n", optopt);
				else fprintf(stderr, "Invalid character \\x%x.\n", optopt);
		}
	}

	for (int i = optind; i < argc; i++) {
		printf("Input file registered: %s\n", argv[i]);
	}

	printf("\nSpecial mode: %s\n", (cflag ? "ON" : "OFF"));
	printf("Output file: '%s'\n", ovalue);

	return 0;
}
