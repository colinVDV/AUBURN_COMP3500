/********************************************************************************************
* The file that contains all the sheduling policies.
* Takes an input from input.c, then sends data to computeState.c
********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

#define MAX_TIME 10000

stats* fcfs_policy(task_t task_array[], stats stats_array[], int count) {
    //Variables
    int process, burstCount, timeCount = 0;

    //Going through each single process
    for (process = 0; process < count; process++) {
        //Inserting waiting time for the current process
        stats_array[process].waiting_time = timeCount - task_array[process].arrival_time;
        stats_array[process].response_time = timeCount - task_array[process].arrival_time;
		
        //Releasing the process
        for (burstCount = 0; burstCount < task_array[process].burst_time; burstCount++) {
           printf("<time %d> process %d is running\n", timeCount, task_array[process].pid);
           timeCount = timeCount+1;
        }
        //Inserting turnaround time for the current process
        stats_array[process].turnaround_time = timeCount - task_array[process].arrival_time;
        printf("<time %d> process %d is finished...\n", timeCount, task_array[process].pid);
    }
    printf("<time %d> All processes finish ......\n", timeCount);

    return stats_array;
}

stats* rr_policy(task_t task_array[], stats stats_array[], int finish_array[], int count, int time_quantum) {
    //Variables
    int process, timeCount = 0, cont = 1, i;
    int remainingBurst[count];
    
    for (process = 0; process < count; process++) {
        remainingBurst[process] = task_array[process].burst_time;
    }

    while (cont == 1) {
        int done  = 1;
        for (process = 0; process < count; process++) {
            if (remainingBurst[process] > 0) {
                done = 0;
                if (remainingBurst[process] > time_quantum) {
                    printf("<time %d> process %d is running\n", (timeCount), task_array[process].pid);
                    for (i = 1; i < time_quantum; i++) {
                        printf("<time %d> process %d is running\n", (timeCount + i), task_array[process].pid);
                    }
                    timeCount = timeCount + time_quantum;
                    remainingBurst[process] = remainingBurst[process] - time_quantum;
                } else {
                    timeCount = timeCount + remainingBurst[process];
                    remainingBurst[process] = 0;
                    stats_array[process].waiting_time = timeCount - task_array[process].burst_time - task_array[process].arrival_time;
                    stats_array[process].response_time = timeCount - task_array[process].burst_time - task_array[process].arrival_time;
                    stats_array[process].turnaround_time = timeCount - task_array[process].arrival_time;
                }

                if (remainingBurst[process] == 0) {
                    printf("<time %d> process %d is finished...\n", timeCount, task_array[process].pid);
                }
            }

        }

        if (done == 1) {
            break;
        }
    }
    printf("<time %d> All processes finish ......\n", timeCount);

    return stats_array;
}

stats* srtf_policy(task_t task_array[], stats stats_array[], int finish_array[], int count) {
    //Variables
    int process, burstCount, timeCount = 0, complete = 0;
    int minTime = MAX_TIME, shortest = 0, check = 0;
    int remainingTime[count];

    for (process = 0; process < count; process++) {
        remainingTime[process] = task_array[process].burst_time;
    }

    while(complete != count) {
        for (process = 0; process < count; process++) {
            if ((task_array[process].arrival_time <= timeCount) && (remainingTime[process] > 0) && (remainingTime[process] < minTime)) {
                minTime = remainingTime[process];
                shortest = process;
                check = 1;
            }
        }

        if (check == 0) {
            timeCount++;
            continue;
        }

        remainingTime[shortest]--;
        minTime = remainingTime[shortest];
        if (minTime == 0) {
            minTime = MAX_TIME;
        }

        printf("<time %d> process %d is running\n", timeCount, task_array[shortest].pid);
        if (remainingTime[shortest] == 0) {
            printf("<time %d> process %d is finished...\n", timeCount, task_array[shortest].pid);
            complete++;
            check = 0;
            stats_array[shortest].waiting_time = timeCount - task_array[shortest].burst_time - task_array[shortest].arrival_time;
            stats_array[shortest].response_time = timeCount - task_array[shortest].burst_time - task_array[shortest].arrival_time;
            stats_array[shortest].turnaround_time = timeCount - task_array[shortest].arrival_time;
        }
        timeCount++;
    }
    printf("<time %d> All processes finish ......\n", timeCount);

    return stats_array;
}

stats* averageCalculator(stats stats_array[], int count) {
    //Variables
    int i;
    
    //Calculating and preparing average data
    int totalWaitingTime = 0, totalTurnaroundTime = 0, totalResponseTime = 0;
    for (i = 0; i < (count); i++) {
        totalWaitingTime = totalWaitingTime + stats_array[i].waiting_time;
        totalTurnaroundTime = totalTurnaroundTime + stats_array[i].turnaround_time;
        totalResponseTime = totalResponseTime + stats_array[i].response_time;
    }
    double averageWaitingTime = totalWaitingTime / count;
    double averageTurnaroundTime = totalTurnaroundTime / count;
    double averageResponseTime = totalResponseTime / count;
    stats_array[count + 1].waiting_time = averageWaitingTime;
    stats_array[count + 1].turnaround_time = averageTurnaroundTime;
    stats_array[count + 1].response_time = averageResponseTime;

    return stats_array;
}
