/*
 * Header file for input.c
*/

#ifndef _INPUT_H_
#define _INPUT_H_

typedef unsigned int u_int;

typedef struct task {
	u_int pid;
	u_int arrival_time;
	u_int burst_time;
} task_t;

typedef struct stat {
	int waiting_time;
	int turnaround_time;
	int response_time;
} stats;

#endif
