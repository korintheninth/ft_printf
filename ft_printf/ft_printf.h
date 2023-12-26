/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamati <emamati@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:06:09 by emamati           #+#    #+#             */
/*   Updated: 2023/12/26 17:31:47 by emamati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/libft.h"
# include <stdarg.h>
# include <unistd.h>

typedef struct t_FormatInfo
{
	char	flags;
	int		arg;
}			t_FormatInfo;

int			ft_printf(const char *args, ...);
int			type_hex(unsigned long nb, unsigned char flags, char type, int arg);
int			ft_putnbr_long(long int nb, unsigned char flags, int arg);
int			type_s(char *print_arg, unsigned char flags, char type, int arg);
int			type_c(char c, unsigned char flags, char type, int args);
int			ft_puthex(unsigned long nb, char *hex);
int			put_num(long int nb);
int			num_len(unsigned long nb, int base);
size_t		strlen(const char *arg);

#endif
