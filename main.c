#include "header.h"


int main()
{
    // make a copy of standard file input
    int std_in = dup(STDIN_FILENO);
    int std_out = dup(STDOUT_FILENO);
    char* pwd = getcwd(NULL, 0);
    char hwd[1024];
    getcwd(hwd, sizeof(hwd));
    int hwdlen = strlen(hwd);
    while(1)
    {
        char input[100];
        char input_main[100] ;// Assuming a maximum input length of 100 characters
        char *token;
        char input_cpy[256]; 
        prompt(hwd);
        fgets(input_main, sizeof(input_main), stdin);
        int count = 0;
        // Remove the newline character from the input
        if (input_main[strlen(input_main) - 1] == '\n') 
        {
            input_main[strlen(input_main) - 1] = '\0';
        }
        for(int i = 0; i < 100; i++)
        {
            if(input_main[i] == '&')
            {
                count++;
            }
        }
        // copy the input_main to a new variable named input_main_updated and replace all & with ;&
        char input_main_updated[100 + count];
        int j = 0;
        for(int i = 0; i < 100; i++)
        {
            if(input_main[i] == '&')
            {
                input_main_updated[j] = '&';
                j++;
                input_main_updated[j] = ';';
                j++;
            }
            else
            {
                input_main_updated[j] = input_main[i];
                j++;
            }
        }
        if (input_main_updated[strlen(input_main_updated) - 1] == '\n') 
        {
            input_main_updated[strlen(input_main_updated) - 1] = '\0';
        }
        char input_main_updated_cpy[100 + count];
        strcpy(input_main_updated_cpy, input_main_updated);

        // tokenise the input_main_updated and store it in input
        token = strtok(input_main_updated_cpy, ";");
        strcpy(input, token);
        int token_count = 0;

        while(input != NULL)
        {
            token_count++;
            strcpy(input_cpy, input);
            if(token[strlen(token) - 1] == '&')
            {
                pid_t child = fork();
                if(child < 0)
                {
                    printf("Error in forking\n");
                }
                else if(child == 0)
                {
                    // change the output from stdout to /dev/null
                    freopen("/dev/null", "w", stdout);
                    token = strtok(input, " ");
                    char cwdforwarp[1024];
                    

                    if(strcmp(token, "warp") == 0)
                    {
                        token = strtok(NULL, " ");
                        warp(token, pwd, hwd);
                    }
                    else if(strcmp(token, "peek") == 0)
                    {
                        char *tokens[4];
                        tokens[0] = token;
                        token = strtok(NULL, " ");
                        tokens[1] = token;
                        token = strtok(NULL, " ");
                        tokens[2] = token;
                        token = strtok(NULL, " ");
                        tokens[3] = token;


                        peek(input, tokens[0], tokens[1], tokens[2], tokens[3], pwd, hwd);
                    }
                    else if(strcmp(token, "proclore") == 0)
                    {
                        token = strtok(NULL, " ");
                        proclore(token);
                    }
                    else if(strcmp(token, "pastevents") == 0)
                    {
                        token = strtok(NULL, " ");
                        if(token == NULL)
                        {
                            pastevents();
                        }
                        else if(strcmp(token, "execute") == 0)
                        {
                            token = strtok(NULL, " ");
                            pastevents_execute(token, pwd, hwd);
                        }
                        else if(strcmp(token, "purge") == 0)
                        {
                            pastevents_purge();
                        }
                    }
                    else if(strcmp(token, "iMan") == 0)
                    {
                        token = strtok(NULL, " ");
                        if(token == NULL)
                        {
                            printf("No command specified\n");
                        }
                        else
                        {
                            iman(token);
                        }
                    }
                    else
                    {
                        int fun_len = strlen(input_cpy);
                        sys_call(input_cpy, fun_len);
                    }

                        exit(0);
                }
                else
                {
                    printf("%d\n", child);

                    int check = token_count;
                    check--;
                    strcpy(input_main_updated_cpy, input_main_updated);
                    token = strtok(input_main_updated_cpy, ";");
                    while(check > -1)
                    {
                        token = strtok(NULL, ";");
                        check--;
                    }
                    if(token != NULL)
                    {
                        strcpy(input, token);
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                int input_test = 0;
                int output_test = 0;
                for(int i = 0; i < strlen(input); i++)
                {
                    if(input[i] == '<')
                    {
                        input_test = 1;
                    }
                    if(input[i] == '>' && input[i + 1] == '>')
                    {
                        output_test = 2;
                        i++;
                    }
                    else if(input[i] == '>')
                    {
                        output_test = 1;
                    }
                }
                char* input_file;
                char* output_file;
                if(input_test == 0 && output_test == 0)
                {

                }
                else if(input_test == 1 && output_test == 0)
                {
                    // input redirection
                    token = strtok(input, "<");
                    token = strtok(NULL, "<");
                    input_file = strdup(token);
                    // open file descriptor
                    int fd = open(input_file, O_RDONLY);
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                    token = strtok(input, "<");
                    strcpy(input_cpy, token);
                }
                else if(input_test == 0 && output_test == 1)
                {
                    // output redirection
                    token = strtok(input, ">");
                    token = strtok(NULL, ">");
                    output_file = strdup(token);
                    // open file descriptor
                    int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    token = strtok(input, ">");
                    strcpy(input_cpy, token);
                }
                else if(input_test == 0 && output_test == 2)
                {
                    // output redirection but append mode
                    token = strtok(input, ">>");
                    token = strtok(NULL, ">>");
                    output_file = strdup(token);
                    // open file descriptor
                    int fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    token = strtok(input, ">>");
                    strcpy(input_cpy, token);
                }
                else if(input_test == 1 && output_test == 1)
                {
                    // input and output redirection
                    token = strtok(input, "<");
                    token = strtok(NULL, "<");
                    char token_nibba[256];
                    strcpy(token_nibba, token);
                    token = strtok(token_nibba, ">");
                    input_file = strdup(token);
                    // make the last character \0
                    int len = strlen(input_file);
                    input_file[len - 1] = '\0';
                    // open file descriptor
                    int fd = open(input_file, O_RDONLY);
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                    int nibba_len = strlen(token_nibba);
                    token_nibba[nibba_len] = '>';
                    token = strtok(token_nibba, ">");
                    token = strtok(NULL, ">");
                    output_file = strdup(token);
                    // open file descriptor
                    fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    token = strtok(input, ">");
                    strcpy(input_cpy, token);
                }
                else if(input_test == 1 && output_test == 2)
                {
                    // input and output redirection
                    token = strtok(input, "<");
                    token = strtok(NULL, "<");
                    char token_nibba[256];
                    strcpy(token_nibba, token);
                    token = strtok(token_nibba, ">>");
                    input_file = strdup(token);
                    // make the last character \0
                    int len = strlen(input_file);
                    input_file[len - 1] = '\0';
                    // open file descriptor
                    int fd = open(input_file, O_RDONLY);
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                    int nibba_len = strlen(token_nibba);
                    token_nibba[nibba_len] = '>';
                    token = NULL;
                    token = strtok(token_nibba, ">>");
                    token = strtok(NULL, ">>");
                    output_file = strdup(token);
                    // open file descriptor
                    fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    token = strtok(input, ">>");
                    strcpy(input_cpy, token);
                }

                token = strtok(input, " ");
                char cwdforwarp[1024];
                

                if(strcmp(token, "warp") == 0)
                {
                    token = strtok(NULL, " ");
                    warp(token, pwd, hwd);
                }
                else if(strcmp(token, "peek") == 0)
                {
                    char *tokens[4];
                    tokens[0] = token;
                    token = strtok(NULL, " ");
                    tokens[1] = token;
                    token = strtok(NULL, " ");
                    tokens[2] = token;
                    token = strtok(NULL, " ");
                    tokens[3] = token;


                    peek(input, tokens[0], tokens[1], tokens[2], tokens[3], pwd, hwd);
                }
                else if(strcmp(token, "proclore") == 0)
                {
                    token = strtok(NULL, " ");
                    proclore(token);
                }
                else if(strcmp(token, "pastevents") == 0)
                {
                    token = strtok(NULL, " ");
                    if(token == NULL)
                    {
                        pastevents();
                    }
                    else if(strcmp(token, "execute") == 0)
                    {
                        token = strtok(NULL, " ");
                        pastevents_execute(token, pwd, hwd);
                    }
                    else if(strcmp(token, "purge") == 0)
                    {
                        pastevents_purge();
                    }
                }
                else if(strcmp(token, "iMan") == 0)
                {
                    token = strtok(NULL, " ");
                    if(token == NULL)
                    {
                        printf("No command specified\n");
                    }
                    else
                    {
                        iman(token);
                    }
                }
                else if(strcmp(token, "neonate") == 0)
                {
                    token = strtok(NULL, " ");
                    token = strtok(NULL, " ");
                    neonate(token);
                }
                else if(strcmp(token, "activities") == 0)
                {
                    activities();
                }
                else if(strcmp(token, "fg") == 0)
                {
                    token = strtok(NULL, " ");
                    // check if token exists in /proc
                    DIR *dir;
                    struct dirent *entry;
                    // open proc directory
                    dir = opendir("/proc");
                    int pid_exists = 0;
                    while ((entry = readdir(dir)) != NULL) {
                        if (atoi(entry->d_name) == atoi(token)) {
                            pid_exists = 1;
                            break;
                        }
                    }
                    closedir(dir);
                    // if pid does not exists then print so
                    if(pid_exists == 0)
                    {
                        printf("No such process exists\n");
                    }
                    else
                    {

                    }     
                }
                else if(strcmp(token, "bg") == 0)
                {
                    token = strtok(NULL, " ");
                    // check if token exists in /proc
                    DIR *dir;
                    struct dirent *entry;
                    // open proc directory
                    dir = opendir("/proc");
                    int pid_exists = 0;
                    while ((entry = readdir(dir)) != NULL) {
                        if (atoi(entry->d_name) == atoi(token)) {
                            pid_exists = 1;
                            break;
                        }
                    }
                    closedir(dir);
                    // if pid does not exists then print so
                    if(pid_exists == 0)
                    {
                        printf("No such process exists\n");
                    }
                    else
                    {
                        // run the process in background
                        pid_t child = fork();
                        if(child == 0)
                        {
                            // change the output from stdout to /dev/null
                            freopen("/dev/null", "w", stdout);
                            // run the process
                            token = strtok(input_cpy, " ");
                            char* args[100];
                            int i = 0;
                            char* token_cpy = strdup(token);
                            while (token != NULL) {
                                args[i++] = token;
                                token = strtok(NULL, " ");
                            }
                            args[i] = NULL;

                            // Execute the command
                            if (execvp(args[0], args) == -1) {
                                // perror("execvp");
                                exit(EXIT_FAILURE);
                            }
                        }

                    }

                }
                else
                {
                    int fun_len = strlen(input_cpy);
                    sys_call(input_cpy, fun_len);
                }

                int check = token_count;
                check--;
                strcpy(input_main_updated_cpy, input_main_updated);
                token = strtok(input_main_updated_cpy, ";");
                while(check > -1)
                {
                    token = strtok(NULL, ";");
                    check--;
                }
                if(token != NULL)
                {
                    strcpy(input, token);
                }
                else
                {
                    break;
                }
            }
        }
        // retyrn the input to stdin
        dup2(std_in, STDIN_FILENO);
        // change output back to stdout
        dup2(std_out, STDOUT_FILENO);
    
    }
}
