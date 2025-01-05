# RShell: A Custom Command Line Interpreter

RShell is a custom command-line interpreter designed to mimic the behavior of traditional Unix shells like Bash. It supports parsing and execution of commands with logical connectors (`&&`, `||`, `;`), as well as parenthetical grouping of commands.

## Features

- **Interactive Shell**: Continuously prompts for user input until the `exit` command is entered.
- **Command Execution**: Uses system calls (`fork`, `execvp`) to execute user commands.
- **Logical Connectors**:
  - `&&`: Executes the next command only if the previous command succeeds.
  - `||`: Executes the next command only if the previous command fails.
  - `;`: Executes commands sequentially regardless of success or failure.
- **Parentheses**: Supports grouping of commands using `()`.

## Code Structure

### Key Components

- **`Base`**: Abstract base class for all commands and connectors.
- **`Executable`**: Represents a single executable command with arguments.
- **`Connector`**: Abstract base class for logical connectors.
  - **`And`**: Implements `&&` logic.
  - **`Or`**: Implements `||` logic.
  - **`Semicolon`**: Implements `;` logic.
- **`Parser`**: Parses user input into executable commands and connectors.

### File Overview

- `main.cpp`: Entry point of the application. Handles the interactive shell loop.
- `parser.cpp`: Implements parsing logic to tokenize user input and construct command trees.
- `executable.cpp`: Handles command execution using system calls.
- `and.cpp`, `or.cpp`, `semicolon.cpp`: Implement the logic for the respective connectors.
- `connector.cpp`: Base class for connectors.

## Build Instructions

### Prerequisites

- A C++11 compatible compiler (e.g., g++)
- CMake 2.8 or higher

### Steps

1. Clone the repository:
   ```bash
   git clone [<repository-url>](https://github.com/edwjlr/RShell/)
   cd RShell
   ```
2. Build the project:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```
3. Run the application:
   ```bash
   ./rshell
   ```

## Usage

1. Launch RShell:
   ```bash
   ./rshell
   ```
2. Enter commands separated by connectors. Examples:
   - `echo Hello && echo World`
   - `ls -l || echo "Failed to list directory"`
   - `(mkdir test; cd test) && echo "Test directory created"`

3. Exit the shell:
   ```bash
   exit
   ```

## Design Patterns

- **Composite Pattern**: Used to construct and execute command trees.
- **Interpreter Pattern**: Used in the `Parser` to interpret user input.
- **Command Pattern**: Encapsulates executable commands.

## Limitations

- Command chaining logic is limited to connectors (`&&`, `||`, `;`).
- Error handling is basic; further improvements are needed for robustness.

## License

This project is open-source. Feel free to modify and use it for educational purposes.
