/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:32:09 by tmege             #+#    #+#             */
/*   Updated: 2025/05/28 16:51:35 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_utoa_base_long(unsigned long n, char *base)
{
	char			*str;
	int				len;
	unsigned long	tmp;
	int				base_len;

	base_len = ft_strlen(base);
	len = 1;
	tmp = n;
	while (tmp >= (unsigned long)base_len)
	{
		tmp /= base_len;
		len++;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = '\0';
	while (len--)
	{
		str[len] = base[n % base_len];
		n /= base_len;
	}
	return (str);
}

static int	ft_print_null_pointer(t_format *fmt)
{
	int	len;
	int	padding;

	len = 0;
	padding = fmt->width - 5;
	if (padding < 0)
		padding = 0;
	if (!fmt->minus)
		len += ft_print_padding(' ', padding);
	len += write(1, "(nil)", 5);
	if (fmt->minus)
		len += ft_print_padding(' ', padding);
	return (len);
}

int	ft_print_pointer(t_format *fmt, void *ptr)
{
	unsigned long	addr;
	char			*str;
	int				len;
	int				num_len;
	int				padding;

	if (!ptr)
		return (ft_print_null_pointer(fmt));
	addr = (unsigned long)ptr;
	str = ft_utoa_base_long(addr, "0123456789abcdef");
	if (!str)
		return (0);
	num_len = ft_strlen(str) + 2;
	padding = fmt->width - num_len;
	len = 0;
	if (!fmt->minus)
		len += ft_print_padding(' ', padding);
	len += write(1, "0x", 2);
	len += write(1, str, ft_strlen(str));
	if (fmt->minus)
		len += ft_print_padding(' ', padding);
	free(str);
	return (len);
}
