# Minishell

Minishell is a project from the 42 curriculum that consists of creating a simple UNIX shell, inspired by bash.  
The goal is to understand how a real shell works by building one from scratch, handling processes, parsing commands, and managing input/output redirections.

---

## Project Overview

The Minishell program:
- Provides a command-line interface similar to bash.
- Parses and executes user commands.
- Implements environment variable handling.
- Manages input/output redirections and pipelines.
- Handles signals such as `Ctrl+C`, `Ctrl+D`, and `Ctrl+\`.

This project is designed to improve understanding of processes, file descriptors, system calls, and UNIX fundamentals.

---

## Features

- Prompt display awaiting user input.
- Command execution with arguments (via `execve`).
- Built-in commands:
  - `echo` (with `-n` option)
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Pipes (`|`) and redirections (`<`, `>`, `>>`, `<<`).
- Environment variable expansion (`$VAR`).
- Proper signal handling.

---

## Installation and Usage

```bash
# Build Requirements
sudo apt update
sudo apt install build-essential
sudo apt install  libreadline-dev

# Clone the repository
git clone https://github.com/Chaudbrush/42_minishell.git
cd 42_minishell

# Compile
make

# Run
./minishell
