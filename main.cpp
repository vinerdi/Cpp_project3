#include <iostream>
#include <queue>
#include <vector>
#include <string>

struct PrintJob {
    std::string user;
    int priority;
    double requestTime;
};

struct PrintJobComparator {
    bool operator()(const PrintJob& a, const PrintJob& b) {
        return a.priority < b.priority;
    }
};

int main() {
    std::priority_queue<PrintJob, std::vector<PrintJob>, PrintJobComparator> printQueue;
    std::queue<PrintJob> printLog;

    int numJobs;
    std::cout << "Enter number of print jobs: ";
    std::cin >> numJobs;

    for (int i = 0; i < numJobs; ++i) {
        PrintJob job;
        std::cout << "Enter user name: ";
        std::cin >> job.user;
        std::cout << "Enter priority (higher number means higher priority): ";
        std::cin >> job.priority;
        job.requestTime = i * 5; // Simulate request time
        printQueue.push(job);
    }

    while (!printQueue.empty()) {
        PrintJob job = printQueue.top();
        printQueue.pop();
        printLog.push(job);
        std::cout << "Printing job for user: " << job.user << " with priority: " << job.priority << std::endl;
    }

    std::cout << "\nPrint log:\n";
    while (!printLog.empty()) {
        PrintJob job = printLog.front();
        printLog.pop();
        std::cout << "User: " << job.user << ", Priority: " << job.priority << ", Request Time: " << job.requestTime << std::endl;
    }

    return 0;
}
