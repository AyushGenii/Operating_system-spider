#include <iostream>
#include <vector>

struct Process {
    int pid; 
    int burst_time;  
    int waiting_time;  
    int turnaround_time;  

   
    Process(int id, int bt) : pid(id), burst_time(bt), waiting_time(0), turnaround_time(0) {}
};


void findWaitingTime(std::vector<Process>& processes) {
    processes[0].waiting_time = 0;  

    for (size_t i = 1; i < processes.size(); i++) {
        processes[i].waiting_time = processes[i-1].waiting_time + processes[i-1].burst_time;
    }
}


void findTurnaroundTime(std::vector<Process>& processes) {
    for (size_t i = 0; i < processes.size(); i++) {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
    }
}


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

