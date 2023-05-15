#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

#define MAX_COMMAND_LENGTH 100

void display_prompt() {
    char prompt[] = "#cisfun$ ";
    write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
}

void execute_command(char *command)
{
    char *token = strtok(command, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;  
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        char *args[MAX_COMMAND_LENGTH / 2 + 1];
        args[0] = command;
        args[1] = NULL;
        execv(command, args);
        perror("execv");
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
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

