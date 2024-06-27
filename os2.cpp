#include <iostream>
#include <vector>

struct Process {
    int pid;  // Process ID
    int burst_time;  // CPU Burst Time required
    int waiting_time;  // Waiting time
    int turnaround_time;  // Turnaround time

    // Constructor to initialize a Process
    Process(int id, int bt) : pid(id), burst_time(bt), waiting_time(0), turnaround_time(0) {}
};

// Function to find waiting time of all processes
void findWaitingTime(std::vector<Process>& processes) {
    processes[0].waiting_time = 0;  // First process has no waiting time

    for (size_t i = 1; i < processes.size(); i++) {
        processes[i].waiting_time = processes[i-1].waiting_time + processes[i-1].burst_time;
    }
}

// Function to find turnaround time for all processes
void findTurnaroundTime(std::vector<Process>& processes) {
    for (size_t i = 0; i < processes.size(); i++) {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
    }
}

// Function to calculate average waiting and turnaround time
void findAverageTime(std::vector<Process>& processes) {
    findWaitingTime(processes);
    findTurnaroundTime(processes);

    int total_waiting_time = 0, total_turnaround_time = 0;
    for (size_t i = 0; i < processes.size(); i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    std::cout << "Average waiting time: " << (double)total_waiting_time / processes.size() << std::endl;
    std::cout << "Average turnaround time: " << (double)total_turnaround_time / processes.size() << std::endl;
}

int main() {
    std::vector<Process> processes;
    processes.push_back(Process(1, 10));
    processes.push_back(Process(2, 5));
    processes.push_back(Process(3, 8));

    findAverageTime(processes);
    return 0;
}

