/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:30:13 by tmege             #+#    #+#             */
/*   Updated: 2025/05/28 17:06:00 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_utoa(unsigned int n)
{
	char			*str;
	int				len;
	unsigned int	tmp;

	len = 1;
	tmp = n;
	while (tmp >= 10)
	{
		tmp /= 10;
		len++;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = '\0';
	while (len--)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

static int	print_unsigned_padding(t_format *fmt, char *str, int num_len)
{
	int	len;
	int	precision;
	int	padding;
	int	print_len;

	len = 0;
	precision = fmt->precision;
	if (precision > num_len)
		print_len = precision;
	else
		print_len = num_len;
	padding = fmt->width - print_len;
	if (!fmt->minus && (!fmt->zero || fmt->dot))
		len += ft_print_padding(' ', padding);
	else if (!fmt->minus && fmt->zero && !fmt->dot)
		len += ft_print_padding('0', padding);
	len += ft_print_padding('0', precision - num_len);
	if (num_len > 0)
		len += write(1, str, num_len);
	if (fmt->minus)
		len += ft_print_padding(' ', padding);
	return (len);
}

int	ft_print_unsigned(t_format *fmt, unsigned int n)
{
	char	*str;
	int		num_len;
	int		len;

	str = ft_utoa(n);
	if (!str)
		return (0);
	num_len = ft_strlen(str);
	if (fmt->dot && fmt->precision == 0 && n == 0)
		num_len = 0;
	len = print_unsigned_padding(fmt, str, num_len);
	free(str);
	return (len);
}
