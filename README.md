*This project was created as part of the 42 curriculum by tmege, chgomez.*

# minishell

## Description

**minishell** is a simplified Unix shell implementation written in C, inspired by Bash.
The goal is to reproduce the core behaviour of a real shell: reading user input,
parsing it into commands, expanding variables, and executing processes — while
respecting POSIX conventions and handling edge cases correctly.

The project covers the full pipeline from raw text to process execution:

```
input → lexer → syntax check → expander → parser → executor
```

Key topics explored: process creation with `fork`/`execve`, inter-process
communication with `pipe`, file-descriptor management, signal handling, and
environment variable manipulation.

### Features

#### Commands

| Syntax                  | Description                      | Example                        |
|-------------------------|----------------------------------|--------------------------------|
| `command args...`       | Execute a command with arguments | `echo hello world`             |
| `cmd1 \| cmd2`          | Pipe output of cmd1 into cmd2    | `ls \| grep foo`               |
| `cmd1 \| cmd2 \| cmd3`  | Chain multiple pipes             | `cat file \| grep x \| wc -l` |

#### Redirections

| Operator | Description                          | Example              |
|----------|--------------------------------------|----------------------|
| `<`      | Redirect input from file             | `cat < file.txt`     |
| `>`      | Redirect output to file (overwrite)  | `echo hi > out.txt`  |
| `>>`     | Redirect output to file (append)     | `echo hi >> out.txt` |
| `<<`     | Heredoc (read until delimiter)       | `cat << EOF`         |

Heredocs expand `$VAR` unless the delimiter is quoted (`<< 'EOF'`).

#### Quoting

| Syntax  | Description                                  | Example                            |
|---------|----------------------------------------------|------------------------------------|
| `'...'` | Single quotes — literal string, no expansion | `echo '$HOME'` → `$HOME`           |
| `"..."` | Double quotes — allows `$VAR` expansion      | `echo "$HOME"` → `/home/user`      |
| Mixed   | Quotes can appear mid-word                   | `ec"ho" hello` runs `echo`         |

#### Variable expansion

| Syntax      | Description                                    | Example      |
|-------------|------------------------------------------------|--------------|
| `$VAR`      | Expands to the value of the environment var    | `echo $HOME` |
| `$?`        | Expands to the last command's exit status      | `echo $?`    |
| `$` (alone) | Stays as a literal `$`                         | `echo $`     |

Unquoted `$NONEXISTENT` is removed (empty-token suppression).

#### Signals

| Signal   | Interactive    | During execution                  |
|----------|----------------|-----------------------------------|
| `Ctrl+C` | New prompt     | Interrupt child + newline         |
| `Ctrl+\` | Ignored        | Quit child + "Quit (core dumped)" |
| `Ctrl+D` | Exit the shell | EOF on stdin                      |

#### Builtins

| Command  | Description                          |
|----------|--------------------------------------|
| `echo`   | Print arguments (with `-n` option)   |
| `cd`     | Change directory (HOME, OLDPWD, `-`) |
| `pwd`    | Print working directory              |
| `export` | Set/display environment variables    |
| `unset`  | Unset environment variables          |
| `env`    | Print environment                    |
| `exit`   | Exit the shell                       |

#### Error handling

| Case                      | Message                                     | Exit code |
|---------------------------|---------------------------------------------|-----------|
| Command not found         | `minishell: cmd: command not found`         | 127       |
| No such file or directory | `minishell: ./bad: No such file or dir`     | 127       |
| Is a directory            | `minishell: ./src: Is a directory`          | 126       |
| Permission denied         | `minishell: ./file: Permission denied`      | 126       |
| Syntax error              | `minishell: syntax error near ...`          | 2         |

#### Syntax errors detected

- Pipe at the start or end of input: `| ls`, `ls |`
- Consecutive pipes: `ls || grep`
- Redirection without a target: `ls >`, `cat <<`
- Redirection followed by an operator: `ls > | file`
- Unclosed quotes: `echo "hello`, `echo 'hello`

### Architecture

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
├── expander_tokens.c   # token-level expansion helpers
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
├── heredoc_collect.c   # heredoc input collection
├── free_utils.c        # free_tokens(), free_cmds(), free_redirs()
└── builtins/
    ├── builtin_echo.c
    ├── builtin_cd.c
    ├── builtin_pwd.c
    ├── builtin_export.c
    ├── builtin_export_utils.c
    ├── builtin_unset.c
    ├── builtin_env.c
    └── builtin_exit.c
```

---

## Instructions

### Dependencies

- `cc` (or any C99-compatible compiler)
- GNU `readline` library

On Debian/Ubuntu:
```bash
sudo apt-get install libreadline-dev
```

### Compilation

```bash
make        # build the binary
make clean  # remove object files
make fclean # remove object files and binary
make re     # full rebuild
```

### Execution

```bash
./minishell
```

The shell starts an interactive prompt. Type any command and press Enter.
Use `exit` or `Ctrl+D` to quit.

### Testing

```bash
bash test_edge_cases.sh
```

Runs automated tests covering commands, pipes, redirections, quoting,
variable expansion, builtins, signals, and edge cases.

---

## Resources

### Official documentation

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — authoritative reference for shell behaviour, quoting rules, expansion order, and builtins.
- [POSIX Shell & Utilities specification](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) — formal standard that defines portable shell semantics.
- [GNU Readline library](https://tiswww.case.edu/php/chet/readline/rltop.html) — documentation for the readline API used for interactive input and history.
- [`man 2 fork`](https://man7.org/linux/man-pages/man2/fork.2.html), [`man 2 execve`](https://man7.org/linux/man-pages/man2/execve.2.html), [`man 2 pipe`](https://man7.org/linux/man-pages/man2/pipe.2.html), [`man 2 waitpid`](https://man7.org/linux/man-pages/man2/waitpid.2.html) — Linux system calls at the core of the execution engine.
- [`man 2 sigaction`](https://man7.org/linux/man-pages/man2/sigaction.2.html) — signal handling used for `SIGINT` and `SIGQUIT`.

### Articles & tutorials

- [Writing a Unix Shell (series)](https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/) — step-by-step walkthrough of building a shell from scratch in C.
- [Let's Build a Shell](https://brennan.io/2015/01/16/write-a-shell-in-c/) — concise tutorial covering fork, exec, and pipes.
- [The Linux Programming Interface](https://man7.org/tlpi/) (Kerrisk, 2010) — comprehensive reference for system programming on Linux.

### AI usage

Claude (Anthropic) was used as an assistant during development of this project in the following ways:

- **Discovery of unknown functions**: Identifying which C standard library and
  POSIX system call functions were available and permitted for the project
  (e.g. `readline`, `dup2`, `sigaction`, `waitpid`), and understanding what
  each one does, its signature, and when to use it.
- **Debugging**: Analysing memory leaks, signal-handling race conditions, and
  incorrect file-descriptor propagation across forked processes.
- **Code review**: Verifying that quoting and expansion logic matched Bash
  behaviour for edge cases (empty variables, nested quotes, `$?` inside heredocs).
- **README generation**: Formatting and improving the readability of the final README.md.

All logic, design decisions, and final code were written and reviewed by the
project authors. AI was used strictly as a reference, teacher and review tool, not as a
code generator for the implementation.

---

## Authors

- **tmege** & **chgomez** 
