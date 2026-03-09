# MiniShell – Linux Command Interpreter

MiniShell is a simplified implementation of a **Linux command-line shell** developed using **C programming and POSIX system calls**.  
The shell reads user commands, determines whether they are **built-in or external commands**, and executes them accordingly.

This project demonstrates concepts such as **process creation, signal handling, and job control** in Linux system programming.

---

# Features

- Execute **external Linux commands**
- Support for **built-in shell commands**
- **Foreground and background process execution**
- **Job control using signals**
- **Custom shell prompt (PS1)**
- Prevents **zombie processes**

---

# Technologies Used

- C Programming
- Linux System Programming
- POSIX System Calls
- Process Management
- Signal Handling

---

# System Calls Used

| System Call | Purpose |
|-------------|--------|
| `fork()` | Create a new child process |
| `execvp()` | Execute external commands |
| `waitpid()` | Wait for child process |
| `signal()` | Handle signals |
| `system()` | Execute system commands |

---

# Built-in Commands

Examples of supported internal commands:

- `cd` – Change directory
- `pwd` – Print current directory
- `exit` – Exit shell
- `jobs` – List background jobs

---

# Working Principle

1. Display shell prompt.
2. Read user input.
3. Parse the command.
4. Determine command type:
   - Built-in command
   - External command
5. Execute command using appropriate method.

---

# Applications

- Learning Linux shell internals
- Understanding process management
- system programming concepts

---
