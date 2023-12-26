/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamati <emamati@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:06:09 by emamati           #+#    #+#             */
/*   Updated: 2023/12/16 17:38:48 by emamati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *args, ...);
int	type_hex(unsigned long nb, char *hex, unsigned char flags, char type, int arg);
int	ft_putnbr_long(long int nb, unsigned char flags, int arg);
int	type_s(char *print_arg, unsigned char flags, char type, int arg);
int	type_c(char c, unsigned char flags, char type, int args);

#endif
