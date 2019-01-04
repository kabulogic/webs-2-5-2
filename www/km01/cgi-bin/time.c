#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	time_t time_n;
	time(&time_n);
	printf("%lu\n", time_n);
    return 0;
}
