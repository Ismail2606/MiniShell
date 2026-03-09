#include "main.h"

char prompt[50] = "minishell$ ";
char input_string[100];
char *external_commands[100];

pid_t pid;
int status;

int main(void)
{
    /* Register signals */
    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);

    /* Load external commands */
    extract_external_commands(external_commands);

    system("clear");

   while (1)
    {
        printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, prompt);
        fflush(stdout);

        scan_input(input_string);

        if (input_string[0] == '\0')
            continue;

        if (strncmp(input_string, "PS1=", 4) == 0 && input_string[4] != '\0' && input_string[4] != ' ')
        {
            copy_change(prompt, input_string);
            continue;
        }

        char *cmd = get_command(input_string);
        int type = check_command_type(cmd);

        if (type == BUILTIN)
        {
            execute_internal_commands(input_string);
        }
        else if (type == EXTERNAL)
        {
            pid = fork();

            if (pid == 0)
            {
                // signal(SIGINT, SIG_DFL);
                // signal(SIGTSTP, SIG_DFL);
                execute_external_commands(input_string);
            }

            else
            {
                waitpid(pid, &status, WUNTRACED);

                if (WIFSTOPPED(status))
                {
                    insert_job(pid, input_string);  
                }

                pid = 0;
            }

        }
        else
        {
            printf("Command not found: %s\n", cmd);
        }

        free(cmd);
    }


    return 0;
}




