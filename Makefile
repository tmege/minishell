NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = main.c \
       shell_loop.c \
       init_shell.c \
       signals.c \
       free_utils.c \
       lexer.c \
       lexer_utils.c \
       lexer_quotes.c \
       syntax_check.c \
       expander.c \
       expander_utils.c \
       parser.c \
       parser_utils.c \
       env_utils.c \
       env_utils2.c \
       executor.c \
       executor_cmd.c \
       executor_utils.c \
       executor_pipe.c \
       redirections.c \
       heredoc.c \
       heredoc_collect.c \
       expander_tokens.c

BUILTIN_SRCS = builtins/builtin_echo.c \
               builtins/builtin_cd.c \
               builtins/builtin_pwd.c \
               builtins/builtin_export.c \
               builtins/builtin_export_utils.c \
               builtins/builtin_unset.c \
               builtins/builtin_env.c \
               builtins/builtin_exit.c

ALL_SRCS = $(SRCS) $(BUILTIN_SRCS)
OBJS = $(ALL_SRCS:%.c=$(OBJ_DIR)/%.o)
HEADERS = $(INC_DIR)/minishell.h

all: $(NAME)

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
