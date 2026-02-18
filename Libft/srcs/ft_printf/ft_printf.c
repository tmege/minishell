/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:54:33 by tmege             #+#    #+#             */
/*   Updated: 2025/05/28 16:58:59 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_handle_conversion(const char *format, int *i, va_list args)
{
	t_format	fmt;
	int			len;

	ft_init_format(&fmt);
	if (ft_parser(format, i, &fmt, args) == -1)
		return (-1);
	len = ft_dispatch_conversion(&fmt, args);
	return (len);
}

static int	ft_process_conversion(const char *format, int *i, va_list args)
{
	int	ret;

	ret = ft_handle_conversion(format, i, args);
	if (ret == -1)
		return (-1);
	return (ret);
}

static int	ft_printf_loop(const char *format, va_list args)
{
	int	i;
	int	len;
	int	ret;

	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			ret = ft_process_conversion(format, &i, args);
			if (ret == -1)
				return (-1);
			len += ret;
		}
		else
			len += write(1, &format[i++], 1);
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	va_start(args, format);
	len = ft_printf_loop(format, args);
	va_end(args);
	return (len);
}
/*
#include <stdio.h>
#include <assert.h>

void	test_ft_printf_length()
{
	
	char	*str1 = "Hello";
	char	*str2 = "this will pass";
	char	*str3 = "please make it work";

	int	original;
	int	implementation;
	// %i conversion
	original = printf("%i\n", -541155487);
	implementation = ft_printf("%i\n", -541155487);
	assert(original == implementation);
	original = printf("%i\n", -54);
	implementation = ft_printf("%i\n", -54);
	assert(original == implementation);
	original = printf("%i\n", -545);
	implementation = ft_printf("%i\n", -545);
	assert(original == implementation);
	ft_printf("\n");
	ft_printf("################################################\n");
	ft_printf("#    All tests for %%i conversion passed !      #\n");
	ft_printf("################################################\n\n");

	// %d conversion
	original = printf("%d\n", -541155487);
	implementation = ft_printf("%d\n", -541155487);
	assert(original == implementation);
	original = printf("%d\n", 278);
	implementation = ft_printf("%d\n", 278);
	assert(original == implementation);
	original = printf("%d\n", -54545);
	implementation = ft_printf("%d\n", -54545);
	assert(original == implementation);
	ft_printf("\n");
	ft_printf("################################################\n");
	ft_printf("#     All tests for %%d conversion passed !     #\n");
	ft_printf("################################################\n\n");
	// %s conversion
	original = printf("%s %s %s!!\n", str1, str2, str3);
	implementation = ft_printf("%s %s %s!!\n", str1, str2, str3);
	assert(original == implementation);
	original = printf("%s %s\n", "Hello World!", "Will this \0 work ! :/");
	implementation = printf("%s %s\n", "Hello World!", "Will this \0 work ! :/");
	assert(original == implementation);
	original = printf("%s", "");
	implementation = ft_printf("%s", "");
	assert(original == implementation);
	char	*null_str = NULL;
	original = printf("%s\n", null_str);
	implementation = ft_printf("%s\n", null_str);
	assert(original == implementation);

	ft_printf("\n");
	ft_printf("################################################\n");
	ft_printf("#      All tests for %%s conversion passed !    #\n");
	ft_printf("################################################\n\n");


	// %c conversion
	original = printf("%%%c\n", 'C');
	implementation = ft_printf("%%%c\n", 'C');
	assert(original == implementation);

	original = printf("My name is %c%c%c%c\n", 'A', 'x', 'e', 'l');
	implementation = ft_printf("My name is %c%c%c%c\n", 'A', 'x', 'e', 'l');
	assert(original == implementation);

	ft_printf("\n");
	ft_printf("################################################\n");
	ft_printf("#   All tests for %%c conversion passed !       #\n");
	ft_printf("################################################\n\n");

	//%x conversion
	original = printf("%x\n", 12345678);
	implementation = ft_printf("%x\n", 12345678);
	assert(original == implementation);

	original = printf("%x\n", 0);
	implementation = ft_printf("%x\n", 0);
	assert(original == implementation);

	original = printf("%x\n", -1);
	implementation = ft_printf("%x\n", -1);
	assert(original == implementation);

	original = printf("%x\n", 4294967295U);
	implementation = ft_printf("%x\n", 4294967295U);
	assert(original == implementation);

	ft_printf("\n");
	ft_printf("################################################\n");
	ft_printf("#   All tests for %%x conversion passed !       #\n");
	ft_printf("################################################\n\n");

	//%X conversion
	original = printf("%X\n", 78877878);
	implementation = ft_printf("%X\n", 78877878);
	assert(original == implementation);

	original = printf("%X\n", 1548);
	implementation = ft_printf("%X\n", 1548);
	assert(original == implementation);

	original = printf("%X\n", -42);
	implementation = ft_printf("%X\n", -42);
	assert(original == implementation);

	original = printf("%X\n", 4294967295U);
	implementation = ft_printf("%X\n", 4294967295U);
	assert(original == implementation);

	ft_printf("\n");
	ft_printf("################################################\n");
	ft_printf("#   All tests for %%X conversion passed !       #\n");
	ft_printf("################################################\n\n");

	// %u conversion
	
	original = printf("%u\n", 0);
	implementation = ft_printf("%u\n", 0);

	original = printf("%u\n", 12345);
	implementation = ft_printf("%u\n", 12345);
	assert(original == implementation);

	original = printf("%u\n", 4294967295U);
	implementation = ft_printf("%u\n", 4294967295U);
	assert(original == implementation);

	original = printf("%u\n", -1);
	implementation = ft_printf("%u\n", -1);
	assert(original == implementation);

	original = printf("%u\n", 987654);
	implementation = ft_printf("%u\n", 987654);
	assert(original == implementation);

	ft_printf("\n");
	ft_printf("################################################\n");
	ft_printf("#   All tests for %%u conversion passed !       #\n");
	ft_printf("################################################\n\n");

	// %p conversion
	int x = 42;
	int *ptr = &x;

	original = printf("%p\n", (void *)ptr);  
	implementation = ft_printf("%p\n", (void *)ptr);
	assert(original == implementation);

	original = printf("%p\n", NULL);  
	implementation = ft_printf("%p\n", NULL);
	assert(original == implementation);

	original = printf("%p\n", (void *)&x);
	implementation = ft_printf("%p\n", (void *)&x);
	assert(original == implementation);

	char *str = "Hello";
	original = printf("%p\n", (void *)str);
	implementation = ft_printf("%p\n", (void *)str);
	assert(original == implementation);

	int y = 100;
	original = printf("%p\n", (void *)&y);
	implementation = ft_printf("%p\n", (void *)&y);
	assert(original == implementation);

	ft_printf("\n");
	ft_printf("################################################\n");
	ft_printf("#   All tests for %%p conversion passed !       #\n");
	ft_printf("################################################\n\n");

	// combined conversion
	char c = 'C';
	char *str_test = "is such a blast !";
	int num1 = 42;
	int *p = &num1;
	unsigned int u_num = 4294967295U;
	int hex_num = 255; 

	original = printf("%c %s\n", c, str_test);
	implementation = ft_printf("%c %s\n", c, str_test);
	assert(original == implementation);

	original = printf("%p %d %i\n", (void *)ptr, -num1, num1);
	implementation = ft_printf("%p %d %i\n", (void *)p, -num1, num1);
	assert(original == implementation);

	original = printf("%u %x %X\n", u_num, hex_num, hex_num);
	implementation = ft_printf("%u %x %X\n", u_num, hex_num, hex_num);
	assert(original == implementation);

	original = printf("Print a percent sign: %%\n");
	implementation = ft_printf("Print a percent sign: %%\n");
	assert(original == implementation);

	ft_printf("\n");
	ft_printf("################################################\n");
	ft_printf("#   All tests for combined conversion passed !  #\n");
	ft_printf("################################################\n\n");

	ft_printf("-------------------------------------------------");
	ft_printf("\n");

	ft_printf("\n");
	ft_printf("#################################################\n");
	ft_printf("#           All length tests passed !           #\n");
	ft_printf("#################################################\n\n");

	// + flag
	original = printf("%+d\n", 42);
	implementation = ft_printf("%+d\n", 42);
	assert(original == implementation);

	original = printf("%+i\n", -42);
	implementation = ft_printf("%+i\n", -42);
	assert(original == implementation);

	original = printf("%+d\n", 0);
	implementation = ft_printf("%+d\n", 0);
	assert(original == implementation);

	ft_printf("\n################################################\n");
	ft_printf("#   All tests for + flag passed !             #\n");
	ft_printf("################################################\n\n");

	// ' ' (space) flag
	original = printf("% d\n", 42);
	implementation = ft_printf("% d\n", 42);
	assert(original == implementation);

	original = printf("% i\n", -42);
	implementation = ft_printf("% i\n", -42);
	assert(original == implementation);

	original = printf("% d\n", 0);
	implementation = ft_printf("% d\n", 0);
	assert(original == implementation);

	ft_printf("\n################################################\n");
	ft_printf("#   All tests for space flag passed !        #\n");
	ft_printf("################################################\n\n");

	// - flag (left justify)
	original = printf("%-10d|\n", 42);
	implementation = ft_printf("%-10d|\n", 42);
	assert(original == implementation);

	original = printf("%-s|\n", "test");
	implementation = ft_printf("%-s|\n", "test");
	assert(original == implementation);

	original = printf("%-5c|\n", 'A');
	implementation = ft_printf("%-5c|\n", 'A');
	assert(original == implementation);

	ft_printf("\n################################################\n");
	ft_printf("#   All tests for - flag passed !             #\n");
	ft_printf("################################################\n\n");

	// . (precision) flag
	original = printf("%.5d\n", 42);
	implementation = ft_printf("%.5d\n", 42);
	assert(original == implementation);

	original = printf("%.3s\n", "Hello");
	implementation = ft_printf("%.3s\n", "Hello");
	assert(original == implementation);

	original = printf("%.0d\n", 0);
	implementation = ft_printf("%.0d\n", 0);
	assert(original == implementation);

	ft_printf("\n################################################\n");
	ft_printf("#   All tests for . precision flag passed !    #\n");
	ft_printf("################################################\n\n");

	// # (alternate form) flag
	original = printf("%#x\n", 42);
	implementation = ft_printf("%#x\n", 42);
	assert(original == implementation);

	original = printf("%#X\n", 42);
	implementation = ft_printf("%#X\n", 42);
	assert(original == implementation);

	original = printf("%#X\n", 10);
	implementation = ft_printf("%#X\n", 10);
	assert(original == implementation);

	original = printf("%#x\n", 0);
	implementation = ft_printf("%#x\n", 0);
	assert(original == implementation);

	ft_printf("\n################################################\n");
	ft_printf("#   All tests for # flag passed !              #\n");
	ft_printf("################################################\n\n");

	// * (dynamic width and precision)
	original = printf("%*d\n", 10, 42);
	implementation = ft_printf("%*d\n", 10, 42);
	assert(original == implementation);

	original = printf("%.*s\n", 3, "Hello");
	implementation = ft_printf("%.*s\n", 3, "Hello");
	assert(original == implementation);

	original = printf("%*.*d\n", 8, 4, 123);
	implementation = ft_printf("%*.*d\n", 8, 4, 123);
	assert(original == implementation);

	ft_printf("\n################################################\n");
	ft_printf("#   All tests for * flag passed !              #\n");
	ft_printf("################################################\n\n");

	// 0 (zero-padding) flag
	original = printf("%010d\n", 42);
	implementation = ft_printf("%010d\n", 42);
	assert(original == implementation);

	original = printf("%08x\n", 255);
	implementation = ft_printf("%08x\n", 255);
	assert(original == implementation);


	ft_printf("\n################################################\n");
	ft_printf("#   All tests for 0 zero-padding flag passed! #\n");
	ft_printf("################################################\n\n");
	
	ft_printf("ptr1: [%p]\n", NULL);
	printf("ptr1: [%p]\n", NULL);
	ft_printf("ptr2: [%20p]\n", NULL);
	printf("ptr2: [%20p]\n", NULL);
	ft_printf("ptr3: [%-20p]\n", NULL);
	printf("ptr3: [%-20p]\n", NULL);
	ft_printf("ptr4: [%p]\n", (void *)0x12345);
	printf("ptr4: [%p]\n", (void *)0x12345);
	ft_printf("ptr5: [%20p]\n", (void *)0x12345);
	printf("ptr5: [%20p]\n", (void *)0x12345);
	ft_printf("ptr6: [%-20p]\n", (void *)0x12345);
	printf("ptr6: [%-20p]\n", (void *)0x12345);
	
	ft_printf("\n################################################\n");
	ft_printf("#   All tests for p && padding flag passed! #\n");
	ft_printf("################################################\n\n");
}

int	main(void)
{ 
	ft_printf("################################################\n");
	ft_printf("\n");
	test_ft_printf_length();
	return (0);
}
//#command line compile :  ccc -Ilibft ft_printf.c libftprintf.a libft/libft.a
*/
