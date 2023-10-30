#include <iostream>
#include <pthread.h>
#include "common.h"


using namespace std;

int totalWorkCommands = 0;
int totalSleepCommands = 0;
int numAsk = 0;
int numReceive = 0;
int numComplete = 0;

queue<int> workQueue;
pthread_mutex_t queueMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t queueCondVar = PTHREAD_COND_INITIALIZER;
pthread_mutex_t logMutex = PTHREAD_MUTEX_INITIALIZER;
ofstream logFile;

size_t maxQueueSize = 0;  // Changed type to size_t

void InitializeQueue(int numberOfConsumers) {
    maxQueueSize = 2 * numberOfConsumers;
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <number_of_consumer_threads> [<id>]" << endl;
        return 1;
    }

    int numberOfConsumers = stoi(argv[1]);
    int id = (argc == 3) ? stoi(argv[2]) : 0;

    // Initialie the work queue
    InitializeQueue(numberOfConsumers);

    // Initialize mutex and condvar
    pthread_mutex_init(&queueMutex, nullptr);
    pthread_cond_init(&queueCondVar, nullptr);
    pthread_mutex_init(&logMutex, nullptr);

    // open logfile based on id
    string logFileName = "prodcon." + to_string(id) + ".log";
    logFile.open(logFileName);

    // Create the consumer pthreads
    pthread_t* consumerThreads = new pthread_t[numberOfConsumers]; // creating an array of thread identifiers (store in heap)
    for (int i = 0; i < numberOfConsumers; ++i) {
        pthread_create(&consumerThreads[i], NULL, consumerFunction, (void*) (intptr_t)(i+1)); // create actual consumer threads for each thread identifier
    }

    producerFunction();

    // Join consumer threads (ensures main program doesnt terminate until all consumer threads have finished their work)
    for (int i = 0; i < numberOfConsumers; ++i) {
        pthread_join(consumerThreads[i], NULL);
    }

    pthread_mutex_lock(&logMutex);
    logFile << "Summary:" << endl;
    logFile << "Work " << totalWorkCommands << endl;
    logFile << "Ask " << numAsk << endl;
    logFile << "Receive " << numReceive << endl;
    logFile << "Complete " << numComplete << endl;
    logFile << "Sleep " << totalSleepCommands << endl;
    pthread_mutex_unlock(&logMutex);

    // Clean up
    delete[] consumerThreads;
    logFile.close();

    pthread_mutex_destroy(&queueMutex);
    pthread_cond_destroy(&queueCondVar);
    pthread_mutex_destroy(&logMutex);


    return 0;

}