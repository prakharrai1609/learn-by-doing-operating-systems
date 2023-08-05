#include <iostream>
#include <queue>
#include <mutex>
#include <thread>

std::queue<int> globalQueue;
std::mutex mutexLock;

int THREAD_COUNT = 5000;

void ThreadFunction(int index) {
    mutexLock.lock();
    globalQueue.push(index);
    mutexLock.unlock();
}

int main() {
    std::thread threads[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; i++) {
        threads[i] = std::thread(ThreadFunction, i);
    }

    std::cout << "Size of the global queue: " << globalQueue.size();

    return 0;
}
