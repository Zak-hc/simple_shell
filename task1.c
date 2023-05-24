#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 100
extern char **environ;

void display_prompt()
{
char prompt[] = "#cisfun$ ";
write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
}

void execute_command(char *command)
{   int i;
    char* envp[2] = {"PATH=/bin:/usr/bin", NULL};
    char **env;
    pid_t pid;
    char *args[MAX_COMMAND_LENGTH / 2 + 1];
    char *token = strtok(command, " ");
    i = 0;
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;  
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
      
    }
    else if (strcmp(args[0], "env") == 0)
    {
        env = environ;
        while (*env) {
            size_t len = strlen(*env);
            write(STDOUT_FILENO, *env, len);
            write(STDOUT_FILENO, "\n", 1);
            env++;
        }
        return;
    }
    
    else if (pid == 0) {
        args[0] = command;
        args[1] = NULL;
        execve(command, args, envp);
        perror("execv");
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}

int main()
{
    char command[MAX_COMMAND_LENGTH];
    int i;
    char v[5] = "exit";
    while (1) {            
        display_prompt();

        if (fgets(command, sizeof(command), stdin) == NULL) {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }
        for (i = 0; command[i] != '\0'; i++)
	{}
        if (command[i - 1] == '\n') {
            command[i - 1] = '\0';
        }
        for (i = 0; v[i] != '\0'; i++)
	{
	if (command[i] != v[i])
	break;
	}
	if (i == 4 && command[i] == '\0')
	{
            break;
        }
        execute_command(command);
    }

    return 0;
}
