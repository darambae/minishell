
# minishell
> **Versions**: [Français](#minishell---version-française) | [한국어](#minishell---한국어-버전)
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

**minishell** is an Ecole 42 project aimed at building a simplified Unix shell from scratch. This shell executes commands by interacting with the operating system, parsing input, and supporting common built-in commands. Through **minishell**, you gain hands-on experience with process management, file descriptors, signals, and the shell environment.

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

# minishell - Version Française

## Table des Matières

- [Introduction](#introduction)
- [Fonctionnalités](#fonctionnalités)
- [Fonctions Importantes](#fonctions-importantes)
- [Fonctionnement du Shell](#fonctionnement-du-shell)
- [Gestion des Signaux](#gestion-des-signaux)
- [Gestion des Erreurs](#gestion-des-erreurs)
- [Commandes Intégrées Prises en Charge](#commandes-intégrées-prises-en-charge)

---

## Introduction

**minishell** est un projet de l'École 42 destiné à créer un shell Unix simplifié. Ce shell exécute des commandes en interagissant avec le système d'exploitation, en analysant les entrées, et en prenant en charge des commandes intégrées courantes. **minishell** offre une expérience pratique de gestion de processus, de descripteurs de fichiers, de signaux, et de l'environnement du shell.

---

## Fonctionnalités

- **Exécution de Commandes** : Exécute des commandes système avec gestion des redirections et des pipes.
- **Commandes Intégrées** : Implémente des commandes essentielles telles que `echo`, `cd`, `pwd`, `export`, `unset`, `env`, et `exit`.
- **Gestion de l'Environnement** : Maintient et modifie les variables d'environnement du shell.
- **Gestion des Signaux** : Gère les signaux comme `SIGINT` (Ctrl+C) et `SIGQUIT` (Ctrl+\) pour une meilleure expérience utilisateur.
- **Gestion des Erreurs** : Affiche des messages d'erreur descriptifs pour les commandes ou entrées non valides.

---

**Exemples** :
- Exécuter une commande :
  ```bash
  ls -la
  ```
- Chainer des commandes :
  ```bash
  ls | grep minishell | wc -l
  ```
- Redirection de sortie :
  ```bash
  echo "Bonjour le monde" > output.txt
  ```
- Utiliser des commandes intégrées :
  ```bash
  export MA_VAR="42"
  echo $MA_VAR
  ```

---

## Fonctions Importantes

### `fork`

- **Usage** : `pid_t pid = fork();`
- Crée un processus enfant pour exécuter des commandes de manière indépendante.
- Le processus enfant exécute les commandes, tandis que le processus parent attend qu'il se termine.

### `execve`

- **Usage** : `execve(path, args, env);`
- Remplace le processus actuel par un nouveau programme.
- Utilisé dans le processus enfant pour exécuter des commandes externes comme `ls`, `cat`, etc.

### `waitpid`

- **Usage** : `waitpid(pid, &status, 0);`
- Utilisé par le processus parent pour attendre la fin du processus enfant, permettant la synchronisation des commandes.

### `pipe`

- **Usage** : `pipe(pipefd);`
- Crée un canal pour la communication entre processus, permettant à la sortie d'une commande de passer en entrée d'une autre.

### `dup2`

- **Usage** : `dup2(fd, STDOUT_FILENO);`
- Duplique un descripteur de fichier vers un autre, permettant la redirection de l'entrée/sortie standard.

### `signal`

- **Usage** : `signal(SIGINT, handler_function);`
- Définit des gestionnaires de signaux personnalisés pour les signaux comme `SIGINT` et `SIGQUIT`.

### `getcwd`

- **Usage** : `getcwd(buffer, size);`
- Récupère le chemin du répertoire de travail actuel.

### `chdir`

- **Usage** : `chdir(path);`
- Change le répertoire actuel vers le chemin spécifié.

### `setenv` / `unsetenv`

- **Usage** : `setenv("VAR", "valeur", 1);`
- Définit ou supprime des variables d'environnement.

---
## Fonctionnement du Shell

Le fonctionnement du shell implique deux processus principaux :
- **Processus Parent** : Attend les processus enfants, gère les entrées utilisateur, et maintient l'environnement du shell.
- **Processus Enfant** : Exécute les commandes en utilisant `execve`. Pour chaque commande non intégrée, un processus enfant est créé par le parent à l'aide de `fork`, et le code de la commande est exécuté par l'enfant.
---
## Gestion des Signaux

minishell gère des signaux comme `SIGINT` (Ctrl+C) et `SIGQUIT` (Ctrl+\) :
- **SIGINT** : Interrompt l'exécution actuelle et retourne au prompt.
- **SIGQUIT** : Ignoré pendant l'exécution du shell principal, mais termine un processus en cours.
---
## Gestion des Erreurs

Les erreurs dans minishell incluent :
- **Commandes Introuvables** : Affiche un message indiquant que la commande n'est pas reconnue.
- **Permissions Insuffisantes** : Affiche un message si le fichier cible ne peut être exécuté.
- **Redirections ou Pipes Incorrects** : Signale toute erreur dans les redirections ou les pipes.
---
## Commandes Intégrées Prises en Charge

minishell implémente les commandes intégrées suivantes :
- **`echo`** : Affiche le texte fourni.
- **`cd`** : Change le répertoire de travail actuel.
- **`pwd`** : Affiche le répertoire de travail actuel.
- **`export`** : Définit une variable d'environnement.
- **`unset`** : Supprime une variable d'environnement.
- **`env`** : Liste toutes les variables d'environnement.
- **`exit`** : Termine le shell.

---

# minishell - 한국어 버전

## 목차

- [소개](#소개)
- [기능](#기능)
- [중요 함수](#중요-함수)
- [쉘 동작](#쉘-동작)
- [신호 처리](#신호-처리)
- [에러 처리](#에러-처리)
- [지원되는 내장 명령어](#지원되는-내장-명령어)

---

## 소개

**minishell**은 Unix 쉘을 간소화한 프로젝트로, 운영 체제와의 상호 작용을 통해 명령어를 실행하고 입력을 분석하며 내장 명령어를 지원합니다. **minishell**을 통해 프로세스 관리, 파일 디스크립터, 신호 및 쉘 환경 관리에 대해 학습하게 됩니다.

---

## 기능

- **명령어 실행** : 리다이렉션 및 파이프 처리를 포함한 시스템 명령어를 실행합니다.
- **내장 명령어** : `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit` 등의 기본 명령어를 구현합니다.
- **환경 변수 관리** : 쉘 환경 변수를 유지 및 수정할 수 있습니다.
- **신호 처리** : `SIGINT` (Ctrl+C) 및 `SIGQUIT` (Ctrl+\)와 같은 신호를 처리합니다.
- **에러 관리** : 지원되지 않는 명령어 또는 잘못된 입력에 대해 설명하는 에러 메시지를 표시합니다.

---

**예제**:
- 명령어 실행:
  ```bash
  ls -la
  ```
- 명령어 파이핑:
  ```bash
  ls | grep minishell | wc -l
  ```
- 출력 리다이렉션:
  ```bash
  echo "Hello World" > output.txt
  ```
- 내장 명령어 사용:
  ```bash
  export MY_VAR="42"
  echo $MY_VAR
  ```

---

## 중요 함수

### `fork`

- **사용법** : `pid_t pid = fork();`
- 명령을 독립적으로 실행하기 위해 자식 프로세스를 만듭니다.
- 자식 프로세스는 명령을 실행하고, 부모 프로세스는 완료될 때까지 대기합니다.

### `execve`

- **사용법** : `execve(path, args, env);`
- 현재 프로세스를 새로운 프로그램으로 대체합니다.
- 자식 프로세스에서 외부 명령어(`ls`, `cat` 등)를 실행하는 데 사용됩니다.

### `waitpid`

- **사용법** : `waitpid(pid, &status, 0);`
- 부모 프로세스가 자식 프로세스가 종료될 때까지 대기하게 하여 명령 동기화를 가능하게 합니다.

### `pipe`

- **사용법** : `pipe(pipefd);`
- 프로세스 간 통신을 위한 파이프를 생성하여 명령의 출력을 다른 명령의 입력으로 전달합니다.

### `dup2`

- **사용법** : `dup2(fd, STDOUT_FILENO);`
- 파일 디스크립터를 다른 디스크립터로 복제하여 표준 입출력을 리다이렉션할 수 있습니다.

### `signal`

- **사용법** : `signal(SIGINT, handler_function);`
- `SIGINT` 및 `SIGQUIT`와 같은 신호에 대해 사용자 정의 신호 핸들러를 설정합니다.

### `getcwd`

- **사용법** : `getcwd(buffer, size);`
- 현재 작업 디렉토리의 경로를 가져옵니다.

### `chdir`

- **사용법** : `chdir(path);`
- 현재 디렉토리를 지정된 경로로 변경합니다.

### `setenv` / `unsetenv`

-

 **사용법** : `setenv("VAR", "value", 1);`
- 환경 변수를 설정하거나 제거합니다.

---
## 쉘 동작

쉘의 동작은 두 가지 주요 프로세스로 구성됩니다:
- **부모 프로세스** : 자식 프로세스를 기다리고, 사용자 입력을 처리하며 쉘 환경을 유지합니다.
- **자식 프로세스** : `execve`를 사용해 명령어를 실행합니다. 내장 명령어가 아닌 각 명령어에 대해 부모가 `fork`를 사용해 자식 프로세스를 생성하며, 자식이 명령어를 실행합니다.
---
## 신호 처리

minishell은 `SIGINT` (Ctrl+C)와 `SIGQUIT` (Ctrl+\)와 같은 신호를 처리합니다:
- **SIGINT** : 현재 실행을 중단하고 프롬프트로 돌아갑니다.
- **SIGQUIT** : 쉘이 실행 중일 때는 무시되지만, 진행 중인 프로세스는 종료됩니다.
---
## 에러 처리

minishell의 에러 처리에는 다음이 포함됩니다:
- **명령어를 찾을 수 없음** : 명령어가 인식되지 않음을 알리는 메시지가 표시됩니다.
- **권한 부족** : 파일을 실행할 수 없을 때 메시지를 표시합니다.
- **잘못된 리다이렉션 또는 파이프** : 리다이렉션이나 파이프 오류가 있을 경우 에러 메시지를 표시합니다.
---
## 지원되는 내장 명령어

minishell은 다음 내장 명령어들을 지원합니다:
- **`echo`** : 제공된 텍스트를 출력합니다.
- **`cd`** : 현재 작업 디렉토리를 변경합니다.
- **`pwd`** : 현재 작업 디렉토리를 표시합니다.
- **`export`** : 환경 변수를 설정합니다.
- **`unset`** : 환경 변수를 제거합니다.
- **`env`** : 모든 환경 변수를 나열합니다.
- **`exit`** : 쉘을 종료합니다.
---
