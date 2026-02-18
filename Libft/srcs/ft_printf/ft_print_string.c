/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:21:36 by tmege             #+#    #+#             */
/*   Updated: 2025/05/28 16:53:38 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_string(t_format *fmt, char *str)
{
	int	len;
	int	strlen;
	int	space;

	len = 0;
	if (!str)
		str = "(null)";
	strlen = ft_strlen(str);
	if (fmt->dot && fmt->precision >= 0 && fmt->precision < strlen)
		strlen = fmt->precision;
	space = 0;
	if (fmt->width > strlen)
		space = fmt->width - strlen;
	if (!fmt->minus)
	{
		while (space-- > 0)
			len += write(1, " ", 1);
	}
	len += write(1, str, strlen);
	if (fmt->minus)
	{
		while (++space < fmt->width - strlen)
			len += write(1, " ", 1);
	}
	return (len);
}
