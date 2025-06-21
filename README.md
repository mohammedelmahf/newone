# 🐚 minishell

A minimal Unix shell, written in C, designed to mimic the fundamental behavior of Bash.  
This project is a pedagogical exercise focused on understanding how command-line interpreters work under the hood.

---

## 🚀 Features

- **Command Parsing & Execution**  
  Supports execution of binaries and built-in commands with proper parsing logic.

- **Built-ins Implemented**  
  `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

- **Redirections & Pipes**  
  Handles input/output redirections (`>`, `>>`, `<`) and piping of commands (`|`).

- **Environment Variable Expansion**  
  Recognizes and expands `$VARS` in commands.

- **Signal Handling**  
  Graceful handling of `SIGINT` (`Ctrl+C`) and `SIGQUIT` (`Ctrl+\`).

- **Error Handling**  
  Detects and reports syntax and execution errors.

---

## ⚙️ Getting Started

### Prerequisites

- GCC or Clang
- GNU Make
- Unix-like OS (Linux, macOS, WSL)

### Build

```sh
make
```

### Run

```sh
./minishell
```
Enter your commands at the prompt!

---

## 🧑‍💻 Usage Examples

```sh
ls -al | grep minishell > output.txt
export PATH=$PATH:~/bin
cd ..
echo "Hello, Minishell!"
cat < input.txt | sort | uniq > result.txt
```

---

## 📁 Project Structure

- `src/` — Source files for shell logic
- `include/` — Header files
- `Makefile` — Build instructions

---

## 🏗️ Limitations

- No wildcard (globbing) expansion
- Limited quoting/escaping
- No advanced scripting or job control

---

## 👥 Authors

- [hmouis](https://github.com/hmouis)
- [oait-h-m](https://github.com/oait-h-m)

---

## 📜 License

For educational use only.

---

> _"The shell is both a command language and a programming language, and learning to build one is the best way to understand UNIX."_
