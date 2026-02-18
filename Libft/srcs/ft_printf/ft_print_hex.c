/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:31:13 by tmege             #+#    #+#             */
/*   Updated: 2025/05/28 17:09:27 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_add_precision(char *str, int precision)
{
	int		len;
	char	*new_str;

	len = ft_strlen(str);
	if (precision <= len)
		return (str);
	new_str = ft_calloc(precision + 1, sizeof(char));
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	ft_memset(new_str, '0', precision - len);
	ft_memcpy(new_str + (precision - len), str, len);
	free(str);
	return (new_str);
}

int	ft_print_hex_body(t_format *fmt, char *str, unsigned int n, int upper)
{
	int	len;
	int	num_len;
	int	prefix_len;

	len = 0;
	num_len = ft_strlen(str);
	if (fmt->dot && fmt->precision == 0 && n == 0)
		num_len = 0;
	prefix_len = ft_prefix_len(fmt, n);
	if (fmt->zero && !fmt->minus && !fmt->dot)
	{
		len += ft_print_prefix(fmt, n, upper);
		len += ft_hex_padding(fmt, num_len + prefix_len);
	}
	else
	{
		len += ft_hex_padding(fmt, num_len + prefix_len);
		len += ft_print_prefix(fmt, n, upper);
	}
	if (!(fmt->dot && fmt->precision == 0 && n == 0))
		len += write(1, str, num_len);
	if (fmt->minus && fmt->width > len)
		len += ft_print_padding(' ', fmt->width - len);
	return (len);
}

int	ft_print_hex(t_format *fmt, unsigned int n, int upper)
{
	char	*str;
	int		len;
	char	*tmp;

	str = ft_hex_prepare(n, upper);
	if (!str)
		return (0);
	if (fmt->dot)
	{
		tmp = ft_add_precision(str, fmt->precision);
		if (!tmp)
		{
			free(str);
			return (0);
		}
		str = tmp;
	}
	len = ft_print_hex_body(fmt, str, n, upper);
	free(str);
	return (len);
}
