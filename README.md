**Assignment2.cpp**
> All the user-defined header files are included for every command implemented
> The user name and system name display is printed in a while loop and takes user input using getline
> Tokenization based on spaces is done and the command is pushed into token_array vector
> The command is read from the token_array and based on the command the corresponding function is call from its respective file
> If the command is 'exit', it breaks from the loop and the terminal ends
> Signal handling is done for ctrl+c and ctrl+z

**bgfg.cpp**
> fork() system call is used to create child process
> If it is a background process, the flag is set to 1 and pid of the process is printed
> If the flag is 0 it is a foreground process and the terminal waits until the process is completed

**cd.cpp**
> chdir() is used to change the directory based on the path given
> In order to handle cases like cd -, the previous directory paths are found using getcwd() and then chdir() is applied
> The terminal display is changed accordingly using the display_update() function based on the directory we are changing to

**echo.cpp**
> The contents present after the echo command are printed by iterating over the arguments using a for loop

**history.cpp**
> Global variables are declared for max commands to print and max commands to store
> The file test1.txt where all commands are stored is also declared as global
> When history command is called from main function, the get_hist() is called first, where the commands are read from the file and pushed into the commands vector
> This commands vector and the no. of commands to be printed are given as arguments to print_hist() function
> This function prints the history commands onto the console by checking the max conditions
> add_hist() is another function declared that is used to write the commands into the test1.txt file whenever any command is executed

**ls.cpp**
> the ls_cmd() function checks the arguments provided with ls command
> Based on the arguments provided, the flag values are assigned and the ls_dir() function is called
> The functionalities of -l, -a and any path are given and output is printed on console

**pinfo.cpp**
> It uses the /proc filesystem
> It displays the procedd ID, process status, memory and the executable path
> When run without arguments, it displays the info about the current process
> When run with any argument, it displays the info about the process PID specified
> It uses readlink on /proc/[pid]/exe to retrieve the executable path

**pwd.cpp**
> pwd_cmd() function is defined which checks whether the current working directory is equal to home directory using getcwd()
> If it is equal, then the original display is printed
> If it is different, the relative path is extracted from the complete path of the current directory and appended to the original display 

**ioredir.cpp**
> It splits commands into tokens and handles >, >>, < for redirection
> The check_cmd() function detects redirection operators and gives flags based on the operator
> The exec_redir() function executes the command using execvp() and dup2() is used to redirect the output to the file
> append is a boolean variable used to determine if the file needs to be appended or not

**search.cpp**
> search_cmd() function is called from main which calls the search_dir() function 
> search_dir() recursively checks every directory using S_ISDIR() to locate the file or folder specified
> It is done using struct dirent and DIR* to point to each directory entry and readdir() is used to read each entry
> The names are compared with the target file and returns true if found otherwise returns false

Header files are created for each file and included in the main file 'Assignment2.cpp'

How to compile the code:
make main

How to run the code:
./a.out