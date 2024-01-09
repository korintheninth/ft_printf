/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamati <emamati@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:26:57 by emamati           #+#    #+#             */
/*   Updated: 2023/12/26 17:31:37 by emamati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(unsigned long nb, char type)
{
	int		len;
	char	*hex;

	hex = "0123456789ABCDEF";
	if (type == 'x' || type == 'p')
		hex = "0123456789abcdef";
	len = 0;
	if (nb >= 16)
		len += ft_puthex(nb / 16, type);
	len += write(1, &hex[nb % 16], 1);
	return (len);
}

int	num_len(long long nb)
{
	int	len;

	len = 0;
	if (nb < 0)
		nb *= -1;
	if (nb >= 10)
		len += num_len(nb / 10);
	len++;
	return (len);
}

int	put_num(long int nb)
{
	int		len;
	char	c;

	len = 0;
	if (nb < 0)
		nb *= -1;
	if (nb >= 10)
	{
		len += put_num(nb / 10);
		len += put_num(nb % 10);
	}
	else
	{
		c = nb + '0';
		len += write(1, &c, 1);
	}
	return (len);
}

int	str_len(const char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	while (arg[i])
		i++;
	return (i);
}

int	get_len(unsigned char flags, char type, int *arg, unsigned long nb)
{
	int	len;

	len = 0;
	if ((flags & (1 << 1) && nb != 0) || type == 'p')
		len += 2;
	if (arg[2] > hex_len(nb))
		len += arg[2];
	else
		len += hex_len(nb);
	return (len);
}
