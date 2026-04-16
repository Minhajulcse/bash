#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>

using namespace std;

struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    bool completed; // Track if the process is done
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "P" << p[i].pid << " AT: ";
        cin >> p[i].at;
        cout << "P" << p[i].pid << " BT: ";
        cin >> p[i].bt;
        p[i].completed = false; 
    }

    int currentTime = 0;
    int completedCount = 0;
    double totalTAT = 0, totalWT = 0;

    // Step 1: Run until all processes are finished
    while (completedCount < n) {
        int idx = -1;
        int minBT = INT_MAX;

        // Step 2: Find the shortest job that has already arrived
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= currentTime) {
                if (p[i].bt < minBT) {
                    minBT = p[i].bt;
                    idx = i;
                }
                // Standard tie-breaker: If burst times are equal, pick the one that arrived first
                else if (p[i].bt == minBT) {
                    if (p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        // Step 3: Execute the process
        if (idx != -1) {
            currentTime += p[idx].bt;
            p[idx].ct = currentTime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            
            p[idx].completed = true;
            completedCount++;
            
            totalTAT += p[idx].tat;
            totalWT += p[idx].wt;
        } 
        else {
            // No process has arrived yet, so the CPU sits idle for 1 time unit
            currentTime++;
        }
    }

    // Step 4: Print Output
    cout << "\n" << left << setw(5) << "PID" << setw(5) << "AT" << setw(5) << "BT" 
         << setw(5) << "CT" << setw(6) << "TAT" << setw(5) << "WT\n";
    cout << string(31, '-') << "\n";

    for (int i = 0; i < n; i++) {
        cout << left << setw(5) << ("P" + to_string(p[i].pid)) << setw(5) << p[i].at 
             << setw(5) << p[i].bt << setw(5) << p[i].ct << setw(6) << p[i].tat 
             << setw(5) << p[i].wt << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage TAT: " << totalTAT / n;
    cout << "\nAverage WT : " << totalWT / n << "\n";

    return 0;
}