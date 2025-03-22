#include <stdio.h>

struct P
{
    int id, at, bt, rt, ct, tat, wt;
};

int main()
{
    int n, q;
    printf("Enter number of processes & Time Quantum: ");
    scanf("%d %d", &n, &q);
    struct P p[n];

    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        printf("Enter P%d Arrival Time & Burst Time: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
    }

    int t = 0, c = 0, flag;

    while (c < n)
    {
        flag = 0;  // Flag to check if any process was executed in this iteration

        for (int i = 0; i < n; i++)
        {
            if (p[i].rt > 0 && p[i].at <= t)
            {
                flag = 1;  // A process got executed
                int et = (p[i].rt > q) ? q : p[i].rt;
                t += et;
                p[i].rt -= et;

                if (p[i].rt == 0)
                {
                    c++;
                    p[i].ct = t;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                }
            }
        }

        // If no process was executed, increment time (idle CPU case)
        if (!flag)
            t++;
    }

    printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);

    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++)
    {
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
    }

    printf("\nAvg TAT: %.2f\nAvg WT: %.2f\n", avg_tat / n, avg_wt / n);

    return 0;
}
