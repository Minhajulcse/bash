#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    int pid; // Process ID
    int at;  // Arrival Time
    int bt;  // Burst Time
    int ct;  // Completion Time
    int tat; // Turnaround Time
    int wt;  // Waiting Time
};

// Comparator to sort primarily by Arrival Time, then by PID
bool compareArrival(const Process& a, const Process& b) {
    if (a.at == b.at) return a.pid < b.pid;
    return a.at < b.at;
}

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
    }

    // Step 1: Sort by Arrival Time
    sort(p.begin(), p.end(), compareArrival);

    int currentTime = 0;
    double totalTAT = 0, totalWT = 0;

    // Step 2: Calculate times
    for (int i = 0; i < n; i++) {
        // If the CPU is idle, jump time forward to the next arrival
        if (currentTime < p[i].at) {
            currentTime = p[i].at;
        }

        p[i].ct = currentTime + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        currentTime = p[i].ct; // Move time forward
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    // Step 3: Print Output
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