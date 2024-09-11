#include <stdio.h>

#define MAX_PROCESSES 100

// Function prototypes
void roundRobinScheduling(int burstTimes[], int arrivalTimes[], int numProcesses, int quantum);

int main() {
    int burstTimes[MAX_PROCESSES];
    int arrivalTimes[MAX_PROCESSES];
    int numProcesses, quantum;

    // Input number of processes and time quantum
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    if (numProcesses > MAX_PROCESSES) {
        printf("Number of processes exceeds maximum limit of %d.\n", MAX_PROCESSES);
        return 1;
    }

    printf("Enter the arrival times of the processes:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &arrivalTimes[i]);
    }

    printf("Enter the burst times of the processes:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &burstTimes[i]);
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    // Perform Round Robin Scheduling
    roundRobinScheduling(burstTimes, arrivalTimes, numProcesses, quantum);

    return 0;
}

void roundRobinScheduling(int burstTimes[], int arrivalTimes[], int numProcesses, int quantum) {
    int remainingTimes[MAX_PROCESSES];
    int completionTimes[MAX_PROCESSES];
    int turnaroundTimes[MAX_PROCESSES];
    int waitingTimes[MAX_PROCESSES];
    int time = 0;
    int completedProcesses = 0;
    int i;
    float totalWaitingTime = 0;
    float totalTurnaroundTime = 0;

    // Initialize remaining times and other arrays
    for (i = 0; i < numProcesses; i++) {
        remainingTimes[i] = burstTimes[i];
        completionTimes[i] = 0;
        waitingTimes[i] = 0;
        turnaroundTimes[i] = 0;
    }

    while (completedProcesses < numProcesses) {
        int allDone = 1;

        for (i = 0; i < numProcesses; i++) {
            if (remainingTimes[i] > 0 && arrivalTimes[i] <= time) {
                allDone = 0; // At least one process is not done

                if (remainingTimes[i] > quantum) {
                    // Process will be executed for 'quantum' time units
                    remainingTimes[i] -= quantum;
                    time += quantum;
                } else {
                    // Process will be finished in this cycle
                    time += remainingTimes[i];
                    completionTimes[i] = time;
                    turnaroundTimes[i] = completionTimes[i] - arrivalTimes[i];
                    waitingTimes[i] = turnaroundTimes[i] - burstTimes[i];
                    remainingTimes[i] = 0;
                    completedProcesses++;
                    printf("Process %d finished at time %d\n", i + 1, time);
                }
            }
        }

        if (allDone) {
            break; // All processes are done
        }
    }

    // Calculate average waiting time and turnaround time
    for (i = 0; i < numProcesses; i++) {
        totalWaitingTime += waitingTimes[i];
        totalTurnaroundTime += turnaroundTimes[i];
    }
    float averageWaitingTime = totalWaitingTime / numProcesses;
    float averageTurnaroundTime = totalTurnaroundTime / numProcesses;

    // Print the results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < numProcesses; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrivalTimes[i], burstTimes[i], completionTimes[i], turnaroundTimes[i], waitingTimes[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", averageWaitingTime);
    printf("Average Turnaround Time: %.2f\n", averageTurnaroundTime);
}


/*Number of processes: 5
Arrival times: [0, 1, 2, 3, 4]
Burst times: [8, 4, 3, 7, 6]
Time quantum: 4*/
