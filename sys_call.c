#include "header.h"

void sys_call(char* input_cpy, int fun_len)
{
    if(input_cpy[fun_len - 1] != '&')
            {
                int result = system(input_cpy);
            }
            else
            {
                input_cpy[fun_len - 1] = '\0';
                pid_t child = fork();
                if(child == 0)
                {
                    freopen("/dev/null", "w", stdout);
                    int result = system(input_cpy);
                    exit(0);
                }
                else if(child < 0)
                {
                    printf("Error in forking\n");
                }
                else
                {
                    printf("%d\n", child);
                }
            }
}