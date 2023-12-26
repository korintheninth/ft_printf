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

int	put_num(long int nb)
{
	int		len;
	char	c;

	len = 0;
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

size_t	strlen(const char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	while (arg[i])
		i++;
	return (i);
}
