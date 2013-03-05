#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>

void printUsage();
void export(int pin);
void unexport(int pin);
void changeOwner(int pin, const char *filename, int uid, int gid);
void writePinToFile(int pin, const char *path);

int main(int argc, char *argv[]) {
	int uid, gid;

	uid = getuid();
	gid = getgid();

   	if (setuid(0) < 0) {
   		fprintf(stderr, "setuid() failed: %d - %s\n", errno, strerror(errno));
		exit(-errno);
   	}

   	if (argc == 3) {
	   	int pin = atoi(argv[2]);

   		if (strcmp(argv[1], "export") == 0) {
	   		export(pin);
	   		changeOwner(pin, "value", uid, gid);
	   		changeOwner(pin, "direction", uid, gid);
   		}

   		if (strcmp(argv[1], "unexport") == 0) {
	   		unexport(pin);
   		}
   	}
   	else {
   		printUsage(argv);
   	}

   	return 0;
}

void printUsage(char *argv[]) {
	fprintf(stderr, "Usage: %s export <pin>\n\n", argv[0]);
	exit(1);
}

void export(int pin) {
	writePinToFile(pin, "/sys/class/gpio/export");
}

void unexport(int pin) {
	writePinToFile(pin, "/sys/class/gpio/unexport");
}

void changeOwner(int pin, const char *filename, int uid, int gid) {
  	char path[PATH_MAX];
  	int size = snprintf(path, PATH_MAX, "/sys/class/gpio/gpio%d/%s", pin, filename);
  
  	if (size >= PATH_MAX) {
  		fprintf(stderr, "Path of GPIO pin is too long!");
   		return;
  	}

	if (chown(path, uid, gid) < 0) {
   		fprintf(stderr, "Failed to change ownership of file %s to (%d:%d): %d - %s\n", path, uid, gid, errno, strerror(errno));
		exit(-errno);
	} 
}

void writePinToFile(int pin, const char *path) {
	FILE *fd;

	fd = fopen(path, "w");
	if (fd == NULL) {
   		fprintf(stderr, "Failed to open file %s: %d - %s\n", path, errno, strerror(errno));
		exit(-errno);
	}

	if (fprintf(fd, "%d", pin) < 0) {
   		fprintf(stderr, "Failed to write pin number to file %s: %d - %s\n", path, errno, strerror(errno));
		exit(-errno);
	}

	if (fclose(fd) == EOF) {
   		fprintf(stderr, "Failed to flush data to file %s: %d - %s\n", path, errno, strerror(errno));
		exit(-errno);
	}
}
