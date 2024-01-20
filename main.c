#include "header.h"


int main()
{
    char* pwd = getcwd(NULL, 0);
    char hwd[1024];
    getcwd(hwd, sizeof(hwd));
    int hwdlen = strlen(hwd);
    while(1)
    {
        char input[100]; // Assuming a maximum input length of 100 characters
        char *token;
        char input_cpy[256]; 
        prompt(hwd);
        fgets(input, sizeof(input), stdin);
        // Remove the newline character from the input
        if (input[strlen(input) - 1] == '\n') 
        {
            input[strlen(input) - 1] = '\0';
        }
        strcpy(input_cpy, input);
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
        else
        {
            int fun_len = strlen(input_cpy);
            sys_call(input_cpy, fun_len);
        }
    }
    
    
    
}