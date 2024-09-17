#include<stdio.h>
int main()
{
    int n;
    float avg_wt = 0, avg_tat = 0; // Variables to store average values
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int b[n], w[n], t[n]; // Arrays for Burst Time, Waiting Time, Turnaround Time

    printf("Enter the Burst Time for each process: \n");
    for(int i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        scanf("%d", &b[i]);
    }

    // Calculating Waiting Time and Turnaround Time
    for(int i = 0; i < n; i++)
    {
        if(i == 0)
        {
            w[i] = 0;
            t[i] = b[i];
        }
        else
        {
            w[i] = t[i-1];
            t[i] = b[i] + w[i];
        }
    }

    // Printing the process details and calculating averages
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\n", i+1, b[i], w[i], t[i]);
        avg_wt += w[i];
        avg_tat += t[i];
    }

    // Calculating the average waiting and turnaround time
    avg_wt /= n;
    avg_tat /= n;

    // Printing the average waiting time and turnaround time
    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);

    return 0;
}
