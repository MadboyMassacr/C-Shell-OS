#include<stdio.h>
#include <unistd.h>
#include<pwd.h>
#include<string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include<stdlib.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>

int compare(const void *a, const void *b);

void print_permissions(mode_t mode);

void peek(char* input, char* token1, char* token2, char* token3, char* token4, char* pwd, char* hwd) ;
