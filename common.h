#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;


queue<int> workQueue; // Queue to hold tasks
mutex queueMutex; // Mutex for queue synchronization
condition_variable queueCondVar; // Condition variable for queue synchronization

int maxQueueSize;

void InitializeQueue(int numberOfConsumers) {
    maxQueueSize = 2 * numberOfConsumers;
}