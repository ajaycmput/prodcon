#include <queue>
#include <pthread.h>

using namespace std;

extern int totalWorkCommands;
extern int totalSleepCommands;
extern int numAsk;
extern int numReceive;
extern int numComplete;

queue<int> workQueue; // Queue to hold tasks
pthread_mutex_t queueMutex = PTHREAD_MUTEX_INITIALIZER; // Mutex for queue synchronization
pthread_cond_t queueCondVar = PTHREAD_COND_INITIALIZER; // Condition variable for queue synchronization
pthread_mutex_t logMutex;
extern ofstream logFile;


int maxQueueSize;

void InitializeQueue(int numberOfConsumers) {
    maxQueueSize = 2 * numberOfConsumers;
}

void* consumerFunction(void* arg);
void producerFunction();