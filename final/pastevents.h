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

struct CircularQueue {
    char data[15][255];
    int front;
    int rear;
    int size;
};
void initQueue(struct CircularQueue *queue);
int isFull(struct CircularQueue *queue);
void enqueue(struct CircularQueue *queue, const char *item);
void pastevents_append(char* input);
void pastevents();
void pastevents_execute(char* token, char* pwd, char* hwd);
void pastevents_purge();