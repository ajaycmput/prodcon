#include <queue>
#include <pthread.h>
#include <fstream>

using namespace std;

extern int totalWorkCommands;
extern int totalSleepCommands;
extern int numAsk;
extern int numReceive;
extern int numComplete;

extern queue<int> workQueue;
extern pthread_mutex_t queueMutex;
extern pthread_cond_t queueCondVar;
extern pthread_mutex_t logMutex;
extern ofstream logFile;
extern size_t maxQueueSize;  // Changed type to size_t

void InitializeQueue(int numberOfConsumers);
void* consumerFunction(void* arg);
void producerFunction();