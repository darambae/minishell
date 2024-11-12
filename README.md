
# minishell

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Usage](#usage)
- [Important Functions](#important-functions)
- [Shell Operation](#shell-operation)
- [Signal Handling](#signal-handling)
- [Error Handling](#error-handling)
- [Supported Built-in Commands](#supported-built-in-commands)

---

## Introduction

**minishell** is an Ecole 42 project aimed at building a simplified Unix shell from scratch. This shell executes commands by interacting with the operating system, parsing input, and supporting common built-in commands. Through **minishell**, students gain hands-on experience with process management, file descriptors, signals, and the shell environment.

---

## Features

- **Command Execution**: Executes system commands, handling input/output redirection and pipes.
- **Built-in Commands**: Implements essential built-in shell commands such as `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- **Environment Management**: Maintains and modifies environment variables used by the shell.
- **Signal Handling**: Manages signals like `SIGINT` (Ctrl+C) and `SIGQUIT` (Ctrl+\) for a smooth user experience.
- **Error Management**: Provides descriptive error messages for unsupported or invalid commands and inputs.

---
## Usage

Run the shell by executing:
```bash
./minishell
```

**Examples**:
- Running a command:
  ```bash
  ls -la
  ```
- Piping commands:
  ```bash
  ls | grep minishell | wc -l
  ```
- Redirecting output:
  ```bash
  echo "Hello World" > output.txt
  ```
- Using built-in commands:
  ```bash
  export MY_VAR="42"
  echo $MY_VAR
  ```

---

## Important Functions

### `fork`

- **Usage**: `pid_t pid = fork();`
- Creates a child process to run commands independently.
- The child process executes commands, while the parent waits for it to finish.

### `execve`

- **Usage**: `execve(path, args, env);`
- Replaces the current process with a new program.
- Used in the child process to execute external commands like `ls`, `cat`, etc.

### `waitpid`

- **Usage**: `waitpid(pid, &status, 0);`
- Used by the parent process to wait for the child process to finish, enabling command synchronization.

### `pipe`

- **Usage**: `pipe(pipefd);`
- Creates a pipe for inter-process communication, allowing output from one command to be passed as input to another.

### `dup2`

- **Usage**: `dup2(fd, STDOUT_FILENO);`
- Duplicates a file descriptor to another, enabling redirection of standard input/output.
- Essential for implementing pipes and redirection within commands.

### `signal`

- **Usage**: `signal(SIGINT, handler_function);`
- Sets up custom signal handlers for signals like `SIGINT` and `SIGQUIT`.
- Ensures minishell handles interruptions gracefully.

### `getcwd`

- **Usage**: `getcwd(buffer, size);`
- Retrieves the current working directory path.
- Used in `pwd` and other commands requiring the current directory path.

### `chdir`

- **Usage**: `chdir(path);`
- Changes the current directory to the specified path.
- Used for the `cd` built-in command.

### `setenv` / `unsetenv`

- **Usage**: `setenv("VAR", "value", 1);`
- Sets or unsets environment variables, enabling dynamic environment updates.
- `export` and `unset` are implemented using these functions.

---

## Shell Operation

1. **Command Parsing**:
   - **Input Parsing**: Reads user input from the terminal and splits it into tokens.
   - **Command Identification**: Identifies if a command is built-in or external.
   - **Redirection and Piping**: Parses symbols like `>`, `<`, and `|` to handle redirection and pipelines.

2. **Process Management**:
   - **Parent Process**: Remains active to handle user input and manage child processes.
   - **Child Process**: Created by `fork()` to execute commands independently.
   - **Pipes and Redirection**: Uses pipes and `dup2` to redirect standard input/output as per the command syntax.

3. **Execution Flow**:
   - For each command, the shell forks a new child process.
   - In the child process, `execve` executes external commands, and control is returned to the parent.
   - Built-in commands are handled directly by the parent without forking new processes.

---

## Signal Handling

- **SIGINT (Ctrl+C)**: Terminates the current command or process without closing minishell.
- **SIGQUIT (Ctrl+\)**: Exits the running command but keeps minishell running.
- **Custom Handlers**: Signal handlers provide custom messages and prevent abrupt shell termination, allowing the user to interrupt processes smoothly.

Signal handling ensures that minishell behaves like a standard shell with familiar keyboard shortcuts for process control.

---

## Error Handling

- **Invalid Commands**: Displays an error message if the command is not recognized.
- **File Not Found**: Returns an error if files for redirection cannot be found.
- **Unmatched Quotes**: Detects and flags errors for syntax issues, such as unmatched quotes in input.

Error handling in **minishell** provides useful feedback to guide users, maintaining a robust and user-friendly shell environment.

---

## Supported Built-in Commands

### `echo`

- **Usage**: `echo [-n] [string ...]`
- Prints strings to the standard output. If `-n` is provided, `echo` omits the trailing newline.

### `cd`

- **Usage**: `cd [path]`
- Changes the current directory to `path`. If `path` is not provided, it defaults to the home directory.

### `pwd`

- **Usage**: `pwd`
- Prints the current working directory.

### `export`

- **Usage**: `export [name=value ...]`
- Sets environment variables or lists all environment variables if no arguments are provided.

### `unset`

- **Usage**: `unset [name ...]`
- Removes specified environment variables.

### `env`

- **Usage**: `env`
- Lists all environment variables.

### `exit`

- **Usage**: `exit [status]`
- Exits minishell with an optional exit status. If no status is provided, it defaults to the last command’s exit status.

---
