# 🍣 SUSHI — Simple Unix Shell Implementation

A custom Unix shell built from scratch in **C++**, featuring lexical analysis, grammar parsing, process management, I/O redirection, and piping — developed as a semester-long Operating Systems course project.

![C++](https://img.shields.io/badge/C++-17-blue?logo=cplusplus) ![Flex](https://img.shields.io/badge/Lexer-Flex-orange) ![Bison](https://img.shields.io/badge/Parser-Bison-green) ![Make](https://img.shields.io/badge/Build-Make-lightgrey) ![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS-informational)

---

## Overview

**SUSHI** (Simple Unix Shell Implementation) is a fully functional Unix shell that replicates core behaviors of shells like `bash` and `zsh`. It was built incrementally over six assignments, progressively adding features from basic command parsing to inter-process communication via pipes.

The shell accepts interactive user input or script files, parses commands using a formal grammar (Flex + Bison), and executes them by forking child processes with proper signal handling, I/O redirection, and pipeline support.

---

## Features

- **Interactive REPL** — Persistent read-eval-print loop with a customizable prompt (`PS1` environment variable)
- **Command Parsing** — Full lexical analysis (Flex) and grammar-based parsing (Bison/Yacc) for robust command interpretation
- **Process Spawning** — `fork()`/`execvp()` based execution with proper parent-child process management
- **I/O Redirection** — Support for input (`<`), output (`>`), and append (`>>`) redirection using file descriptors
- **Piping** — Inter-process communication via Unix pipes (`|`) connecting stdout of one process to stdin of another
- **Background Execution** — Run commands in the background with `&`
- **Built-in Commands** — Native support for `cd`, `pwd`, `history`, `exit`, and environment variable assignment (`VAR=value`)
- **Command History** — Stores and recalls up to 10 recent commands with `!n` bang syntax
- **Configuration File** — Reads and executes commands from `~/sushi.conf` on startup
- **Signal Handling** — Graceful `SIGINT` handling prevents the shell from terminating on Ctrl+C
- **Environment Variables** — Get, set, and expand environment variables (including `$?` for exit status)
- **Escape Sequence Processing** — Full support for string escape characters (`\\n`, `\\t`, `\\\\`, etc.)
- **Script Execution** — Pass script files as command-line arguments for batch processing

---

## Architecture

```
┌─────────────┐     ┌──────────────┐     ┌──────────────┐
│   Main.cc   │────▶│   Sushi.cc   │────▶│   spawn()    │
│  (Entry)    │     │  (Core Shell)│     │  fork/exec   │
└─────────────┘     └──────┬───────┘     └──────────────┘
                           │
                    ┌──────▼───────┐
                    │ parse_command │
                    └──────┬───────┘
                           │
              ┌────────────▼────────────┐
              │    Flex Lexer           │
              │  (sushi_yylexer.l)     │
              │    Tokenization         │
              └────────────┬────────────┘
                           │
              ┌────────────▼────────────┐
              │    Bison Parser         │
              │  (sushi_yyparser.y)    │
              │    Grammar Rules        │
              └─────────────────────────┘
```

**Key Classes:**

| Class | Responsibility |
|-------|---------------|
| `Sushi` | Core shell — main loop, history, config, process spawning, signal handling |
| `Program` | Represents an executable command with arguments, redirections, and pipe linkage |
| `Redirection` | Manages stdin/stdout/append file descriptor redirections |
| `Pipe` | Linked list structure connecting programs in a pipeline |

---

## Tech Stack

| Technology | Purpose |
|-----------|---------|
| **C++** | Core implementation language |
| **POSIX API** | `fork()`, `execvp()`, `pipe()`, `dup2()`, `waitpid()`, `sigaction()` |
| **Flex** | Lexical analysis — tokenizing shell input |
| **Bison** | Parser generator — grammar-based command parsing |
| **Make** | Build automation with dependency management |

---

## Getting Started

### Prerequisites

- **GCC/G++** (C++17 or later)
- **Flex** (lexical analyzer generator)
- **Bison** (parser generator)
- **Make**
- Linux or macOS environment

### Build & Run

```bash
# Clone the repository
git clone https://github.com/vinilmatic/sushi-vinil-keshav.git
cd sushi-vinil-keshav

# Build the project
make

# Run the shell interactively
./sushi

# Or run a script file
./sushi script.sh
```

### Usage Examples

```bash
sushi> ls -la                    # List files
sushi> echo hello > output.txt   # Output redirection
sushi> cat < input.txt           # Input redirection
sushi> ls | grep .cc             # Piping
sushi> sleep 10 &                # Background execution
sushi> PS1="myshell> "           # Custom prompt
sushi> history                   # View command history
sushi> !3                        # Re-run 3rd most recent command
sushi> cd /tmp                   # Change directory
sushi> pwd                       # Print working directory
sushi> exit                      # Exit the shell
```

---

## Project Structure

```
├── Main.cc                 # Entry point — initializes shell and runs main loop
├── Sushi.hh                # Header — class definitions for Sushi, Program, Redirection
├── Sushi.cc                # Implementation — shell core, process spawning, signal handling
├── sushi_parse.cc          # String utilities, environment variables, command re-parsing
├── sushi_yylexer.l         # Flex lexer specification — tokenization rules
├── sushi_yyparser.y        # Bison parser grammar — command syntax rules
├── Pipe.hh                 # Pipe data structure for multi-command pipelines
├── Makefile                # Build system with dependency generation
├── sushi.conf              # Default startup configuration script
└── test.sh                 # Test script for shell features
```

---

## Key OS Concepts Demonstrated

This project demonstrates practical understanding of core operating systems concepts:

- **Process creation and management** — `fork()`, `execvp()`, `waitpid()` system calls
- **Inter-process communication** — Unix pipes for connecting process I/O streams
- **File descriptor manipulation** — `dup2()`, `open()`, `close()` for I/O redirection
- **Signal handling** — Custom `SIGINT` handler with `sigaction()` to prevent shell termination
- **Environment variables** — Reading and modifying the process environment at runtime
- **Compiler construction fundamentals** — Lexer/parser pipeline using industry-standard tools (Flex/Bison)
- **Memory management** — Manual allocation/deallocation in a systems programming context

---

## License

This project was developed for academic purposes as part of an Operating Systems course.

---

*Built with ❤️ and systems-level programming*
