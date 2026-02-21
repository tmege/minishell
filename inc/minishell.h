/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/16 14:32:18 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "../Libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_status;

/* ───── Token types ───── */

typedef enum e_token_type
{
	token_word,
	token_pipe,
	token_redir_in,
	token_redir_out,
	token_heredoc,
	token_append,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				quoted;
	struct s_token	*next;
}	t_token;

/* ───── Redirection / Command ───── */

typedef enum e_redir_type
{
	redir_in,
	redir_out,
	redir_heredoc,
	redir_append,
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	int				fd;
	int				quoted;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

/* ───── Shell data ───── */

typedef struct s_data
{
	char	**envp;
	int		exit_status;
	int		running;
	int		in_pipe;
	t_cmd	*cmds;
}	t_data;

/* ───── init / loop / cleanup ───── */

void			init_shell(t_data *data, char **envp);
void			shell_loop(t_data *data);
void			cleanup_shell(t_data *data);
void			setup_signals(void);
void			setup_signals_child(void);
void			setup_signals_exec(void);
void			process_line(t_data *data, char *line);

/* ───── lexer ───── */

t_token			*tokenize(char *line, int *err);
int				is_metachar(char c);
t_token			*token_new(char *value, t_token_type type, int quoted);
void			token_add_back(t_token **lst, t_token *new);
int				skip_quotes(char *line, int i);

/* ───── syntax ───── */

int				check_syntax(t_token *tokens);

/* ───── expander ───── */

void			expand_tokens(t_token **tokens, t_data *data);
char			*expand_value(char *str, t_data *data, int quoted);
char			*extract_var_name(char *str, int *i);
char			*get_env_value(char *name, t_data *data);
char			*append_char(char *s, char c);
char			*append_str(char *s, char *add);

/* ───── parser ───── */

t_cmd			*parse_tokens(t_token *tokens);
t_cmd			*cmd_new(void);
t_redir			*redir_new(t_redir_type type, char *file, int quoted);
void			redir_add_back(t_redir **lst, t_redir *new);
char			**list_to_args(t_list *lst);

/* ───── free utils ───── */

void			free_tokens(t_token *tokens);
void			free_cmds(t_cmd *cmds);
void			free_redirs(t_redir *redirs);
void			free_envp(char **envp);

/* ───── env utils ───── */

void			set_env_value(char *name, char *value, t_data *data);
void			remove_env_value(char *name, t_data *data);
void			add_env_entry(char *entry, t_data *data);
void			add_env_no_value(char *name, t_data *data);

/* ───── executor ───── */

void			execute_cmds(t_data *data);
void			execute_pipeline(t_data *data);
int				exec_builtin(t_cmd *cmd, t_data *data);
void			cmd_path_error(char *cmd, t_data *data);
char			*resolve_path_cmd(char *cmd, t_data *data);
void			pipe_exec_cmd(t_cmd *cmd, t_data *data);
char			*find_cmd_path(char *cmd, char **envp);
int				is_builtin(char *cmd);
int				count_cmds(t_cmd *cmds);

/* ───── redirections / heredoc ───── */

int				apply_redirections(t_cmd *cmd);
int				handle_heredoc(char *delim, int quoted, t_data *data);
int				collect_heredocs(t_cmd *cmds, t_data *data);

/* ───── export utils ───── */

char			**copy_sort_env(char **envp, int count);

/* ───── builtins ───── */

int				builtin_echo(char **args);
int				builtin_cd(char **args, t_data *data);
int				builtin_pwd(void);
int				builtin_export(char **args, t_data *data);
int				builtin_unset(char **args, t_data *data);
int				builtin_env(t_data *data);
int				builtin_exit(char **args, t_data *data);

#endif
