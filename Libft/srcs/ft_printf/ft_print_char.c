/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:59 by tmege             #+#    #+#             */
/*   Updated: 2025/05/28 16:52:29 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_char_padding(int width)
{
	int	len;
	int	padding;

	len = 0;
	padding = width - 1;
	while (padding > 0)
	{
		len += write(1, " ", 1);
		padding--;
	}
	return (len);
}

int	ft_print_char(t_format *fmt, char c)
{
	int	len;
	int	width;
	int	minus;

	len = 0;
	width = 1;
	minus = 0;
	if (fmt)
	{
		if (fmt->width > 1)
			width = fmt->width;
		minus = fmt->minus;
	}
	if (!minus)
		len += ft_print_char_padding(width);
	len += write(1, &c, 1);
	if (minus)
		len += ft_print_char_padding(width);
	return (len);
}
