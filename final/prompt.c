#include "prompt.h"

void prompt(char* hwd) 
{
    int hwdlen = strlen(hwd);
    char input[256];
    char input_cpy[256]; // Assuming a maximum input length of 100 characters
    char *token;
    char hostname[256];
    char cwd[1024]; 
    char* home = getenv("HOME");
    gethostname(hostname, sizeof(hostname));
    getcwd(cwd, sizeof(cwd));
    if(strcmp(cwd, hwd) == 0)
        printf("<%s@%s:~>", getpwuid(1000)->pw_name, hostname);
    else
    {
        int count = 0;
        while (count < hwdlen && cwd[count] == hwd[count]) 
        {
            count++;
        }
        if(count == hwdlen)
        {
            int len = strlen(cwd);
            char *relative_path = (char*)malloc(len - count + 1);
            for (int i = count; i < len; i++)
            {
                relative_path[i - count] = cwd[i];
            }
            printf("<%s@%s:~%s>", getpwuid(1000)->pw_name, hostname, relative_path);
        }
        else 
        {
            printf("<%s@%s:%s>", getpwuid(1000)->pw_name, hostname, cwd);
        }

    }
}
        
        
        