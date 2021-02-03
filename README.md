
                                          Basic Linux/Unix shell
                                                            
                                                            

I had implemented two types of bash commands:

1) Internal commands

I had implemented five Internal commands like ‘cd’, ‘echo’, ‘history’, ‘pwd’ and ‘exit’.

'cd' - Helps in changing current directory.
followed by directory path and prints error if path doesn't exists.
Flags Implemented:
-e - return -1 if directory path doesn't exists.
--help - Demonstrate how to use cd commands along with implemented flags.

'echo' - Prints the statement followed by this bsh command along with newline character.
Flags Implemented:
-n - prints the statement without newline character
-E - default implementation of echo command with implemented flags.

'history' - Prints the history of commands used in current session of terminal
Flags Implemented:
-w - stores the history of current bash session to history.txt file for permanent store.
--help - Demonstrate how to use history commands along with implemented flags.

'pwd' - Helps to get current path of file and prints error if extra inputs are provided.
Flags Implemented:
-L - default implementation of pwd is done by this flag in terminal.
--help - Demonstrate how to use pwd commands along with implemented flags.

'exit' - exits the terminal session



2) External commands
 
I had implemented five External commands like ‘ls’, ‘cat’, ‘date’, ‘rm’ and ‘mkdir’.

'ls' - Tells the name of all files/folders present in current directory sorted in ascending order. Case for ls for different directory in one command is also handled.
Flags Implemented:
-1 - Prints the name of all files/folders present in current directory sorted in ascending order in vertical lines instead of default horizontal alignmnent.
--help - Demonstrate how to use ls commands along with implemented flags.

'cat' - Concatenates the content of given numbers files and display on console. Prints error if any file is not present along with output of files presented.
Flags Implemented:
-n - Prints the number along with each line.
-E - Prints $ at the end of each line.
--help - Demonstrate how to use cat commands along with implemented flags.

'date' - Prints standard system date with console format.
Flags Implemented:
-R - prints current date in UTC time zone format.
-u - prints current UTC zone time.
--help - Demonstrate how to use date commands along with implemented flags.

'rm' - use to delete listed files as arguments and shows error if any file doesn't exists. It does not remove directory by default.
Flags Implemented:
-d - use to empty directory if present else shows error.
--help - Demonstrate how to use delete commands along with implemented flags.

'mkdir' - use to make new directory at the current pwd location.
Flags Implemented:
-v - prints success message on console whenever directory is created successfully.
--help - Demonstrate how to use delete commands along with implemented flags.


Implementation of external commands is done by fork() system call, creating child process for external bash command and replacing child code by execvp passing file path along with double pointer to specific file.
'date' -> date.c
'ls' -> ls.c
'history' -> history.c
'rm' -> rem.c
'cat' -> cat.c




Common Errors Handled:

1) Shows bash error for any wrong command except of above listed 10 implemented commands.
2) Unknown flag error.
3) Insufficient/Extra provided arguments to particular command.


Testcase and Sceenshots:

Basic test case are also provided along with their output in the form of practical runnung by screenshots. Kindly refer to them for better understanding. 
Screenshots are present in 'Screenshots' folder.

Sample inputs:

ls 

ls -l 

mkdir 

mkdir nik@1 

rm -d nik@1 

date 

date cdmv 

pwd 

cd.. 

cd .. 

pwd 

history 

history -w 

exit 

cat history.txt 

exit 


NOTE:

Kindly remember to use '@' delemiter instead of space for passing name of files or text to be echoed.
                                                  
