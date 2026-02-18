/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:11:47 by tmege             #+#    #+#             */
/*   Updated: 2025/05/28 17:04:53 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_get_number_str(int n, int *is_neg)
{
	*is_neg = 0;
	if (n == -2147483648)
	{
		*is_neg = 1;
		return (ft_strdup("2147483648"));
	}
	if (n < 0)
	{
		*is_neg = 1;
		n = -n;
	}
	return (ft_itoa(n));
}

int	ft_print_sign(t_format *fmt, int is_neg)
{
	if (is_neg)
		return (ft_print_char(fmt, '-'));
	else if (fmt->plus)
		return (ft_print_char(fmt, '+'));
	else if (fmt->space)
		return (ft_print_char(fmt, ' '));
	return (0);
}

int	ft_print_padding(char c, int count)
{
	int	len;

	len = 0;
	while (count-- > 0)
		len += ft_print_char(NULL, c);
	return (len);
}

int	ft_calc_needed_len(t_format *fmt, int num_len, int is_neg)
{
	int	needed_len;

	needed_len = num_len;
	if (fmt->precision > num_len)
		needed_len = fmt->precision;
	if (is_neg)
		needed_len += 1;
	else if (fmt->plus || fmt->space)
		needed_len += 1;
	return (needed_len);
}
