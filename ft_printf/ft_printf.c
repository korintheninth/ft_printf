/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamati <emamati@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:16:27 by emamati           #+#    #+#             */
/*   Updated: 2023/12/16 17:39:42 by emamati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"
#include <stdarg.h>

int	type_handler(char type, va_list input, char flags, int arg)
{
	int	len;

	len = 0;
	if (type == 's')
		len += type_s(va_arg(input, char *), flags, type, arg);
	else if (type == 'd' || type == 'i')
		len += ft_putnbr_long(va_arg(input, int), flags, arg);
	else if (type == 'p')
	{
		len += write(1, "0x", 2);
		len += type_hex(va_arg(input, unsigned long), "0123456789abcdefg", flags, type, arg);
	}
	else if (type == '%')
		len += write(1, "%%", 1);
	else if (type == 'x')
		len += type_hex(va_arg(input, unsigned int), "0123456789abcdefg", flags, type, arg);
	else if (type == 'u' || type == 'U')
		len += ft_putnbr_long(va_arg(input, unsigned int), flags, arg);
	else if (type == 'X')
		len += type_hex(va_arg(input, unsigned int), "0123456789ABCDEFG", flags, type, arg);
	else if (type == 'c')
		len += type_c(va_arg(input, int), flags, type, arg);
	else if (type == 's')
		 len += type_s(va_arg(input, char *), flags, type, arg);
	return (len);
}

int	flag_handler(char c, unsigned char flags) 
{
	char init;

	init = flags;
	if (flags >= 16)
		flags -= 16;
	else if (c == '+')
		init += 16;
	if (flags >= 8)
		flags -= 8;
	else if (c == '#')
		init += 8;
	if (flags >= 4)
		flags -= 4;
	else if (c == ' ')
		init += 4;
	if (flags >= 2)
		flags -= 2;
	else if (c == '0')
		init += 2;
	if (flags >= 1)
		flags -= 1;
	else if (c == '-')
		init += 1;
	return (init);
}

int	ft_printf(const char *args, ...)
{
	char	type;
	int		j;
	va_list	input;
	int		len;
	char	flags;
	int	arg;

	len = 0;
	va_start(input, args);
	j = 0;
	while (args[j])
	{
		if (args[j] == '%')
		{
			flags = 0;
			arg = 0;
			while (!ft_isalpha(args[j + 1]) && args[j + 1] != '%')
			{
				flags = flag_handler(args[j + 1], flags);
				if (ft_isalnum(args[j + 1]))
					arg = arg * 10 + args[j + 1] - '0';
				j++;
			}
			type = args[j + 1];
			len += type_handler(type, input, flags, arg);
			j++;
		}
		else
			len += write(1, &args[j], 1);
		j++;
	}
	va_end(input);
	return (len);
}

