#include <stdio.h>
#include <limits.h>

struct process {
    int pid;        // Process ID
    int bt;         // Burst Time
    int at;         // Arrival Time
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
    int completed;  // Completion status (0 = not completed, 1 = completed)
};

// Function to sort processes by arrival time
void sortByArrivalTime(struct process p[], int n) {
    struct process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

// Function to find the next process with the shortest burst time that has arrived
int findNextProcess(struct process p[], int n, int currentTime) {
    int shortest = -1;
    int minBurstTime = INT_MAX; // Set to maximum possible value

    for (int i = 0; i < n; i++) {
        if (p[i].at <= currentTime && p[i].completed == 0) { // Only consider processes that have arrived
            if (p[i].bt < minBurstTime) {
                minBurstTime = p[i].bt;
                shortest = i;
            }
        }
    }
    return shortest;
}

// Function to calculate waiting time for each process
void calculateWaitingTime(struct process p[], int n) {
    int currentTime = 0; // Track the current time in the CPU
    int completedProcesses = 0;

    while (completedProcesses < n) {
        int idx = findNextProcess(p, n, currentTime);

        if (idx == -1) {
            // No process has arrived yet, move time forward
            currentTime++;
        } else {
            // Process the next available shortest burst time process
            p[idx].wt = currentTime - p[idx].at;
            if (p[idx].wt < 0) {
                p[idx].wt = 0; // No negative waiting times
            }
            currentTime += p[idx].bt; // Move time forward by the burst time
            p[idx].completed = 1; // Mark the process as completed
            completedProcesses++;
        }
    }
}

// Function to calculate turnaround time for each process
void calculateTurnaroundTime(struct process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].bt + p[i].wt;
    }
}

// Function to print the results
void printResults(struct process p[], int n) {
    float totalWT = 0, totalTAT = 0;
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }
    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
}

int main() {
    int n;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    // Input details of each process
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].completed = 0; // Initially, no process is completed
        printf("Enter Arrival Time for Process P%d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time for Process P%d: ", i + 1);
        scanf("%d", &p[i].bt);
    }

    // Sort the processes by arrival time
    sortByArrivalTime(p, n);

    // Calculate waiting time and turnaround time
    calculateWaitingTime(p, n);
    calculateTurnaroundTime(p, n);

    // Print results
    printResults(p, n);

    return 0;
}