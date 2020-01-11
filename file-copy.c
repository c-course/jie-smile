#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX 1024

int filecopy(const char *p1, const char *p2)
{
	char buf[MAX];
	int file = open(p1, O_RDONLY);
	if (file < 0)
		return 1;
	int backup = open(p2, O_WRONLY | O_CREAT, S_IRWXU);

	int n;
	while ((n = read(file, buf, MAX)))
		write(backup, buf, n);

	close(file);
	close(backup);
	return 0;
}

int main()
{
	int status = filecopy("../file/test.txt", "../file/test.txt.backup");
	return status;
}
