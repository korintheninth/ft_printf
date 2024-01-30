/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamati <emamati@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:22:57 by emamati           #+#    #+#             */
/*   Updated: 2024/01/30 15:25:32 by emamati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
#include <stdarg.h>

int	type_handler(char type, va_list input, char flags, int *arg)
{
	int	len;

	len = 0;
	if (type == 's')
		len += type_s(va_arg(input, char *), flags, arg);
	else if (type == 'd' || type == 'i')
		len += ft_putnbr_long(va_arg(input, int), flags, arg);
	else if (type == 'p')
		len += type_hex(va_arg(input, unsigned long), flags, type, arg);
	else if (type == '%')
		len += type_percent(flags, arg);
	else if (type == 'x')
		len += type_hex(va_arg(input, unsigned int), flags, type, arg);
	else if (type == 'u' || type == 'U')
		len += ft_putnbr_long(va_arg(input, unsigned int), flags, arg);
	else if (type == 'X')
		len += type_hex(va_arg(input, unsigned int), flags, type, arg);
	else if (type == 'c')
		len += type_c(va_arg(input, int), flags, arg);
	return (len);
}

int	flag_handler(char c, unsigned char flags)
{
	if (c == '.')
		flags |= 1 << 5;
	if (c == '-')
		flags |= 1 << 4;
	if (c == '0')
		flags |= 1 << 3;
	if (c == '+')
		flags |= 1 << 2;
	if (c == '#')
		flags |= 1 << 1;
	if (c == ' ')
		flags |= 1 << 0;
	return (flags);
}

int	get_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

t_FormatInfo	parse_format(va_list input, const char **args)
{
	t_FormatInfo	info;
	char			mode;
	char			*flags;

	mode = 0;
	flags = "-0.";
	ft_bzero(info.arg, 4 * sizeof(int));
	info.flags = 0;
	while (!ft_isalpha((*args)[1]) && (*args)[1] != '%')
	{
		info.flags = flag_handler((*args)[1], info.flags);
		if (ft_isdigit((*args)[1]))
		{
			if (!(ft_isdigit((*args)[0])) && (*args)[1] == '0' && mode == 0)
				mode = '0';
			info.arg[get_index(flags, mode)]
				= info.arg[get_index(flags, mode)] * 10 + ((*args)[1] - '0');
		}
		else if ((*args)[1] == '-' || (*args)[1] == '.')
			mode = (*args)[1];
		else if ((*args)[1] == '*')
			info.arg[get_index(flags, mode)] = va_arg(input, int);
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
			info = parse_format(input, &args);
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
