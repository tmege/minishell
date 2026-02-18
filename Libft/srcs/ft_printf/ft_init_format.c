/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:48:15 by tmege             #+#    #+#             */
/*   Updated: 2025/05/28 16:52:49 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_init_format(t_format *fmt)
{
	fmt->minus = 0;
	fmt->zero = 0;
	fmt->plus = 0;
	fmt->space = 0;
	fmt->hash = 0;
	fmt->width = 0;
	fmt->dot = 0;
	fmt->precision = -1;
	fmt->type = 0;
}
