# Simple Shell Using C Programming

A lightweight Unix shell implemented in C that demonstrates core concepts of process management and command execution in a Unix-like environment.

## Overview

This project provides a basic shell interface that accepts user commands, executes built-in and system commands, and supports features such as:

- **Command Execution:** Runs external programs by forking and executing processes.
- **Built-in Commands:** Implements essential built-in commands (like `cd` and `exit`) to manage the shell session.
- **Prompt Display:** Continuously prompts the user for input and displays the output.
- **Error Handling:** Provides basic error handling for invalid commands and system call failures.

## Features

- **Process Management:** Uses `fork()`, `execvp()`, and `wait()` to handle process creation and termination.
- **Built-in Command Support:** Recognizes and processes commands internally when needed.
- **Interactive Command Line Interface:** Provides a user-friendly prompt that mimics common Unix shells.
- **Modular Code Structure:** Clean and commented source code that serves as a learning tool for understanding shell mechanics.

## Getting Started

### Prerequisites

- A Unix-like operating system (Linux, macOS, etc.)
- GCC (GNU Compiler Collection) installed

### Compilation

Clone the repository and compile the source code using GCC:

```bash
git clone https://github.com/defnotutkarsh/Simple-shell-using-c-programming.git
cd Simple-shell-using-c-programming
gcc -o shell shell.c
