/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamati <emamati@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:05:29 by emamati           #+#    #+#             */
/*   Updated: 2023/12/26 18:37:44 by emamati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int	ft_putnbr_long(long int nb, unsigned char flags, int arg)
{
	int	len;

	len = 0;
	if (flags & (1 << 4) && nb >= 0)
		len += write(1, "+", 1);
	if (flags & (1 << 2) && nb >= 0 && !(flags & (1 << 4)))
		len += write(1, " ", 1);
	while (len < arg - (num_len(-nb, 10) + 1) && nb < 0 && !(flags & (1 << 1))
		&& !(flags & (1 << 0)) && !(flags & (1 << 5)))
		len += write(1, " ", 1);
	while (len < arg - num_len(nb, 10) && nb >= 0 && !(flags & (1 << 1))
		&& !(flags & (1 << 0)) && !(flags & (1 << 5)))
		len += write(1, " ", 1);
	if (nb < 0)
	{
		len += write(1, "-", 1);
		nb = -nb;
	}
	while (flags & (1 << 5) &&  0 < (arg -num_len(nb, 10)))
	{
		len += write(1,"0",1);
		arg--;
	}
	while (len < arg - num_len(nb, 10) && flags & (1 << 1)
		&& !(flags & (1 << 0)))
		len += write(1, "0", 1);
	len += put_num(nb);
	while (len < arg && flags & (1 << 0))
		len += write(1, " ", 1);
	return (len);
}

int	type_s(char *print_arg, unsigned char flags, char type, int arg)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	if (!print_arg)
		return (write(1, "(null)", 6));
	while (len < (int)(arg - (strlen(print_arg))) && !(flags & (1 << 0)) && !(flags & (1 << 5)))
		len += write(1, " ", 1);
	while (print_arg[i] && !(flags & (1 << 5) && i >= arg))
		write(1, &print_arg[i++], 1);
	len += i;
	while (len < arg && flags & (1 << 0))
		len += write(1, " ", 1);
	return (len);
}

int	type_c(char c, unsigned char flags, char type, int arg)
{
	int	len;

	len = 0;
	while (len < arg - 1 && !(flags & (1 << 0)))
		len += write(1, " ", 1);
	len += write(1, &c, 1);
	while (len < arg && flags & (1 << 0))
		len += write(1, " ", 1);
	return (len);
}

int	type_hex(unsigned long nb, unsigned char flags, char type, int arg)
{
	int		len;
	char	*hex;

	len = 0;
	if (type == 'x' || type == 'p')
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	while (len < arg - num_len(nb, 16) && !(flags & (1 << 1))
		&& !(flags & (1 << 0)) && !(flags & (1 << 5)))
		len += write(1, " ", 1);
	if ((flags & (1 << 3) && type == 'x' && nb != 0) || type == 'p' )
		len += write(1, "0x", 2);
	else if (flags & (1 << 3) && type == 'X' && nb != 0)
		len += write(1, "0X", 2);
	while (len < arg - num_len(nb, 16) && flags & (1 << 1)
		&& !(flags & (1 << 0)) && !(flags & (1 << 5)))
		len += write(1, "0", 1);
	while (flags & (1 << 5) &&  0 < (arg - num_len(nb, 16)))
	{
		len += write(1,"0",1);
		arg--;
	}
	len += ft_puthex(nb, hex);
	while (len < arg && flags & (1 << 0))
		len += write(1, " ", 1);
	return (len);
}
