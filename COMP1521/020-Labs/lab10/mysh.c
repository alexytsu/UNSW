// mysh.c ... a very simple shell
// Started by John Shepherd, October 2017
// Completed by Alexander Su, May 2018

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

extern char *strdup(char *);
void trim(char *);
char **tokenise(char *, char *);
void freeTokens(char **);
int isExecutable(char *);
void execute(char **, char **, char **);

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;   // pid of child process
 //  int stat;    // return status of child
    char **path; // array of directory names

   // set up command PATH from environment variable
   int i;
   for (i = 0; envp[i] != NULL; i++) {
      if (strncmp(envp[i], "PATH", 4) == 0) break;
   }
   if (envp[i] == NULL){
      path = tokenise("/bin:/usr/bin",":");
   }
   else{
      // &envp[i][5] ignores "PATH="
      path = tokenise(&envp[i][5],":");
    }

   // main loop: print prompt, read line, execute command
    char line[BUFSIZ];
    printf("mysh$ ");
    while (fgets(line, BUFSIZ, stdin) != NULL) {
        trim(line); // remove leading/trailing space
        if (strcmp(line,"exit") == 0) break;
        if (strcmp(line,"") == 0) { printf("mysh$ "); continue; }

        pid = fork();
        if(pid == 0){
            //child process
             char **commands = tokenise(line, " ");
             execute(commands, path, envp);
        }else if (pid > 0){
            // parent process
             waitpid(pid, NULL, 0);
             printf("mysh$ ");
        }else{
         // child process not created (error)
        }


        }
        return(EXIT_SUCCESS);
}

// execute: run a program, given command-line args, path and envp
void execute(char **args, char **path, char **envp)
{
    // TODO: implement the find-the-executable and execve() it code
    char *command = args[0];
    if(command[0] == '/' ||command[0] == '.'){
        if(isExecutable(command)){
            printf("Executing %s\n", command);
            if(-1 == execve(command, args, envp)){
                perror("Exec failed");
                exit(1);
            }
            exit(0);
        }
    }else{
        for(int i = 0; path[i] != NULL; i ++){
            char *execpath = strcat(path[i], "/");
            execpath = strcat(execpath, command);
            if(isExecutable(execpath)){
                printf("Executing %s\n", execpath);
                if(-1 == execve(execpath, args, envp)){
                    perror("Exec failed");
                    exit(1);
                }
                exit(0);
            }
        }
    }
    printf("%s: Command not found\n", command);
    exit(1);
}

// isExecutable: check whether this process can execute a file
int isExecutable(char *cmd)
{
   struct stat s;
   // must be accessible
   if (stat(cmd, &s) < 0)
      return 0;
   // must be a regular file
   //if (!(s.st_mode & S_IFREG))
   if (!S_ISREG(s.st_mode))
      return 0;
   // if it's owner executable by us, ok
   if (s.st_uid == getuid() && s.st_mode & S_IXUSR)
      return 1;
   // if it's group executable by us, ok
   if (s.st_gid == getgid() && s.st_mode & S_IXGRP)
      return 1;
   // if it's other executable by us, ok
   if (s.st_mode & S_IXOTH)
      return 1;
   return 0;
}

// tokenise: split a string around a set of separators
// create an array of separate strings
// final array element contains NULL
char **tokenise(char *str, char *sep)
{
   // temp copy of string, because strtok() mangles it
   char *tmp;
   // count tokens
   tmp = strdup(str);
   int n = 0;
   strtok(tmp, sep); n++;
   while (strtok(NULL, sep) != NULL) n++;
   free(tmp);
   // allocate array for argv strings
   char **strings = malloc((n+1)*sizeof(char *));
   assert(strings != NULL);
   // now tokenise and fill array
   tmp = strdup(str);
   char *next; int i = 0;
   next = strtok(tmp, sep);
   strings[i++] = strdup(next);
   while ((next = strtok(NULL,sep)) != NULL)
      strings[i++] = strdup(next);
   strings[i] = NULL;
   free(tmp);
   return strings;
}

// freeTokens: free memory associated with array of tokens
void freeTokens(char **toks)
{
   for (int i = 0; toks[i] != NULL; i++)
      free(toks[i]);
   free(toks);
}

// trim: remove leading/trailing spaces from a string
void trim(char *str)
{
   int first, last;
   first = 0;
   while (isspace(str[first])) first++;
   last  = strlen(str)-1;
   while (isspace(str[last])) last--;
   int i, j = 0;
   for (i = first; i <= last; i++) str[j++] = str[i];
   str[j] = '\0';
}
