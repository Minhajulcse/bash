#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <climits> // Required for INT_MAX

// Structure to represent a process
struct Process {
    std::string id;
    int at;  // Arrival Time
    int bt;  // Burst Time
    int ct;  // Completion Time
    int tat; // Turn Around Time
    int wt;  // Waiting Time
    bool is_completed = false; // Flag to track if the process is finished
};

int main() {
    int n;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Number of processes must be greater than 0." << std::endl;
        return 1; 
    }

    std::vector<Process> processes(n);

    std::cout << "Enter ID, Arrival Time (AT), and Burst Time (BT) for each process:\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> processes[i].id >> processes[i].at >> processes[i].bt;
    }

    int current_time = 0;
    int completed_count = 0;
    std::vector<Process> execution_order; // To store the processes in the order they execute

    // Keep running until all processes are completed
    while (completed_count < n) {
        int shortest_idx = -1;
        int min_bt = INT_MAX;

        // Find the process with the shortest burst time among those that have arrived
        for (int i = 0; i < n; ++i) {
            if (processes[i].at <= current_time && !processes[i].is_completed) {
                if (processes[i].bt < min_bt) {
                    min_bt = processes[i].bt;
                    shortest_idx = i;
                } 
                // Tie-breaker: If burst times are equal, pick the one that arrived first
                else if (processes[i].bt == min_bt) {
                    if (processes[i].at < processes[shortest_idx].at) {
                        shortest_idx = i;
                    }
                }
            }
        }

        // If we found an available process to execute
        if (shortest_idx != -1) {
            // Jump time forward by the burst time
            current_time += processes[shortest_idx].bt;
            
            // Calculate metrics
            processes[shortest_idx].ct = current_time;
            processes[shortest_idx].tat = processes[shortest_idx].ct - processes[shortest_idx].at;
            processes[shortest_idx].wt = processes[shortest_idx].tat - processes[shortest_idx].bt;
            
            // Mark as completed and add to our sequence list
            processes[shortest_idx].is_completed = true;
            execution_order.push_back(processes[shortest_idx]);
            completed_count++;
        } 
        else {
            // CPU is idle (no processes have arrived yet), move time forward
            current_time++; 
        }
    }

    // Print the Execution Sequence
    std::cout << "\nExecution Sequence: ";
    for (size_t i = 0; i < execution_order.size(); ++i) {
        std::cout << execution_order[i].id;
        if (i < execution_order.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << "\n\n";

    // Print the final calculations in a formatted table
    std::cout << "------------------------------------------------------------\n";
    std::cout << std::left 
              << std::setw(10) << "Process" 
              << std::setw(10) << "AT" 
              << std::setw(10) << "BT" 
              << std::setw(10) << "CT" 
              << std::setw(10) << "TAT" 
              << std::setw(10) << "WT" << "\n";
    std::cout << "------------------------------------------------------------\n";
    
    // Printing based on execution order so the timeline is easy to read
    for (size_t i = 0; i < execution_order.size(); ++i) {
        std::cout << std::left 
                  << std::setw(10) << execution_order[i].id 
                  << std::setw(10) << execution_order[i].at 
                  << std::setw(10) << execution_order[i].bt 
                  << std::setw(10) << execution_order[i].ct 
                  << std::setw(10) << execution_order[i].tat 
                  << std::setw(10) << execution_order[i].wt << "\n";
    }
    std::cout << "------------------------------------------------------------\n";

    return 0;
}