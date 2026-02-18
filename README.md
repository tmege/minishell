# minishell

A simplified shell implementation in C, built as part of the 42 curriculum.

## Status

| Phase   | Description       | Status |
|---------|-------------------|--------|
| Phase 1 | Shell foundation  | Done   |
| Phase 2 | Parsing pipeline  | Done   |
| Phase 3 | Execution engine  | Done   |

## Supported features

### Commands

| Syntax                  | Description                      | Example                          |
|-------------------------|----------------------------------|----------------------------------|
| `command args...`       | Execute a command with arguments | `echo hello world`               |
| `cmd1 \| cmd2`         | Pipe output of cmd1 into cmd2   | `ls \| grep foo`                 |
| `cmd1 \| cmd2 \| cmd3` | Chain multiple pipes             | `cat file \| grep x \| wc -l`   |

### Redirections

| Operator | Description                          | Example              |
|----------|--------------------------------------|----------------------|
| `<`      | Redirect input from file             | `cat < file.txt`     |
| `>`      | Redirect output to file (overwrite)  | `echo hi > out.txt`  |
| `>>`     | Redirect output to file (append)     | `echo hi >> out.txt` |
| `<<`     | Heredoc (read input until delimiter) | `cat << EOF`         |

Heredocs expand `$VAR` unless the delimiter is quoted (`<< 'EOF'`).

### Quoting

| Syntax  | Description                                  | Example                                  |
|---------|----------------------------------------------|------------------------------------------|
| `'...'` | Single quotes — literal string, no expansion | `echo '$HOME'` prints `$HOME`            |
| `"..."` | Double quotes — allows `$VAR` expansion      | `echo "$HOME"` prints `/home/user`       |
| Mixed   | Quotes can appear mid-word                   | `ec"ho" hello` runs `echo`               |

### Variable expansion

| Syntax       | Description                                      | Example      |
|--------------|--------------------------------------------------|--------------|
| `$VAR`       | Expands to the value of environment variable     | `echo $HOME` |
| `$?`         | Expands to the exit status of the last command   | `echo $?`    |
| `$` (alone)  | Stays as a literal `$`                           | `echo $`     |

Unquoted `$NONEXISTENT` is removed (empty token suppression).

### Signals

| Signal   | Interactive        | During execution                    |
|----------|--------------------|-------------------------------------|
| `Ctrl+C` | New prompt         | Interrupt child + newline           |
| `Ctrl+\` | Ignored            | Quit child + "Quit (core dumped)"   |
| `Ctrl+D` | Exit the shell     | EOF on stdin                        |

### Builtins

| Command  | Description                          |
|----------|--------------------------------------|
| `echo`   | Print arguments (with `-n` option)   |
| `cd`     | Change directory (HOME, OLDPWD, `-`) |
| `pwd`    | Print working directory              |
| `export` | Set/display environment variables    |
| `unset`  | Unset environment variables          |
| `env`    | Print environment                    |
| `exit`   | Exit the shell                       |

### Error handling

| Case                      | Behavior                                   | Exit code |
|---------------------------|--------------------------------------------|-----------|
| Command not found         | `minishell: cmd: command not found`        | 127       |
| No such file or directory | `minishell: ./bad: No such file or dir`    | 127       |
| Is a directory            | `minishell: ./src: Is a directory`         | 126       |
| Permission denied         | `minishell: ./file: Permission denied`     | 126       |
| Syntax error              | `minishell: syntax error near ...`         | 2         |

### Syntax errors

The parser detects and reports the following errors:

- Pipe at the start or end of input: `| ls`, `ls |`
- Consecutive pipes: `ls || grep`
- Redirection without a target: `ls >`, `cat <<`
- Redirection followed by an operator: `ls > | file`
- Unclosed quotes: `echo "hello`, `echo 'hello`

## Build

```bash
make        # build
make clean  # remove objects
make fclean # remove objects + binary
make re     # full rebuild
```

## Usage

```bash
./minishell
```

## Testing

```bash
bash test_edge_cases.sh
```

Runs automated tests covering commands, pipes, redirections, quoting, expansion, builtins, signals and edge cases.

## Phase 1 — Foundation

- Interactive prompt with `readline` and history
- Signal handling (`SIGINT` / `SIGQUIT`)
- Environment copy (`envp` duplication)
- Libft + ft_printf linked

## Phase 2 — Parsing

Full parsing pipeline: `input` -> `tokens` -> `syntax check` -> `expansion` -> `command list`

### Lexer
- Tokenizes input into words, pipes (`|`), and redirections (`<`, `>`, `<<`, `>>`)
- Handles single and double quotes (including nested)
- Detects unclosed quotes

### Syntax checker
- Validates token stream (no leading/trailing pipes, redirections must have a target)

### Expander
- Expands `$VAR` and `$?` in unquoted and double-quoted contexts
- Single-quoted strings are preserved literally
- Removes empty tokens from unquoted variable expansion

### Parser
- Converts token list into a linked list of `t_cmd` structures
- Each command holds `args` (NULL-terminated array) and `redirs` (linked list)
- Commands are split on pipe tokens

## Phase 3 — Execution

### Single commands
- Builtins run in-place with saved/restored fd
- External commands fork + execve with PATH resolution

### Pipelines
- N-1 pipes for N commands, all children forked in parallel
- Last command exit status is returned

### Heredoc
- Collected before execution (Ctrl+C cancels)
- Variable expansion in heredoc body (unless delimiter is quoted)

## Architecture

```
src/
├── main.c              # entry point
├── shell_loop.c        # readline loop + process_line orchestration
├── init_shell.c        # environment setup
├── signals.c           # SIGINT / SIGQUIT / exec signal handlers
├── lexer.c             # tokenize(), read_word(), read_operator()
├── lexer_utils.c       # token_new(), token_add_back(), is_metachar()
├── lexer_quotes.c      # skip_quotes()
├── syntax_check.c      # check_syntax()
├── expander.c          # expand_tokens(), expand_value()
├── expander_utils.c    # extract_var_name(), get_env_value()
├── parser.c            # parse_tokens(), parse_one_cmd()
├── parser_utils.c      # cmd_new(), redir_new(), list_to_args()
├── env_utils.c         # set_env_value(), remove_env_value()
├── env_utils2.c        # add_env_no_value()
├── executor.c          # execute_cmds(), exec_single(), exec_external()
├── executor_cmd.c      # exec_builtin(), cmd_path_error(), pipe_exec_cmd()
├── executor_utils.c    # find_cmd_path(), is_builtin(), count_cmds()
├── executor_pipe.c     # execute_pipeline(), pipe_child(), wait_children()
├── redirections.c      # apply_redirections()
├── heredoc.c           # collect_heredocs(), handle_heredoc()
├── free_utils.c        # free_tokens(), free_cmds(), free_redirs()
└── builtins/
    ├── builtin_echo.c
    ├── builtin_cd.c
    ├── builtin_pwd.c
    ├── builtin_export.c
    ├── builtin_unset.c
    ├── builtin_env.c
    └── builtin_exit.c
```

## Authors

- **tmege && chgomez** — 42 Barcelona
