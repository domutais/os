#include <stdio.h>
#include <sys/utsname.h>

int main(void) {
	struct utsname name;

	uname(&name);

	printf("os: %s\n", name.sysname);
	printf("name: %s\n", name.nodename);
	printf("release: %s\n", name.release);
	printf("version: %s\n", name.version);
	printf("machine: %s\n", name.machine);

	return 0;

}
