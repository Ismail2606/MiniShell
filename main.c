#include"main.h"

Job *job_head = NULL;

void insert_job(pid_t pid, char *input_string)
{
    Job *new = malloc(sizeof(Job));
    if (new == NULL)
        return;

    new->pid = pid;
    strcpy(new->command, input_string);

    new->next = job_head;
    job_head = new;
}


void display_jobs(void)
{
    Job *temp = job_head;
    if(temp == NULL)
    {
        printf("No jobs\n");
        return;
    }
    printf("Jobs List:\n");
    while (temp)
    {
        printf("[%d] %s\n", temp->pid, temp->command);
        temp = temp->next;
    }
}


void fg_job(void)
{
    if (job_head == NULL)
    {
        printf("fg: no jobs\n");
        return;
    }
    
    Job *temp = job_head;
    job_head = job_head->next;

    kill(temp->pid, SIGCONT);
    pid = temp->pid;
    printf("%d %s\n", temp->pid, temp->command);
    waitpid(temp->pid, &status, WUNTRACED);

    free(temp);
    pid = 0;
}

void bg_job(void)
{
    if (job_head == NULL)
    {
        printf("bg: no jobs\n");
        return;
    }

    kill(job_head->pid, SIGCONT);

    printf("Running %s &\n", job_head->command);
}

