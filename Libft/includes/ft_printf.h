/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:51:45 by tmege             #+#    #+#             */
/*   Updated: 2025/05/28 16:48:26 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_format
{
	int		minus;
	int		zero;
	int		plus;
	int		space;
	int		hash;
	int		width;
	int		dot;
	char	type;
	int		precision;
}	t_format;

int		ft_parser(const char *s, int *i, t_format *fmt, va_list args);
void	ft_init_format(t_format *fmt);
int		ft_dispatch_conversion(t_format *fmt, va_list args);
int		ft_print_char(t_format *fmt, char c);
int		ft_print_string(t_format *fmt, char *str);
char	*ft_get_number_str(int n, int *is_negative);
int		ft_print_sign(t_format *fmt, int n);
int		ft_print_padding(char c, int count);
int		ft_calc_needed_len(t_format *fmt, int num_len, int is_neg);
int		ft_print_number(t_format *fmt, int n);
int		ft_print_numcore(t_format *fmt, char *num_str, int num_len, int is_neg);
int		ft_print_unsigned(t_format *fmt, unsigned int n);
char	*ft_utoa_base(unsigned int n, char *base);
char	*ft_hex_prepare(unsigned int n, int upper);
int		ft_print_prefix(t_format *fmt, unsigned int n, int upper);
int		ft_hex_padding(t_format *fmt, int total_len);
int		ft_prefix_len(t_format *fmt, unsigned int n);
int		ft_print_hex(t_format *fmt, unsigned int n, int upper);
int		ft_print_pointer(t_format *fmt, void *ptr);
int		ft_printf(const char *format, ...);

#endif
