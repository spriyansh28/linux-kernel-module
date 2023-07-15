#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "ioctl_test.h"

int main() {
	int answer;
	struct mystruct test = {4, "Priyansh"};
	int dev = open("/dev/testdriver", O_WRONLY);
	if(dev == -1) {
		printf("Opening was not possible!\n");
		return -1;
	}

	ioctl(dev, RD_VALUE, &answer);
	printf("The old data is %d\n", answer);

	answer = 53542;

	ioctl(dev, WR_VALUE, &answer);
	ioctl(dev, RD_VALUE, &answer);
	printf("The new data is %d\n", answer);

	ioctl(dev, &test);

	printf("Opening was successfull!\n");
	close(dev);
	return 0;
}
