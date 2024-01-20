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
#include "peek.h"
#include "warp.h"
#include "proclore.h"
#include "prompt.h"

void sys_call(char* input_cpy, int fun_len);