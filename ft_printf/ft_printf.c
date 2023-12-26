/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamati <emamati@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:22:57 by emamati           #+#    #+#             */
/*   Updated: 2023/12/26 17:27:24 by emamati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
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
		len += type_hex(va_arg(input, unsigned long), flags, type, arg);
	else if (type == '%')
		len += write(1, "%%", 1);
	else if (type == 'x')
		len += type_hex(va_arg(input, unsigned int), flags, type, arg);
	else if (type == 'u' || type == 'U')
		len += ft_putnbr_long(va_arg(input, unsigned int), flags, arg);
	else if (type == 'X')
		len += type_hex(va_arg(input, unsigned int), flags, type, arg);
	else if (type == 'c')
		len += type_c(va_arg(input, int), flags, type, arg);
	else if (type == 's')
		len += type_s(va_arg(input, char *), flags, type, arg);
	return (len);
}

int	flag_handler(char c, unsigned char flags)
{
	if (c == '.')
		flags |= 1 << 5;
	if (c == '+')
		flags |= 1 << 4;
	if (c == '#')
		flags |= 1 << 3;
	if (c == ' ')
		flags |= 1 << 2;
	if (c == '0')
		flags |= 1 << 1;
	if (c == '-')
		flags |= 1 << 0;
	return (flags);
}

t_FormatInfo	parse_format(const char **args)
{
	t_FormatInfo	info;

	info.arg = 0;
	info.flags = 0;
	while (!ft_isalpha((*args)[1]) && (*args)[1] != '%')
	{
		info.flags = flag_handler((*args)[1], info.flags);
		if (ft_isalnum((*args)[1]))
			info.arg = info.arg * 10 + (*args)[1] - '0';
		(*args)++;
	}
	return (info);
}

int	ft_printf(const char *args, ...)
{
	va_list			input;
	int				len;
	t_FormatInfo	info;

	len = 0;
	va_start(input, args);
	while (*args)
	{
		if (*args == '%')
		{
			info = parse_format(&args);
			len += type_handler(args[1], input, info.flags, info.arg);
			args++;
		}
		else
			len += write(1, args, 1);
		args++;
	}
	va_end(input);
	return (len);
}
