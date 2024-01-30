/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamati <emamati@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:05:29 by emamati           #+#    #+#             */
/*   Updated: 2024/01/30 15:54:40 by emamati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define ARGEMPTY 3
#define ARGMINUS 0
#define ARG0 1
#define ARGDOT 2
#define FLAGDOT 5
#define FLAGMINUS 4
#define FLAG0 3
#define FLAGPLUS 2
#define FLAGSHARP 1
#define FLAGSPACE 0

int	ft_putnbr_long(long int nb, unsigned char flags, int *arg)
{
	int	len;
	int	numlen;

	numlen = 0;
	if (nb != 0 || arg[ARGDOT] > 0 || !(flags & (1 << FLAGDOT)))
		numlen = num_len(nb);
	len = 0;
	if (arg[ARGDOT] > numlen)
		len += arg[ARGDOT];
	else
		len += numlen;
	if (flags & (1 << FLAGPLUS) || nb < 0)
		len ++;
	len = putnbr_sub(nb, flags, arg, len);
	while (((arg[ARGDOT]--) - numlen) > 0)
		write(1, "0", 1);
	if (nb != 0 || num_len(nb) == numlen)
		put_num(nb);
	while (arg[ARGMINUS] > len)
		len += write(1, " ", 1);
	return (len);
}

int	type_s(char *print_arg, unsigned char flags, int *arg)
{
	int	len;
	int	i;

	len = 0;
	if (print_arg == NULL)
		print_arg = "(null)";
	if (flags & (1 << FLAGDOT) && arg[ARGDOT] < str_len(print_arg))
		len += arg[ARGDOT];
	else if ((!print_arg) && (arg[ARGDOT] >= 6 || !(flags & (1 << FLAGDOT))))
		len += 6;
	else
		len += str_len(print_arg);
	while (arg[ARGEMPTY] > len || arg[ARG0] > len)
		len += write(1, " ", 1);
	i = 0;
	if (print_arg && print_arg != NULL)
	{
		while ((flags & (1 << FLAGDOT) && (arg[ARGDOT]--) > 0 && print_arg[i])
			|| (!(flags & (1 << FLAGDOT)) && print_arg[i]))
			write(1, &print_arg[i++], 1);
	}
	while (arg[ARGMINUS] > len)
		len += write(1, " ", 1);
	return (len);
}

int	type_c(char c, unsigned char flags, int *arg)
{
	int	len;

	len = 0;
	while (len < arg[ARGEMPTY] - 1 || len < arg[ARG0] - 1)
		len += write(1, " ", 1);
	len += write(1, &c, 1);
	while (len < arg[ARGMINUS] && flags & (1 << FLAGMINUS))
		len += write(1, " ", 1);
	return (len);
}

int	type_hex(unsigned long nb, unsigned char flags, char type, int *arg)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (nb != 0 || arg[ARGDOT] > 0 || !(flags & (1 << FLAGDOT)))
		len = get_len(flags, type, arg, nb);
	if (arg[ARGDOT] > len)
		len = arg[ARGDOT];
	while (arg[ARGEMPTY] > len || (arg[ARG0] > len && flags & (1 << FLAGDOT)))
		len += write(1, " ", 1);
	if ((flags & (1 << FLAGSHARP) && type == 'x' && nb != 0) || type == 'p')
		write(1, "0x", 2);
	else if (flags & (1 << FLAGSHARP) && type == 'X' && nb != 0)
		write(1, "0X", 2);
	while (arg[ARG0] > len && !(flags & (1 << FLAGDOT)))
		len += write(1, "0", 1);
	while ((arg[ARGDOT]) - hex_len(nb) > i++)
		write(1, "0", 1);
	if (nb != 0 || arg[ARGDOT] > 0 || !(flags & (1 << FLAGDOT)))
		ft_puthex(nb, type);
	while (arg[ARGMINUS] > len)
		len += write(1, " ", 1);
	return (len);
}

int	type_percent(unsigned char flags, int *arg)
{
	int	len;

	len = 0;
	while (len < arg[ARGEMPTY] - 1 || len < arg[ARG0] - 1)
		len += write(1, " ", 1);
	len += write(1, "%", 1);
	while (len < arg[ARGMINUS] && flags & (1 << FLAGMINUS))
		len += write(1, " ", 1);
	return (len);
}
