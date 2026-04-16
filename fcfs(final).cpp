#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip> // Required for formatting the table (std::setw)

// Structure to represent a process
struct Process {
    std::string id;
    int at;  // Arrival Time
    int bt;  // Burst Time
    int ct;  // Completion Time
    int tat; // Turn Around Time
    int wt;  // Waiting Time
};

// Custom comparator function for sorting the processes
bool compareProcesses(const Process& p1, const Process& p2) {
    // Primary condition: Sort by Arrival Time (Ascending)
    if (p1.at != p2.at) {
        return p1.at < p2.at; 
    }
    // Tie-breaker condition: Sort by Burst Time (Descending)
    return p1.bt > p2.bt; 
}

int main() {
    int n;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Number of processes must be greater than 0." << std::endl;
        return 1; 
    }

    std::vector<Process> processes(n);

    std::cout << "Enter ID, Arrival Time (AT), and Burst Time (BT) for each process:" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cin >> processes[i].id >> processes[i].at >> processes[i].bt;
    }

    // 1. Sort the processes based on AT and BT
    std::sort(processes.begin(), processes.end(), compareProcesses);

    // 2. Calculate CT, TAT, and WT
    int current_time = 0;

    for (int i = 0; i < n; ++i) {
        // If the CPU is idle (current time is less than the arrival time of the next process)
        if (current_time < processes[i].at) {
            current_time = processes[i].at;
        }

        // Calculate Completion Time
        processes[i].ct = current_time + processes[i].bt;
        
        // Update the CPU's current time to the end of this process
        current_time = processes[i].ct; 

        // Calculate Turn Around Time (CT - AT)
        processes[i].tat = processes[i].ct - processes[i].at;

        // Calculate Waiting Time (TAT - BT)
        processes[i].wt = processes[i].tat - processes[i].bt;
    }

    // 3. Print the Execution Sequence
    std::cout << "\nExecution Sequence: ";
    for (size_t i = 0; i < processes.size(); ++i) {
        std::cout << processes[i].id;
        if (i < processes.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << "\n\n";

    // 4. Print the final calculations in a formatted table
    std::cout << "------------------------------------------------------------\n";
    std::cout << std::left 
              << std::setw(10) << "Process" 
              << std::setw(10) << "AT" 
              << std::setw(10) << "BT" 
              << std::setw(10) << "CT" 
              << std::setw(10) << "TAT" 
              << std::setw(10) << "WT" << "\n";
    std::cout << "------------------------------------------------------------\n";
    
    for (int i = 0; i < n; ++i) {
        std::cout << std::left 
                  << std::setw(10) << processes[i].id 
                  << std::setw(10) << processes[i].at 
                  << std::setw(10) << processes[i].bt 
                  << std::setw(10) << processes[i].ct 
                  << std::setw(10) << processes[i].tat 
                  << std::setw(10) << processes[i].wt << "\n";
    }
    std::cout << "------------------------------------------------------------\n";

    return 0;
}