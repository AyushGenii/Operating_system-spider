#include <iostream>
#include <vector>

using namespace std;

bool isSafe(vector<int> processes, vector<int> available, vector<vector<int>> max_need, vector<vector<int>> allocation, vector<vector<int>> need) {
    int num_processes = processes.size();
    int num_resources = available.size();

    vector<int> work = available;
    vector<bool> finish(num_processes, false);

    vector<int> safe_sequence;

    while (safe_sequence.size() < num_processes) {
        bool found_process = false;
        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < num_resources; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate) {
                    for (int k = 0; k < num_resources; k++) {
                        work[k] += allocation[i][k];
                    }
                    safe_sequence.push_back(processes[i]);
                    finish[i] = true;
                    found_process = true;
                    break;
                }
            }
        }

        if (!found_process) {
            break;
        }
    }

    if (safe_sequence.size() == num_processes) {
        cout << "System is in a safe state." << endl;
        cout << "Safe sequence: ";
        for (int i = 0; i < safe_sequence.size(); i++) {
            cout << safe_sequence[i] << " ";
        }
        cout << endl;
        return true;
    } else {
        cout << "System is not in a safe state. Deadlock is possible." << endl;
        return false;
    }
}

int main() {
    vector<int> processes = {0, 1, 2, 3, 4};
    vector<int> available = {3, 3, 2};

    vector<vector<int>> max_need = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    vector<vector<int>> allocation = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    vector<vector<int>> need(max_need.size(), vector<int>(available.size()));
    for (int i = 0; i < max_need.size(); i++) {
        for (int j = 0; j < available.size(); j++) {
            need[i][j] = max_need[i][j] - allocation[i][j];
        }
    }

    isSafe(processes, available, max_need, allocation, need);

    return 0;
}

