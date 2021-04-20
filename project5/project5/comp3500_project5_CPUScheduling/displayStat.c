/*********************************************************************************
* Display method
**********************************************************************************/

#include "input.h"

void displayStat(float averageWaitingTime, float averageTurnaroundTime, float averageResponseTime) {
    printf("==================================================================\n");    
    printf("Average waiting time=\t\t%f\n", averageWaitingTime);
    printf("Average response time=\t\t%f\n", averageResponseTime);
    printf("Average turnaround time=\t%f\n", averageTurnaroundTime);
    printf("Overall CPU usage=\t\t100.00\n");
    printf("==================================================================\n");
}
