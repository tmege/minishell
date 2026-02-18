/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:20:23 by tmege             #+#    #+#             */
/*   Updated: 2025/05/28 17:12:24 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_utoa_base(unsigned int n, char *base)
{
	char			*str;
	int				len;
	unsigned int	tmp;
	int				base_len;

	base_len = ft_strlen(base);
	len = 1;
	tmp = n;
	while (tmp >= (unsigned int)base_len)
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

char	*ft_hex_prepare(unsigned int n, int upper)
{
	if (upper)
		return (ft_utoa_base(n, "0123456789ABCDEF"));
	else
		return (ft_utoa_base(n, "0123456789abcdef"));
}

int	ft_print_prefix(t_format *fmt, unsigned int n, int upper)
{
	if (fmt->hash && n != 0)
	{
		if (upper)
			return (write(1, "0X", 2));
		else
			return (write(1, "0x", 2));
	}
	return (0);
}

int	ft_hex_padding(t_format *fmt, int total_len)
{
	int	padding;

	padding = fmt->width - total_len;
	if (padding <= 0)
		return (0);
	if (!fmt->minus && (!fmt->zero || fmt->dot))
		return (ft_print_padding(' ', padding));
	else if (!fmt->minus && fmt->zero && !fmt->dot)
		return (ft_print_padding('0', padding));
	return (0);
}

int	ft_prefix_len(t_format *fmt, unsigned int n)
{
	if (fmt->hash && n != 0)
		return (2);
	return (0);
}
