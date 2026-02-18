# Minishell — Data Flow

## Overview

```
main() → init_shell() → shell_loop() → cleanup_shell() → exit
```

## 1. Initialization (`main.c` → `init_shell.c`)

```
main(argc, argv, envp)
  │
  ├─ init_shell(&data, envp)
  │    ├─ data.envp = dup_envp(envp)    // deep copy of environment
  │    ├─ data.exit_status = 0
  │    ├─ data.running = 1
  │    ├─ data.in_pipe = 0
  │    └─ data.cmds = NULL
  │
  ├─ shell_loop(&data)                  // main loop (see §2)
  │
  ├─ cleanup_shell(&data)
  │    ├─ free_envp(data.envp)
  │    └─ rl_clear_history()
  │
  └─ return (data.exit_status)
```

## 2. Main Loop (`shell_loop.c`)

```
shell_loop(data)
  │
  └─ while (data->running)
       │
       ├─ setup_signals()              // SIGINT → new prompt, SIGQUIT → ignore
       ├─ build_prompt(data)           // "$USER@minishell> "
       ├─ readline(prompt)             // blocks, reads user input
       │
       ├─ if (g_status == 130)         // SIGINT was caught
       │    └─ data->exit_status = 130
       │
       ├─ if (line == NULL)            // Ctrl+D (EOF)
       │    └─ print "exit", stop loop
       │
       └─ handle_line(data, line)
            ├─ add_history(line)       // if non-empty
            ├─ process_line(data, line)
            └─ free(line)
```

## 3. Processing Pipeline (`shell_loop.c` → `process_line`)

This is the core: a single user input goes through 5 stages.

```
process_line(data, line)
  │
  │  ┌─────────────────────────────────────────────────────────┐
  │  │  STAGE 1 — LEXER (tokenize)                            │
  │  │                                                         │
  │  │  "echo $HOME | cat > out"                               │
  │  │       ↓                                                 │
  │  │  [echo][word] → [$HOME][word] → [|][pipe] →            │
  │  │  [cat][word] → [>][redir_out] → [out][word]            │
  │  │                                                         │
  │  │  Files: lexer.c, lexer_utils.c, lexer_quotes.c         │
  │  └─────────────────────────────────────────────────────────┘
  │       ↓  t_token linked list
  │
  │  ┌─────────────────────────────────────────────────────────┐
  │  │  STAGE 2 — SYNTAX CHECK                                │
  │  │                                                         │
  │  │  Validates token stream:                                │
  │  │  - No leading/trailing pipe                             │
  │  │  - Redir must be followed by a word                     │
  │  │  - No consecutive pipes                                 │
  │  │                                                         │
  │  │  Returns 0 → error (exit_status = 2)                   │
  │  │  File: syntax_check.c                                  │
  │  └─────────────────────────────────────────────────────────┘
  │       ↓  same t_token list (validated)
  │
  │  ┌─────────────────────────────────────────────────────────┐
  │  │  STAGE 3 — EXPANDER                                    │
  │  │                                                         │
  │  │  [$HOME][word] → [/home/pab7o][word]                   │
  │  │                                                         │
  │  │  - $VAR → value from envp                               │
  │  │  - $? → data->exit_status                               │
  │  │  - Single quotes: no expansion                          │
  │  │  - Double quotes: expand $VAR only                      │
  │  │  - Unquoted empty result → token removed                │
  │  │                                                         │
  │  │  Files: expander.c, expander_utils.c, expander_tokens.c│
  │  └─────────────────────────────────────────────────────────┘
  │       ↓  expanded t_token list
  │
  │  ┌─────────────────────────────────────────────────────────┐
  │  │  STAGE 4 — PARSER                                      │
  │  │                                                         │
  │  │  Tokens → t_cmd linked list (split on pipes)            │
  │  │                                                         │
  │  │  [echo][/home/pab7o] | [cat][>][out]                   │
  │  │       ↓                    ↓                            │
  │  │  cmd1:                 cmd2:                            │
  │  │    args=["echo",         args=["cat"]                   │
  │  │          "/home/pab7o"]  redirs=[redir_out,"out"]       │
  │  │    redirs=NULL           next=NULL                      │
  │  │    next=cmd2                                            │
  │  │                                                         │
  │  │  Files: parser.c, parser_utils.c                        │
  │  └─────────────────────────────────────────────────────────┘
  │       ↓  t_cmd linked list
  │
  │  ┌─────────────────────────────────────────────────────────┐
  │  │  STAGE 5 — EXECUTOR                                    │
  │  │                                                         │
  │  │  See §4 and §5 below                                   │
  │  │                                                         │
  │  │  Files: executor.c, executor_cmd.c, executor_utils.c,  │
  │  │         executor_pipe.c, redirections.c,                │
  │  │         heredoc.c, heredoc_collect.c                    │
  │  └─────────────────────────────────────────────────────────┘
  │
  ├─ free_tokens(tokens)
  ├─ free_cmds(data->cmds)
  └─ data->cmds = NULL
```

## 4. Execution — Single Command (`executor.c`)

```
execute_cmds(data)
  │
  ├─ collect_heredocs(cmds, data)     // read all heredocs BEFORE execution
  │    └─ for each redir_heredoc:
  │         handle_heredoc(delim, quoted, data)
  │           ├─ pipe() → pipefd
  │           ├─ readline("> ") until delim or EOF
  │           ├─ if !quoted: expand_value(line) for $VAR
  │           └─ return pipefd[0] (stored in redir->fd)
  │
  ├─ if 1 command → exec_single(cmd, data)
  │    │
  │    ├─ if no args (redirect-only) or builtin:
  │    │    exec_redir_cmd(cmd, data)
  │    │      ├─ save STDIN/STDOUT (dup)
  │    │      ├─ apply_redirections(cmd)
  │    │      ├─ if builtin → exec_builtin(cmd, data)
  │    │      └─ restore STDIN/STDOUT (dup2 + close)
  │    │
  │    └─ if external command:
  │         exec_external(cmd, data, path)
  │           ├─ setup_signals_exec()       // parent ignores SIGINT/SIGQUIT
  │           ├─ fork()
  │           │    └─ child:
  │           │         ├─ setup_signals_child()
  │           │         ├─ apply_redirections(cmd)
  │           │         └─ execve(path, args, envp)
  │           ├─ waitpid(pid)
  │           └─ handle_child_status(status)
  │                ├─ WIFSIGNALED → 128 + signal
  │                └─ WIFEXITED → WEXITSTATUS
  │
  └─ if multiple commands → execute_pipeline(data) [see §5]
```

## 5. Execution — Pipeline (`executor_pipe.c`)

```
execute_pipeline(data)    // e.g., "ls | grep foo | wc"
  │
  ├─ create_pipes(n-1)   // n-1 pipes for n commands
  │    [pipe0]  [pipe1]
  │    r0  w0   r1  w1
  │
  ├─ setup_signals_exec()
  │
  ├─ for each command i (fork):
  │    pipe_child(cmd, data, pipes, [i, n])
  │      ├─ data->in_pipe = 1
  │      ├─ setup_signals_child()
  │      ├─ if i > 0:     dup2(pipes[i-1][read], STDIN)
  │      ├─ if i < n-1:   dup2(pipes[i][write], STDOUT)
  │      ├─ close_pipes(all)
  │      ├─ apply_redirections(cmd)
  │      ├─ if builtin → exit(exec_builtin)
  │      └─ if external → pipe_exec_cmd → execve
  │
  ├─ close_pipes(all)     // parent closes all pipe fds
  │
  └─ wait_children(pids, n)
       └─ last child's status → data->exit_status
```

```
Data flow through pipes:

  cmd0         cmd1         cmd2
 [ls]    →   [grep foo] → [wc]
   │              │            │
   stdout→w0  r0→stdin         │
              stdout→w1  r1→stdin
```

## 6. Redirections (`redirections.c`)

```
apply_redirections(cmd)
  │
  └─ for each redir in cmd->redirs:
       │
       ├─ redir_in:      fd = open(file, O_RDONLY)
       ├─ redir_out:     fd = open(file, O_WRONLY|O_CREAT|O_TRUNC)
       ├─ redir_append:  fd = open(file, O_WRONLY|O_CREAT|O_APPEND)
       ├─ redir_heredoc: fd = redir->fd (pre-filled by collect_heredocs)
       │
       ├─ dup2(fd, STDIN or STDOUT)
       └─ close(fd) if fd != target
```

## 7. Key Data Structures

```
t_data (global shell state)
  ├─ envp       char**     environment variables ("KEY=VALUE")
  ├─ exit_status int       last command's exit code ($?)
  ├─ running     int       0 = exit loop
  ├─ in_pipe     int       1 = inside pipeline child
  └─ cmds        t_cmd*    current command list

t_token (lexer output)
  ├─ value       char*     token text
  ├─ type        enum      word / pipe / redir_in / redir_out / heredoc / append
  ├─ quoted      int       1 if any part was quoted
  └─ next        t_token*

t_cmd (parser output)
  ├─ args        char**    NULL-terminated argument array
  ├─ redirs      t_redir*  linked list of redirections
  └─ next        t_cmd*    next command in pipeline

t_redir
  ├─ type        enum      in / out / heredoc / append
  ├─ file        char*     filename or heredoc delimiter
  ├─ fd          int       pre-opened fd (heredoc only)
  ├─ quoted      int       1 if delimiter was quoted (heredoc)
  └─ next        t_redir*
```

## 8. Signal Handling

```
CONTEXT              SIGINT (Ctrl+C)           SIGQUIT (Ctrl+\)
─────────────────────────────────────────────────────────────────
Interactive prompt   new line + new prompt      ignored
During child exec    ignored (parent waits)     ignored (parent waits)
Child process        default (kill)             default (core dump)
Heredoc input        close stdin, g_status=130  ignored
```

## 9. Error Codes

```
CODE    MEANING
0       success
1       general error (bad redirect, builtin failure)
2       syntax error / misuse (unclosed quote, bad pipe, numeric arg)
126     permission denied / is a directory
127     command not found
128+N   killed by signal N (130 = SIGINT, 131 = SIGQUIT)
```
