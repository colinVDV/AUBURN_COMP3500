/***************************************************************************************************************
Handler file for scheduler.c
****************************************************************************************************************/
#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

stats* fcfs_policy(task_t task_array[], stats stats_array[], int count);

stats* rr_policy(task_t task_array[], stats stats_array[], int finish_array[], int count, int time_quantum);

stats* srtf_policy(task_t task_array[], stats stats_array[], int finish_array[], int count);

stats* averageCalculator(stats stats_array[], int count);

#endif
