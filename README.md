# shell-emulation
## Installation
### Clone this repository
```
git clone https://github.com/ClayMav/shell-emulation.git
```
### Additional installation instructions
To run this on your computer:

* Clone this repository
* `make`
* `./bin/runner`

## Operating
## Implemented commands
### ls
Print files and folders in current directory
```
$ ls
$ ls -l
```

### cd
Change directory
```
$ cd some_directory
```

### mkdir
Makes a new folder in current directory
```
$ mkdir new_directory
```

### rmdir
Delete the target directory
```
$ rmdir some_directory
```

### rm
Delete the target file
```
$ rm some_file
```

### pwd
Prints current directory
```
$ pwd
```

### touch
Creates file if not already there, or updates modified time
```
$ touch new_file
$ touch existing_file
```

### chmod
Changes permission on files or folders
```
$ chmod 777 some_file
$ chmod 654 some_directory
```

### exit/quit
Exits the shell
```
$ exit
$ quit
```
