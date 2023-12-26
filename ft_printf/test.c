#include "ft_printf.h"
#include "libft/libft.h"
#include <stdio.h>
int main()
{
	char *var = NULL;
	printf("return: %d\n",ft_printf("%51d %10c %20s ", -1234, 'c', "1234"));

	printf("return: %d\n",printf("%51d %10c %20s ", -1234, 'c', "1234"));
	
}
