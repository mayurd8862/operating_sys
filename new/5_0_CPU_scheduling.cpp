#include <iostream>
#include <vector>
#define MAX_PROCESS 10
using namespace std;

int num_of_process;
vector<int> arrival_time(MAX_PROCESS);
vector<int> burst_time(MAX_PROCESS);
vector<int> completion_time(MAX_PROCESS);
vector<int> waiting_time(MAX_PROCESS);
vector<int> turnaround_time(MAX_PROCESS);
vector<int> response_time(MAX_PROCESS);

void getProcessInfo()
{
    cout << "Enter total number of processes (maximum " << MAX_PROCESS << "): ";
    cin >> num_of_process;

    if (num_of_process < 1 || num_of_process > MAX_PROCESS)
    {
        cout << "Invalid number of processes. Please enter a number between 1 and " << MAX_PROCESS << "." << endl;
        exit(1);
    }

    for (int i = 0; i < num_of_process; i++)
    {
        cout << "\nProcess " << i + 1 << ":\n";
        cout << "Arrival Time: ";
        cin >> arrival_time[i];
        cout << "Burst Time: ";
        cin >> burst_time[i];
    }
}

void calculateFCFS()
{
    int current_time = 0;

    for (int i = 0; i < num_of_process; i++)
    {
        response_time[i] = current_time - arrival_time[i];
        completion_time[i] = (current_time < arrival_time[i]) ? arrival_time[i] + burst_time[i] : current_time + burst_time[i];
        current_time = completion_time[i];
        waiting_time[i] = completion_time[i] - burst_time[i] - arrival_time[i];
        turnaround_time[i] = completion_time[i] - arrival_time[i];
    }
}

void calculateSJF()
{
    for (int i = 0; i < num_of_process - 1; i++)
    {
        for (int j = 0; j < num_of_process - i - 1; j++)
        {
            if (burst_time[j] > burst_time[j + 1])
            {
                int temp_burst = burst_time[j];
                burst_time[j] = burst_time[j + 1];
                burst_time[j + 1] = temp_burst;
                int temp_arrival = arrival_time[j];
                arrival_time[j] = arrival_time[j + 1];
                arrival_time[j + 1] = temp_arrival;
            }
        }
    }

    int current_time = 0;

    for (int i = 0; i < num_of_process; i++)
    {
        response_time[i] = current_time - arrival_time[i];
        completion_time[i] = (current_time < arrival_time[i]) ? arrival_time[i] + burst_time[i] : current_time + burst_time[i];
        current_time = completion_time[i];
        waiting_time[i] = completion_time[i] - burst_time[i] - arrival_time[i];
        turnaround_time[i] = completion_time[i] - arrival_time[i];
    }
}

void calculateRoundRobin(int time_quantum)
{
    vector<int> remaining_time(num_of_process);
    for (int i = 0; i < num_of_process; i++)
    {
        remaining_time[i] = burst_time[i];
    }

    int current_time = 0;

    while (true)
    {
        bool done = true;

        for (int i = 0; i < num_of_process; i++)
        {
            if (remaining_time[i] > 0)
            {
                done = false;

                if (remaining_time[i] > time_quantum)
                {
                    current_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                }
                else
                {
                    current_time += remaining_time[i];
                    completion_time[i] = current_time;
                    waiting_time[i] = current_time - burst_time[i] - arrival_time[i];
                    turnaround_time[i] = completion_time[i] - arrival_time[i];
                    remaining_time[i] = 0;
                }
            }
        }

        if (done)
        {
            break;
        }
    }
}

void calculateAverageTimes(float &avg_waiting_time, float &avg_turnaround_time)
{
    avg_waiting_time = 0.0;
    avg_turnaround_time = 0.0;

    for (int i = 0; i < num_of_process; i++)
    {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
    }

    avg_waiting_time /= num_of_process;
    avg_turnaround_time /= num_of_process;
}

void displayResults(float avg_waiting_time, float avg_turnaround_time)
{
    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\tResponse Time" << endl;
    for (int i = 0; i < num_of_process; i++)
    {
        cout << i + 1 << "\t" << arrival_time[i] << "\t\t" << burst_time[i] << "\t\t" << completion_time[i] << "\t\t" << waiting_time[i] << "\t\t" << turnaround_time[i] << "\t\t" << response_time[i] << endl;
    }

    cout << "\nAverage Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
}

int main()
{
    int selected_algorithm;
    int time_quantum;

    cout << "Select a scheduling algorithm:" << endl;
    cout << "1. FCFS (First-Come-First-Served)" << endl;
    cout << "2. SJF (Shortest Job First)" << endl;
    cout << "3. Round Robin" << endl;
    cout << "Enter your choice: ";
    cin >> selected_algorithm;

    getProcessInfo();

    switch (selected_algorithm)
    {
    case 1:
        calculateFCFS();
        break;
    case 2:
        calculateSJF();
        break;
    case 3:
        cout << "Enter Time Quantum for Round Robin: ";
        cin >> time_quantum;
        calculateRoundRobin(time_quantum);
        break;
    default:
        cout << "Invalid choice. Please select a valid scheduling algorithm." << endl;
        return 1;
    }

    float avg_waiting_time, avg_turnaround_time;
    calculateAverageTimes(avg_waiting_time, avg_turnaround_time);

    displayResults(avg_waiting_time, avg_turnaround_time);

    return 0;
}


//TAT = Completion Time - Arrival Time
//WT = Turnaround Time - Burst Time

