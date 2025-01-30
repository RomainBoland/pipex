🔧 Pipex - 42 Project

[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com)

## 📋 Table of Contents

- [About](#about)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [How it Works](#how-it-works)
- [Error Handling](#error-handling)
- [File Structure](#file-structure)

## 📖 About <a name="about"></a>

The Pipex project is part of the 42 school curriculum, designed to deepen understanding of UNIX mechanisms. It recreates the pipe (`|`) operator's functionality in C, handling processes, file descriptors, and pipe communication.

## ⭐ Features <a name="features"></a>

- Process multiple shell commands
- Handle input/output file redirection
- Implement pipe communication
- Error management
- Memory leak prevention
- Path handling and command execution

## 🚀 Installation <a name="installation"></a>

```bash
# Clone the repository
git clone https://github.com/RomainBoland/pipex.git

# Move to the project directory
cd pipex

# Compile the project
make
```
💻 Usage <a name="usage"></a>

bashCopy./pipex file1 cmd1 cmd2 file2
This is equivalent to the shell command:
bashCopy< file1 cmd1 | cmd2 > file2
🔍 Examples <a name="examples"></a>
bashCopy# Example 1: Count number of files
./pipex infile "ls -l" "wc -l" outfile

# Example 2: Search and count words
./pipex file.txt "grep hello" "wc -w" results.txt

# Example 3: Multiple transformations
./pipex text.txt "cat -e" "tr a b" output.txt
⚙️ How it Works <a name="how-it-works"></a>

Program initialization

Argument validation
File descriptor setup
Pipe creation


Process Management

Creates two child processes
Each process handles one command
Manages pipe communication between processes


Command Execution

Locates command in system PATH
Splits command into arguments
Executes command with proper redirection



❗ Error Handling <a name="error-handling"></a>
The program handles various error cases:

Invalid number of arguments
File access errors
Command not found
Fork failures
Pipe creation errors
Memory allocation failures

📁 File Structure <a name="file-structure"></a>
Copypipex/
├── includes/
│   └── pipex.h
├── src/
│   ├── main.c
│   ├── utils.c
│   └── process.c
├── Makefile
└── README.md
🛠️ Technical Details

Written in C
Uses fork(), pipe(), execve()
Handles file descriptors
Manages child processes
Implements proper memory management

📝 Note
This project follows 42 school's norminette coding style and guidelines.

Made with ❤️ by [Your Name]
If you found this helpful, please give it a ⭐