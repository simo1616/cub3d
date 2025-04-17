#include <unistd.h>
#include <stdio.h>


int main ()
{
	double i = 0.0;
	char *str = "simo";
	while(str[i])
	{
		printf("%s\n", str);
		i++;
	}
	return(0);
}