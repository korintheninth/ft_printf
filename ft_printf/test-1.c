#include "ft_printf.h"
#include "libft/libft.h"
#include <stdio.h>
int main()
{
	char *var = NULL;
	printf("return: %d\n",ft_printf("^.^/%030.22d^.^/", 1));

	printf("return: %d\n",printf("^.^/%030.22d^.^/", 1));
	
}
