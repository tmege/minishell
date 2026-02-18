/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dispatch_convert.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:55:51 by tmege             #+#    #+#             */
/*   Updated: 2025/05/28 16:53:58 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_dispatch_conversion(t_format *fmt, va_list args)
{
	if (fmt->type == 'c')
		return (ft_print_char(fmt, va_arg(args, int)));
	else if (fmt->type == 's')
		return (ft_print_string(fmt, va_arg(args, char *)));
	else if (fmt->type == 'd' || fmt->type == 'i')
		return (ft_print_number(fmt, va_arg(args, int)));
	else if (fmt->type == 'u')
		return (ft_print_unsigned(fmt, va_arg(args, unsigned int)));
	else if (fmt->type == 'x')
		return (ft_print_hex(fmt, va_arg(args, unsigned int), 0));
	else if (fmt->type == 'X')
		return (ft_print_hex(fmt, va_arg(args, unsigned int), 1));
	else if (fmt->type == 'p')
		return (ft_print_pointer(fmt, va_arg(args, void *)));
	else if (fmt->type == '%')
		return (ft_print_char(fmt, '%'));
	return (0);
}
