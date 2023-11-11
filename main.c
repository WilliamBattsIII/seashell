#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
void displayprompt() {
  char usr[4] = " > "; // 4 bytes for the spaces + null
  char cwd[4097]; // maximum path length allowed in linux is 4096 bytes
  if(geteuid() == 0)  {strcpy(usr, " # ");} // if we're root, set the prompt to #
  else {strcpy(usr, " $ ");} // if we're not root, set the prompt to $
  
  char *prompt = usr; // I forgot why this is here, but I haven't touched this function in 2 years, so it stays
  getcwd(cwd, sizeof(cwd)); // get the current working directory
  printf("%s%s", cwd, prompt);
}

char input[64];


int runcmd(char *cmd) {
    int pid = fork();
    if(pid < 0) {
        printf("fork() failed!\n");
        perror(cmd);
        exit(1);
    }
    if(pid == 0) { // now we're a child process
        char* args[] = {cmd, NULL};
        if(execv(cmd, args)) {perror(cmd);}
        printf("execv() failed!\n"); // we should never get here
        exit(1);
    }
    int status; // some stuff I don't fully understand, from google
    wait(&status); 
    /* I do know that it helps the shell from going off and doing its own thing while
    the the process being run is running, so there's that */
    return status;
}

int main() {
    int running = 1;
    while(running) {
    displayprompt();
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // removes trailing newline from fgets()
    if(strcmp(input, "exit") != 0) {
        runcmd(input);
    }
    else {running = 0;}
    }
    return 0;
}
