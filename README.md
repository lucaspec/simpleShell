# Simple Shell

This is a simple shell with basic bash functionality. It has its own file system based on a tree abstraction. Files are stored flat within ```/mnt```. I refrained from using bash commands but allowed myself to utilise system calls.

## Get Started

Compile the shell
```bash
make all
```

Start shell
```bash
./shell
>>
```


## Commands

Following list comprises currently supported commands and operations.

1. **cd** - Change directory
   - `cd directory_name`
   - `cd ..`
   - `cd`

2. **ls** - List files and directories
   - `ls`

3. **mkdir** - Create a new directory
   - `mkdir directory_name`

4. **tree** - Show folder hierarchy
   - `tree`

5. **touch** - Create file
   - `touch file_name`
