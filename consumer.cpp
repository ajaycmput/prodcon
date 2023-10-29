#include <iostream>
#include <fstream>
#include "common.h"
#include "tands.h"

using namespace std;

int numAsk = 0;
int numReceive = 0;
int numComplete = 0;

void* consumerFunction(void* arg) {
    // retrieve consumer ID and freeing dynamically allocated memory
    int id = *(int*) arg;
    delete (int*) arg;

    while(true) {
        pthread_mutex_lock(&queueMutex);

        pthread_mutex_lock(&logMutex);
        logFile<< "ID= " << id << " Ask" << endl;
        numAsk++;
        pthread_mutex_unlock(&logMutex);

        while(workQueue.empty()) {
            pthread_cond_wait(&queueCondVar, &queueMutex);
        }

        // take task from the front of the queue
        int work = workQueue.front();
        workQueue.pop();

        pthread_mutex_lock(&logMutex);
        logFile << "ID= " << id << " Q= " << workQueue.size() << " Receive " << work << endl;
        numReceive++;
        pthread_mutex_unlock(&logMutex);

        pthread_cond_broadcast(&queueCondVar); // Signal that work has been removed (useful for the producer)
        pthread_mutex_unlock(&queueMutex);

        Trans(work); // do actual work

        pthread_mutex_lock(&logMutex);
        logFile << "ID= " << id << " Complete " << work << endl;
        numComplete++;
        pthread_mutex_unlock(&logMutex);
    }

    return NULL;
}