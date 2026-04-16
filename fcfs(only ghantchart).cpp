#include <bits/stdc++.h>
using namespace std;

#define int long long
#define optimize() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

// Structure to hold process data
struct Process {
    string id;
    int at;
    int bt;
};

// Custom comparator for the sorting logic
bool compareProcesses(const Process& a, const Process& b) {
    if (a.at == b.at) {
        return a.bt > b.bt; // Tie-break: largest burst time first
    }
    return a.at < b.at;     // Primary: earliest arrival time first
}

int32_t main() {
    optimize();
    
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    
    vector<Process> p(n);
    cout << "Enter Process ID, AT, and BT for each process:\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i].id >> p[i].at >> p[i].bt;
    }
    
    // Sort the processes using the custom logic
    sort(p.begin(), p.end(), compareProcesses);
    
    // Print the output format requested in the lab
    cout << "Output:\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].id;
        if (i < n - 1) cout << " -> ";
    }
    cout << "\n";
    
    return 0;
}