# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 16:44:40 by tmege             #+#    #+#              #
#    Updated: 2025/05/27 16:49:27 by tmege            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nouveau Makefile intégré dans libft/srcs/printf/Makefile

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I../../includes -I.

# Sources principales (sans bonus)
SRCS = ft_printf.c \
       ft_init_format.c \
       ft_dispatch_convert.c \
       ft_parser.c \
       ft_print_char.c \
       ft_print_string.c \
       ft_print_number.c \
       ft_print_number_utils.c \
       ft_print_unsigned.c \
       ft_print_hex.c \
       ft_print_hex_utils.c \
       ft_print_pointer.c

OBJS = $(SRCS:%.c=objs/%.o)

# Règles principales
all: $(OBJS)

objs/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf objs

fclean: clean

re: fclean all

.PHONY: all clean fclean re

