# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/30 12:08:41 by tmege             #+#    #+#              #
#    Updated: 2025/05/23 11:52:11 by tmege            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Configuration de base
NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

# Structure des dossiers
SRC_DIR = srcs
PRINTF_DIR = $(SRC_DIR)/ft_printf
INC_DIR = includes
OBJ_DIR = objs

# Sources principales libft (dans srcs/)
LIBFT_SRCS = \
	$(SRC_DIR)/ft_isalpha.c \
	$(SRC_DIR)/ft_isdigit.c \
	$(SRC_DIR)/ft_isalnum.c \
	$(SRC_DIR)/ft_isascii.c \
	$(SRC_DIR)/ft_isprint.c \
	$(SRC_DIR)/ft_strlen.c \
	$(SRC_DIR)/ft_memset.c \
	$(SRC_DIR)/ft_bzero.c \
	$(SRC_DIR)/ft_memcpy.c \
	$(SRC_DIR)/ft_memmove.c \
	$(SRC_DIR)/ft_strlcpy.c \
	$(SRC_DIR)/ft_strlcat.c \
	$(SRC_DIR)/ft_calloc.c \
	$(SRC_DIR)/ft_strdup.c \
	$(SRC_DIR)/ft_toupper.c \
	$(SRC_DIR)/ft_tolower.c \
	$(SRC_DIR)/ft_strchr.c \
	$(SRC_DIR)/ft_strrchr.c \
	$(SRC_DIR)/ft_strncmp.c \
	$(SRC_DIR)/ft_memchr.c \
	$(SRC_DIR)/ft_memcmp.c \
	$(SRC_DIR)/ft_strnstr.c \
	$(SRC_DIR)/ft_atoi.c \
	$(SRC_DIR)/ft_substr.c \
	$(SRC_DIR)/ft_strjoin.c \
	$(SRC_DIR)/ft_strtrim.c \
	$(SRC_DIR)/ft_split.c \
	$(SRC_DIR)/ft_itoa.c \
	$(SRC_DIR)/ft_strmapi.c \
	$(SRC_DIR)/ft_striteri.c \
	$(SRC_DIR)/ft_putchar_fd.c \
	$(SRC_DIR)/ft_putstr_fd.c \
	$(SRC_DIR)/ft_putendl_fd.c \
	$(SRC_DIR)/ft_putnbr_fd.c

# Sources bonus (dans srcs/)
BONUS_SRCS = \
	$(SRC_DIR)/ft_lstnew_bonus.c \
	$(SRC_DIR)/ft_lstadd_front_bonus.c \
	$(SRC_DIR)/ft_lstsize_bonus.c \
	$(SRC_DIR)/ft_lstlast_bonus.c \
	$(SRC_DIR)/ft_lstadd_back_bonus.c \
	$(SRC_DIR)/ft_lstdelone_bonus.c \
	$(SRC_DIR)/ft_lstclear_bonus.c \
	$(SRC_DIR)/ft_lstiter_bonus.c \
	$(SRC_DIR)/ft_lstmap_bonus.c

# Sources printf (dans srcs/ft_printf/)
PRINTF_SRCS = \
	$(PRINTF_DIR)/ft_printf.c \
	$(PRINTF_DIR)/ft_init_format.c \
	$(PRINTF_DIR)/ft_dispatch_convert.c \
	$(PRINTF_DIR)/ft_parser.c \
	$(PRINTF_DIR)/ft_print_char.c \
	$(PRINTF_DIR)/ft_print_string.c \
	$(PRINTF_DIR)/ft_print_number.c \
	$(PRINTF_DIR)/ft_print_number_utils.c \
	$(PRINTF_DIR)/ft_print_unsigned.c \
	$(PRINTF_DIR)/ft_print_hex.c \
	$(PRINTF_DIR)/ft_print_hex_utils.c \
	$(PRINTF_DIR)/ft_print_pointer.c

# Fichiers objets
LIBFT_OBJS = $(LIBFT_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
PRINTF_OBJS = $(PRINTF_SRCS:$(PRINTF_DIR)/%.c=$(OBJ_DIR)/printf/%.o)

# Règles principales
all: $(NAME)

$(NAME): $(LIBFT_OBJS) $(PRINTF_OBJS)
	@$(AR) $@ $^
	@echo "✅ Libft compilée avec succès"

bonus: $(LIBFT_OBJS) $(BONUS_OBJS) $(PRINTF_OBJS)
	@$(AR) $(NAME) $^
	@echo "✨ Bonus compilés avec succès"

# Règles de compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile includes/*.h | $(OBJ_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR)/printf/%.o: $(PRINTF_DIR)/%.c srcs/ft_printf/Makefile | $(OBJ_DIR) 
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@


clean:
	@rm -rf $(OBJ_DIR)
	@echo "🧹 Fichiers objets nettoyés"

fclean: clean
	@rm -f $(NAME)
	@echo "🚀 Bibliothèque nettoyée"

re: fclean all

.PHONY: all bonus clean fclean re
