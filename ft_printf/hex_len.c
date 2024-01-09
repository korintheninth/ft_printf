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

int	hex_len(unsigned long int nb)
{
	int	len;

	len = 0;
	if (nb >= 16)
		len += hex_len(nb / 16);
	len++;
	return (len);
}

int	putnbr_sub(long int nb, const char flags, int *arg, int len)
{
	while (arg[ARGEMPTY] > len || (arg[ARG0] > len && flags & (1 << FLAGDOT)))
		len += write(1, " ", 1);
	if (flags & (1 << FLAGSPACE) && nb >= 0 && !(flags & (1 << FLAGPLUS)))
		len += write(1, " ", 1);
	if (nb < 0)
		write(1, "-", 1);
	if (flags & (1 << FLAGPLUS) && nb >= 0)
		write(1, "+", 1);
	while (arg[ARG0] > len && !(flags & (1 << FLAGDOT)))
		len += write(1, "0", 1);
	return (len);
}
