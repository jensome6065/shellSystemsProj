[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/77as2zNO)

# Systems Project2 - MyShell

# 9-YuE-YeJ

## function headers

void parse(char* line, char** argArray);

void exitCom();

void changeDir(char* input);

int err();

void redirect(char* command, char** args);

void pipee(char* comm);

## description of features

parse: 

exitCom:
this function exits the program with no issues, so an exit status of 0, and prints a message stating it is exiting normally. 

changeDir: 

err: 
this prints out an error message in the stdout and exits with an exit status of 1.

redirect: 

pipee:
this mimics the pipe ability in the bash terminal, where the output of the left side of the pipe is the input of the right side of the pipe. our pipee function accounts for commands and commands with redirection.

## bugs

