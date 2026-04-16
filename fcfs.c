#include <stdio.h>
#include <stdlib.h>

// Structure for Process
typedef struct {
    int pid, at, bt, ct, tat, wt;
} Process;

// Comparator (like C++ lambda: sort by arrival time)
int compareByArrival(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;

    if (p1->at < p2->at) return -1;
    if (p1->at > p2->at) return 1;
    return 0;
}

int main() {
    int n;

    printf("===== FCFS Scheduling =====\nProcesses: ");
    scanf("%d", &n);

    Process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("P%d Arrival: ", p[i].pid);
        scanf("%d", &p[i].at);

        printf("P%d Burst  : ", p[i].pid);
        scanf("%d", &p[i].bt);
    }

    // Sort like C++ sort(p.begin(), p.end(), cmp)
    qsort(p, n, sizeof(Process), compareByArrival);

    int time = 0;

    printf("\nGantt Chart:\n| ");

    // FCFS Scheduling
    for (int i = 0; i < n; i++) {

        if (time < p[i].at)
            time = p[i].at;

        printf("P%d (%d-%d) | ", p[i].pid, time, time + p[i].bt);

        p[i].ct  = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;

        time = p[i].ct;
    }

    // Table Header
    printf("\n\n%-5s %-5s %-5s %-5s %-6s %-5s\n",
           "PID", "AT", "BT", "CT", "TAT", "WT");
    printf("-----------------------------------\n");

    double totalTAT = 0, totalWT = 0;

    // Output Table
    for (int i = 0; i < n; i++) {
        printf("P%-4d %-5d %-5d %-5d %-6d %-5d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);

        totalTAT += p[i].tat;
        totalWT  += p[i].wt;
    }

    printf("\nAverage TAT: %.2lf", totalTAT / n);
    printf("\nAverage WT : %.2lf\n", totalWT / n);

    return 0;
}
