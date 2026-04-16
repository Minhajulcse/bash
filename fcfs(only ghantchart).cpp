#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Structure to represent a process
struct Process {
    std::string id;
    int at; // Arrival Time
    int bt; // Burst Time
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
    // std::cout << "Enter the number of processes: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Number of processes must be greater than 0." << std::endl;
        return 1; 
    }

    std::vector<Process> processes(n);

    // std::cout << "Enter ID, Arrival Time (AT), and Burst Time (BT) for each process:" << std::endl;
    
    // Loop to take user input for ID, AT, and BT
    for (int i = 0; i < n; ++i) {
        std::cin >> processes[i].id >> processes[i].at >> processes[i].bt;
    }

    // Sort the processes using the custom rules
    std::sort(processes.begin(), processes.end(), compareProcesses);

    // Print the output in the required format
    std::cout << "Output:\n";
    for (size_t i = 0; i < processes.size(); ++i) {
        std::cout << processes[i].id;
        if (i < processes.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;

    return 0;
}