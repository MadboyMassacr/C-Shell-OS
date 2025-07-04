# Shell Implementation in C!

This project is a basic implementation of a shell in the C programming language. The shell provides a command-line interface for users to interact with the operating system.

## Getting Started

### Prerequisites

- Ensure you have [C compiler](https://gcc.gnu.org/install/index.html) installed.

### Building

1. Clone the repository:

   ```bash
   git clone https://github.com/MadboyMassacr/C-Shell-OS.git
   cd c-shell

2. Starting the shell
    ```bash 
    make clean;make
    ./shell

## Using The Shell


### 1. Prompt Display
The shell displays a custom prompt indicating the current user, system name, and working directory. The home directory is represented as "~," and paths are displayed relative to it.

### 2. Command Separation
Commands can be entered using either ; or & as separators to execute multiple commands in sequence or concurrently.

### 3. warp Command
The warp command changes the current working directory. It supports flags such as ".", "..", "~", and "-" for navigation. Multiple warp commands can be executed sequentially when provided with multiple arguments.

```bash
warp test
warp assignment
warp ~
warp -
warp .. tutorial
warp ~/project
```


### 4. peek Command
The peek command lists files and directories in a specified directory. It supports flags -a and -l for displaying hidden files and additional information. Differentiates file types with color coding (green for executables, white for files, and blue for directories).

```bash
 
peek test
peek -a -l directory
peek -d -e filename
```

### 5. pastevents Command
The pastevents command stores and retrieves the 15 most recent unique command statements. It supports the execute option to run a command from the past by index and provides a purge option to clear all stored past events.

```bash
 
pastevents
pastevents execute 3
pastevents purge
```

### 6. System Commands
The shell executes system commands both in the foreground and background. It captures and displays the process ID (PID) of background processes.

```bash
 
ls
sleep 5 &
echo "Hello"
```
### 7. proclore Command
The proclore command displays information about a specified process, including PID, process status, process group, virtual memory, and executable path.

```bash
 
proclore
proclore 123
```

### 8. seek Command
The seek command searches for files or directories in the specified target directory. It supports flags -d, -f, and -e for filtering results.

```bash
 
seek filename
seek -d directory
seek -f filename directory
seek -e -f filename directory
```

### 9. I/O Redirection
The shell supports I/O redirection using >, >>, and <. It creates or appends to output files and handles input files appropriately.

```bash
 
echo "Hello" > output.txt
cat < input.txt
command >> log.txt
```

### 10. Pipes
The shell implements pipes (|) for passing information between commands. It supports any number of pipes for both user-defined and system commands.

```bash
command1 | command2
command1 | command2 | command3
```

### 11. Redirection with Pipes
Enables I/O redirection along with pipes for user-defined and system commands.

```bash

 
command1 < input.txt | command2 > output.txt
```
### 12. activities Command
The activities command displays a list of currently running processes spawned by the shell. It shows PID, command name, and state (running or stopped).

```bash

 
activities
```

### 13. ping Command
The ping command sends signals to processes based on PID and signal number. It displays success messages or an error if the process is not found.

```bash 
 
ping 123 9
ping 456 15
```
### 14. fg and bg Commands
The fg command brings a background process to the foreground, and the bg command changes the state of a stopped background process to running.

```bash

 
fg 123
bg 456
```
### 15. Neonate Command
The Neonate command prints the PID of the most recently created process at intervals until the 'x' key is pressed.

```bash
 
neonate -n 4
```

### 16. iMan Command
The iMan command fetches and displays man pages from http://man.he.net/. It accepts a command name as an argument and retrieves the corresponding man page.

```bash
 
iMan ls
iMan grep
```

### 16. Signals
Following 3 commands are direct keyboard input where Ctrl is Control key on keyboard (or it’s equivalent).

#### Ctrl - C

- Interrupt any currently running foreground process by sending it the SIGINT signal. It has no effect if no foreground process is currently running.

#### Ctrl - D

- Log out of your shell (after killing all processes) while having no effect on the actual terminal.

#### Ctrl - Z

- Push the (if any) running foreground process to the background and change it’s state from “Running” to “Stopped”. It has no effect on the shell if no foreground process is running.

## Notes

Please note that the provided documentation is for reference, and specific command outputs may vary based on system configuration.

This shell implementation is designed for educational purposes and may not cover all edge cases or handle complex scenarios.

Feel free to reach out for any assistance or clarification. Happy shell scripting!
