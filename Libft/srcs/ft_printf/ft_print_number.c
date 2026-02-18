/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:57:04 by tmege             #+#    #+#             */
/*   Updated: 2025/05/28 17:00:33 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_numcore(t_format *fmt, char *num_str, int num_len, int is_neg)
{
	int	len;
	int	padding;
	int	needed_len;
	int	zero_pad;

	len = 0;
	padding = 0;
	zero_pad = 0;
	needed_len = ft_calc_needed_len(fmt, num_len, is_neg);
	if (fmt->width > needed_len)
		padding = fmt->width - needed_len;
	if (!fmt->minus && (!fmt->zero || fmt->dot))
		len += ft_print_padding(' ', padding);
	len += ft_print_sign(fmt, is_neg);
	if (!fmt->minus && fmt->zero && !fmt->dot)
		len += ft_print_padding('0', padding);
	if (fmt->precision > num_len)
		zero_pad = fmt->precision - num_len;
	len += ft_print_padding('0', zero_pad);
	if (!(fmt->dot && fmt->precision == 0 && num_len == 1 && num_str[0] == '0'))
		len += write(1, num_str, num_len);
	if (fmt->minus)
		len += ft_print_padding(' ', padding);
	return (len);
}

int	ft_print_number(t_format *fmt, int n)
{
	char		*num_str;
	int			len;
	int			is_neg;
	int			num_len;

	num_str = ft_get_number_str(n, &is_neg);
	if (!num_str)
		return (0);
	num_len = ft_strlen(num_str);
	len = ft_print_numcore(fmt, num_str, num_len, is_neg);
	free(num_str);
	return (len);
}
