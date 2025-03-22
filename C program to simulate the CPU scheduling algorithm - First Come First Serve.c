#include <stdio.h>
#include <stdlib.h>
struct Process
{
    int pid, at, bt, ct, tat, wt;
};
int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("P%d Arrival & Burst Time: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].at > p[j + 1].at)
            {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
    int time = 0;
    for (int i = 0; i < n; i++)
    {
        time = (time < p[i].at) ? p[i].at : time;
        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        time = p[i].ct;
    }
    printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at,
               p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++)
    {
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
    }
    printf("\nAvg TAT: %.2f\nAvg WT: %.2f\n", avg_tat / n, avg_wt / n);
    return 0;
}
