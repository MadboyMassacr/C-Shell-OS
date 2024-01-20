#include "warp.h"

void warp(char* token, char* pwd, char* hwd)
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    
    if(token == NULL)
    {
        if(strcmp(cwd, pwd) == 0)
        {
            chdir(getpwuid(1000)->pw_dir);
            printf("%s\n", getcwd(NULL, 0));
            getcwd(cwd, sizeof(cwd));
        }
        else
        {
            chdir(getpwuid(1000)->pw_dir);
            printf("%s\n", getcwd(NULL, 0));
            strcpy(pwd, cwd);
            getcwd(cwd, sizeof(cwd));
           
        }
    }
    else if(strcmp(token, ".") == 0)
    {
        printf("%s\n", getcwd(NULL, 0));
    }
    else if(strcmp(token, "..") == 0)
    {
        chdir("..");
        printf("%s\n", getcwd(NULL, 0));
        if(strcmp(cwd, pwd) == 0)
        {
            getcwd(cwd, sizeof(cwd));
        }
        else
        {
            strcpy(pwd, cwd);
            getcwd(cwd, sizeof(cwd));
           
        }
    }
    else if(strcmp(token, "~") == 0)
    {
        if(strcmp(cwd, pwd) == 0)
        {
            chdir(hwd);
            printf("%s\n", getcwd(NULL, 0));
            getcwd(cwd, sizeof(cwd));
        }
        else
        {
            chdir(hwd);
            printf("%s\n", getcwd(NULL, 0));
            strcpy(pwd, cwd);
            getcwd(cwd, sizeof(cwd));
           
        }
    }
    else if(strcmp(token, "-") == 0)
    {
        if(strcmp(cwd, pwd) == 0)
        {
            printf("No previous directory\n");
        }
        else
        {
            chdir(pwd);
            printf("%s\n", getcwd(NULL, 0));
            strcpy(pwd, cwd);
            getcwd(cwd, sizeof(cwd));
        }
       
    }
    else if (token[0] == '.' && token[1] == '/')
    {
        if(strcmp(cwd, pwd) == 0)
        {
            // make a copy of token from index 2 to end
            char *newtoken = (char*)malloc(strlen(token) - 1);
            for (int i = 2; i < strlen(token); i++)
            {
                newtoken[i - 2] = token[i];
            }
            chdir(newtoken);
            printf("%s\n", getcwd(NULL, 0));
            getcwd(cwd, sizeof(cwd));
        }
        else
        {
            char *newtoken = (char*)malloc(strlen(token) - 1);
            for (int i = 2; i < strlen(token); i++)
            {
                newtoken[i - 2] = token[i];
            }
            chdir(newtoken);
            printf("%s\n", getcwd(NULL, 0));
            strcpy(pwd, cwd);
            getcwd(cwd, sizeof(cwd));
           
        }
    }
    else if (&token[0] == "." && &token[1] == "." && &token[2] == "/")
    {
        if(strcmp(cwd, pwd) == 0)
        {
            chdir("..");
            char *newtoken = (char*)malloc(strlen(token) - 1);
            for (int i = 2; i < strlen(token); i++)
            {
                newtoken[i - 2] = token[i];
            }
            chdir(newtoken);
            printf("%s\n", getcwd(NULL, 0));
            getcwd(cwd, sizeof(cwd));
        }
        else
        {
            chdir("..");
            char *newtoken = (char*)malloc(strlen(token) - 1);
            for (int i = 2; i < strlen(token); i++)
            {
                newtoken[i - 2] = token[i];
            }
            chdir(newtoken);
            printf("%s\n", getcwd(NULL, 0));
            strcpy(pwd, cwd);
            getcwd(cwd, sizeof(cwd));
           
        }
    }
    else if (token[0] == '~' && token[1] == '/')
    {
        if(strcmp(cwd, pwd) == 0)
        {
            chdir(hwd);
            char *newtoken = (char*)malloc(strlen(token) - 1);
            for (int i = 2; i < strlen(token); i++)
            {
                newtoken[i - 2] = token[i];
            }
            chdir(newtoken);
            printf("%s\n", getcwd(NULL, 0));
            getcwd(cwd, sizeof(cwd));
        }
        else
        {
            chdir(hwd);
            char *newtoken = (char*)malloc(strlen(token) - 1);
            for (int i = 2; i < strlen(token); i++)
            {
                newtoken[i - 2] = token[i];
            }
            chdir(newtoken);
            printf("%s\n", getcwd(NULL, 0));
            strcpy(pwd, cwd);
            getcwd(cwd, sizeof(cwd));
           
        }
    }
    else if (token[0] == '-' && token[1] == '/')
    {
        if(strcmp(cwd, pwd) == 0)
        {
            printf("No previous directory\n");
        }
        else
        {
            chdir(pwd);
            char *newtoken = (char*)malloc(strlen(token) - 1);
            for (int i = 2; i < strlen(token); i++)
            {
                newtoken[i - 2] = token[i];
            }
            chdir(newtoken);
            printf("%s\n", getcwd(NULL, 0));
            strcpy(pwd, cwd);
            getcwd(cwd, sizeof(cwd));
        }
    }
    else
    {
        if(strcmp(cwd, pwd) == 0)
        {
            chdir(token);
            printf("%s\n", getcwd(NULL, 0));
            getcwd(cwd, sizeof(cwd));
        }
        else
        {
            chdir(token);
            printf("%s\n", getcwd(NULL, 0));
            strcpy(pwd, cwd);
            getcwd(cwd, sizeof(cwd));
           
        }

    }
    token = strtok(NULL, " ");
    if(token != NULL)
    {
        if(strcmp(cwd, pwd) == 0)
        {
            chdir(token);
            printf("%s\n", getcwd(NULL, 0));
            getcwd(cwd, sizeof(cwd));
        }
        else
        {
            chdir(token);
            printf("%s\n", getcwd(NULL, 0));
            strcpy(pwd, cwd);
            getcwd(cwd, sizeof(cwd));
           
        }
    }
    return;
}
