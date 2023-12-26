/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamati <emamati@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:05:29 by emamati           #+#    #+#             */
/*   Updated: 2023/12/16 17:43:35 by emamati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int	ft_puthex(unsigned long nb, char *hex)
{
	int	len;

	len = 0;
	if (nb >= 16)
		len += ft_puthex(nb / 16, hex);
	len += write(1, &hex[nb % 16], 1);
	return (len);
}

int	num_len(unsigned long nb, int base)
{
	int	len;

	len = 0;
	if (nb >= base)
		len += num_len(nb / base, base);
	len++;
	return (len);
}

int put_num(long int nb)
{

	int	len;

	len = 0;
	if (nb >= 10)
	{
		len += put_num(nb / 10);
		len += put_num(nb % 10);
	}
	else
	{
		char	c;
		c = nb + '0';
		len += write(1,&c,1);
	}
	return (len);
}

int	ft_putnbr_long(long int nb, unsigned char flags, int arg)
{
	int len;

	len = 0;
	if (flags & (1<<4) && nb >= 0)
		len += write(1, "+", 1);
	if (flags & (1 << 2) && nb > 0 && !(flags & (1 << 4)))
		len += write(1," ",1);
	while (len < arg - (num_len(-nb, 10) + 1) && nb < 0 && !(flags & (1 << 1)) && !(flags & (1 << 0))) 
		len += write(1, " ", 1);
	while (len < arg - num_len(nb, 10) && nb >= 0 && !(flags & (1 << 1)) && !(flags & (1 << 0))) 
		len += write(1, " ", 1);
	if (nb < 0)
	{
		len += write(1,"-",1);
		nb = -nb;
	}
	while (len < arg - num_len(nb, 10) && flags & (1 << 1) && nb >= 0 && !(flags & (1 << 0))) 
		len += write(1, "0", 1);
	len += put_num(nb);
	while (len < arg && flags & (1 << 0))
		len += write(1, " ", 1);
	return (len);
}

int	type_s(char *print_arg, unsigned char  flags, char type, int arg)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (len < arg - (ft_strlen(print_arg)) && !(flags & (1 << 0))) 
		len += write(1, " ", 1);
	if (!print_arg)
		return (write(1, "(null)", 6));
	while (print_arg[i])
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
	len += write(1,&c,1);
	while (len < arg && flags & (1 << 0))
		len += write(1, " ", 1);
	return (len);
}

int	type_hex(unsigned long nb, char *hex, unsigned char flags, char type, int arg)
{
	int	len;

	len = 0;
	while (len < arg - num_len(nb, 16) && !(flags & (1 << 1)) && !(flags & (1 << 0))) 
		len += write(1, " ", 1);
	if (flags & (1<<3) && type == 'x')
		len += write(1,"0x", 2);
	else if (flags & (1<<3) && type == 'X')
		len += write(1, "0X", 2);
	while (len < arg - num_len(nb, 16) && flags & (1 << 1) && !(flags & (1 << 0))) 
		len += write(1, "0", 1);
	len += ft_puthex(nb, hex);
	while (len < arg && flags & (1 << 0))
		len += write(1, " ", 1);
	return (len);
}
