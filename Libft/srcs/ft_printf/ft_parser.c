/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:24:41 by tmege             #+#    #+#             */
/*   Updated: 2025/05/28 16:55:37 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_parse_flag(const char *s, int *i, t_format *fmt)
{
	while (s[*i] && (s[*i] == '-' || s[*i] == '0' || s[*i] == '+'
			|| s[*i] == ' ' || s[*i] == '#'))
	{
		if (s[*i] == '-')
		{
			fmt->minus = 1;
			fmt->zero = 0;
		}
		else if (s[*i] == '0' && !fmt->minus)
			fmt->zero = 1;
		else if (s[*i] == '+')
			fmt->plus = 1;
		else if (s[*i] == ' ')
			fmt->space = 1;
		else if (s[*i] == '#')
			fmt->hash = 1;
		(*i)++;
	}
}

static void	ft_parse_width(const char *s, int *i, t_format *fmt, va_list args)
{
	if (s[*i] == '*')
	{
		fmt->width = va_arg(args, int);
		if (fmt->width < 0)
		{
			fmt->minus = 1;
			fmt->width *= -1;
		}
		(*i)++;
	}
	else
	{
		while (s[*i] >= '0' && s[*i] <= '9')
		{
			fmt->width = fmt->width * 10 + (s[*i] - '0');
			(*i)++;
		}
	}
}

static void	ft_parse_preci(const char *s, int *i, t_format *fmt, va_list args)
{
	if (s[*i] == '.')
	{
		fmt->dot = 1;
		(*i)++;
		if (s[*i] == '*')
		{
			fmt->precision = va_arg(args, int);
			if (fmt->precision < 0)
				fmt->dot = 0;
			(*i)++;
		}
		else
		{
			fmt->precision = 0;
			while (s[*i] >= '0' && s[*i] <= '9')
			{
				fmt->precision = fmt->precision * 10 + (s[*i] - '0');
				(*i)++;
			}
		}
	}
}

static int	ft_parse_type(const char *s, int *i, t_format *fmt)
{
	const char	*valid_types;

	valid_types = "cspdiuxX%";
	if (s[*i] && ft_strchr(valid_types, s[*i]))
	{
		fmt->type = s[*i];
		(*i)++;
		return (0);
	}
	return (-1);
}

int	ft_parser(const char *s, int *i, t_format *fmt, va_list args)
{
	ft_parse_flag(s, i, fmt);
	ft_parse_width(s, i, fmt, args);
	ft_parse_preci(s, i, fmt, args);
	if (ft_parse_type(s, i, fmt) == -1)
		return (-1);
	return (0);
}
