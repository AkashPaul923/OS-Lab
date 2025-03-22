#include <stdio.h>
int main()
{
    int n, m;
    printf("Processes & Resources: ");
    scanf("%d %d", &n, &m);
    int avail[m], max[n][m], alloc[n][m], need[n][m];
    printf("Available: ");
    for (int j = 0; j < m; j++)
        scanf("%d", &avail[j]);
    printf("Max: ");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    printf("Alloc: ");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }
    int finish[n], safe[n], count = 0;
    for (int i = 0; i < n; i++)
        finish[i] = 0;
    while (count < n)
    {
        int found = 0;
        for (int i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int can_finish = 1;
                for (int j = 0; j < m; j++)
                    if (need[i][j] > avail[j])
                    {
                        can_finish = 0;
                        break;
                    }
                if (can_finish)
                {
                    for (int j = 0; j < m; j++)
                        avail[j] += alloc[i][j];
                    finish[i] = 1;
                    safe[count++] = i;
                    found = 1;
                    break;
                }
            }
        }
        if (!found)
        {
            printf("Unsafe state!\n");
            return 0;
        }
    }
    printf("Safe sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safe[i]);
    printf("\n");
    return 0;
}


/*Processes & Resources: 5 3
Available: 3 3 2
Max:
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
Alloc:
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

