#include "main.h"

void extract_external_commands(char **external_commands)
{
    FILE *fp = fopen("external_cmds.txt", "r");
    char buffer[50];
    int i = 0;

    if (fp == NULL)
    {
        perror("fopen");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp))
    {
        buffer[strcspn(buffer, "\n")] = '\0';

        external_commands[i] = malloc(strlen(buffer) + 1);
        strcpy(external_commands[i], buffer);
        i++;
    }

    external_commands[i] = NULL;
    fclose(fp);
}

int check_command_type(char *command)
{
    extern char *builtins[];
    extern char *external_commands[];

    for (int i = 0; builtins[i]; i++)
    {
        if (strcmp(command, builtins[i]) == 0)
            return BUILTIN;
    }

    // for (int i = 0; external_commands[i]; i++)
    // {
    //     if (strcmp(command, external_commands[i]) == 0)
    //         return EXTERNAL;
    // }
    
    return EXTERNAL; // Default to EXTERNAL if not found
}

void execute_internal_commands(char *input_string)
{
    if (strcmp(input_string, "jobs") == 0)
    {
        // printf("Jobs list:\n");
        display_jobs();
        
        return;
    }

    if (strcmp(input_string, "fg") == 0)
    {
        fg_job();
        return;
    }

    if (strcmp(input_string, "bg") == 0)
    {
        bg_job();
        return;
    }
    if (strcmp(input_string, "exit") == 0)
    {
        exit(0);
    }

    

    if (strcmp(input_string, "pwd") == 0)
    {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
        return;
    }

    if (strncmp(input_string, "cd", 2) == 0)
    {
        char *path = strtok(input_string, " ");
        path = strtok(NULL, " ");

        if (path == NULL)
        {
            path = getenv("HOME");
        }
        if (chdir(path) != 0)
        {
            perror("chdir");
        }
        return;
    }
    if (strncmp(input_string, "echo", 4) == 0)
    {
        echo(input_string, status);
        return;
    }
}
void scan_input(char *input_string)
{
    if (fgets(input_string, 100, stdin) == NULL)
        return;

    input_string[strcspn(input_string, "\n")] = '\0';
}

char *get_command(char *input_string)
{
    char *cmd;
    int i = 0;

    cmd = malloc(100);
    if (cmd == NULL)
        return NULL;

    /* Copy only first word */
    while (input_string[i] != ' ' && input_string[i] != '\0')
    {
        cmd[i] = input_string[i];
        i++;
    }

    cmd[i] = '\0';
    return cmd;
}

void copy_change(char *prompt, char *input_string)
{
    if (strncmp(input_string, "PS1=", 4) != 0)
        return;

    char *new_prompt = input_string + 4;

    if (*new_prompt == '\0')
        return;

    strcpy(prompt, new_prompt);
}

void signal_handler(int sig)
{
    if (pid > 0)
    {
        kill(pid, sig);
    }
}

void execute_external_commands(char *input_string)
{
    char *args[10];
    int i = 0;

    args[i] = strtok(input_string, " ");
    while (args[i] != NULL)
    {
        args[++i] = strtok(NULL, " ");
    }

    execvp(args[0], args);
    perror("execvp");
    exit(1);
}


 /*check for echo
       echo $SHELL ->getenv("SHELL")
       echo $? ->print status of last process
       echo $$ ->print initial pid of minishell using getpid()
       */
void echo(char *input_string, int status)
{
    char *token = strtok(input_string, " ");
    token = strtok(NULL, " ");

    while (token != NULL)
    {
        if (strcmp(token, "$?") == 0)
        {
            printf("Status %d ", WEXITSTATUS(status));
        }
        else if (strcmp(token, "$$") == 0)
        {
            printf("PID %d ", getpid());
        }
        else if (token[0] == '$')
        {
            char *env_var = getenv(token + 1);
            if (env_var != NULL)
            {
                printf("%s ", env_var);
            }
        }
        else
        {
            printf("%s ", token);
        }
        token = strtok(NULL, " ");
    }
    printf("\n");
}
