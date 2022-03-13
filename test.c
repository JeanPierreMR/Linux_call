#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
int main()
{
	char exp[100];
	double result;
	scanf("%s", exp);
	char *x = exp;
	// Function call
	if (syscall(329, x))
	{
	printf("Balanced \n");
	}
	else
	printf("Not Balanced \n");
	return 0;
}
