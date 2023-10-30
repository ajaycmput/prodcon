#include <iostream>
#include <string>
#include "common.h"
#include "tands.h"

using namespace std;

void producerFunction() {
    string command;

    while(cin >> command) {
        char cmdType = command[0];
        int n = stoi(command.substr(1));

        if (cmdType == 'T') {
            // if the work queue is full, producer waits and unlocks the mutex (since its full)
            // for the consumer threads to signal condition variable. When signaled, mutex locks again and owned by producer
            totalWorkCommands++;
            pthread_mutex_lock(&queueMutex);
            while(workQueue.size() >= maxQueueSize) {
                pthread_cond_wait(&queueCondVar, &queueMutex);
            }
            workQueue.push(n);
            pthread_cond_broadcast(&queueCondVar); // signal to consumer threads that the condition has changed (item has been added to queue)
            pthread_mutex_unlock(&queueMutex);

            pthread_mutex_lock(&logMutex);
            logFile << "ID= 0 Q= " << workQueue.size() << " Work " << n << endl;
            pthread_mutex_unlock(&logMutex);

        } else if (cmdType == 'S') {
            totalSleepCommands++;
            Sleep(n);
            pthread_mutex_lock(&logMutex);
            logFile << "ID= 0 Sleep " << n << endl;
            pthread_mutex_unlock(&logMutex);
        }
    }
    // Signal to consumers that producton is done
    // ...


}