#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
using namespace std;

struct Process {
    int pid, at, bt, ct, tat, wt;
};

int main() {

    int n;
    cout << "===== FCFS Scheduling =====\nProcesses: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        cout << "P" << p[i].pid << " Arrival: ";
        cin >> p[i].at;

        cout << "P" << p[i].pid << " Burst  : ";
        cin >> p[i].bt;
    }

    // Sort by arrival time
    sort(p.begin(), p.end(), [](const Process &a, const Process &b) {
        return a.at < b.at;
    });

    int time = 0;

    cout << "\nGantt Chart:\n| ";

    // FCFS Scheduling
    for (int i = 0; i < n; i++) {

        if (time < p[i].at)
            time = p[i].at;

        cout << "P" << p[i].pid
             << " (" << time
             << "-" << time + p[i].bt
             << ") | ";

        p[i].ct  = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;

        time = p[i].ct;
    }

    // Table Header
    cout << "\n\n"
         << left << setw(5) << "PID"
         << setw(5) << "AT"
         << setw(5) << "BT"
         << setw(5) << "CT"
         << setw(6) << "TAT"
         << setw(5) << "WT"
         << "\n" << string(31,'-') << "\n";

    double totalTAT = 0, totalWT = 0;

    // Output Table
    for (int i = 0; i < n; i++) {

        cout << left << setw(5) << ("P" + to_string(p[i].pid))
             << setw(5) << p[i].at
             << setw(5) << p[i].bt
             << setw(5) << p[i].ct
             << setw(6) << p[i].tat
             << setw(5) << p[i].wt << endl;

        totalTAT += p[i].tat;
        totalWT  += p[i].wt;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage TAT: " << totalTAT / n;
    cout << "\nAverage WT : " << totalWT / n;

    return 0;
}