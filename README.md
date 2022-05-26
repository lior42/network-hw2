# Home Work 2
## Submitters
todo later

## Tools in use
1. gcc
2. GNU make
3. clangd
4. clang-format
5. clang-tidy
6. Visual Studio Code (clangd extension) / VSCodium (clangd extension)
7. Bear (Optional)

### one-line installation (ubuntu based distro, without ide)
```bash
$ sudo apt install gcc build-essential clangd clang-format clang-tidy bear
```
note that it can be a large installation (~1 GB).
## Tested on
1. Pop OS 22.04

## Usage
- Formatting: shortcut *Ctrl+Shift+I* (On linux).
- For every new file / new compilation flag, run the following command, it will help with auto-completion: 
```bash
$ bear -- make
```
- Compile: stand in this directory and run ```make```.
- all *\*.c* files must be in src folder directly. it should be fine for a small project.